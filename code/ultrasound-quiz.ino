#define TRIG_PIN_NUM 9 //TRIG 핀과 연결된 아두이노 핀 번호 (초음파 보내는 핀)
#define ECHO_PIN_NUM 8 //ECHO 핀과 연결된 아두이노 핀 번호 (초음파 받는 핀)
#define LED_PIN_NUM 7 //LED와 연결된 아두이노 핀 번호

void setup() { //setup은 처음 한 번 실행되는 함수 입니다.
  Serial.begin(9600); //PC와 시리얼 통신을 설정

  pinMode(TRIG_PIN_NUM, OUTPUT); //TRIG 핀과 연결된 아두이노 핀을 출력으로 설정
  pinMode(ECHO_PIN_NUM, INPUT); //ECHO 핀과 연결된 아두이노 핀을 입력으로 설정
}

void loop() { //loop는 계속 반복 실행되는 함수 입니다.
  int blinkInterval = 0;
  long distance = getDistance(); // 거리를 측정해서 distance에 저장합니다.
  int totalDuration = 0;

  // 거리에 따라서 깜빡이는 속도를 다르게 설정합니다.
  if (distance > 40) {
    // 40cm보다 멀리 있을 때 설정
    blinkInterval = 1000;
  } else if (distance > 30) {
    // 30cm보다 멀리 있을 때 설정
    blinkInterval = 700;
  } else if (distance > 20) {
    // 20cm보다 멀리 있을 때 설정
    blinkInterval = 500;
  } else if (distance > 10) {
    // 10cm보다 멀리 있을 때 설정
    blinkInterval = 200;
  } else {
    // 10cm보다 가까이 있을 때 설정
    blinkInterval = 100;
  }

  while (true) { // 계속 반복되는 블럭
    blink_led(blinkInterval); // blinkInterval 동안 led를 깜빡임
    totalDuration = totalDuration + blinkInterval; // 깜빡인 시간을 더함

    if (totalDuration >= 2000){
      // 깜빡인 시간을 모두 더한 값이 2초 이상이면 반복을 중단함
      Serial.print("\totalDuration : ");
      Serial.println(totalDuration); // LED가 깜빡이는 시간을 보여줍니다.
      break;
    }
  }
}

// 주어진 시간 동안 led를 깜빡이는 함수입니다.
void blink_led(int duration)
{
  Serial.print("\n blink_led Duration : ");
  Serial.println(duration); // LED가 깜빡이는 시간을 보여줍니다.

  int half = duration / 2;
  digitalWrite(LED_PIN_NUM, HIGH);
  delay(half);
  digitalWrite(LED_PIN_NUM, LOW);
  delay(half);
}

// 거리를 측정해서 반환하는 함수입니다.
long getDistance()
{
  long duration, distance;

  digitalWrite(TRIG_PIN_NUM, LOW); //TRIG 핀의 신호를 LOW로 설정
  delayMicroseconds(2); // 2마이크로세컨드(0.000002초) 대기, 센서의 동작을 기다림

  digitalWrite(TRIG_PIN_NUM, HIGH); //TRIG 핀의 신호를 HIGH로 설정
  delayMicroseconds(10);  // 10마이크로세컨드(0.00001초) 대기, 센서의 동작을 기다림

  digitalWrite(TRIG_PIN_NUM, LOW); //TRIG 핀의 신호를 LOW로 설정

  duration = pulseIn(ECHO_PIN_NUM, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  // "pulseIn" Returns the length of the pulse in microseconds or gives up and returns 0 if no complete pulse was received within the timeout.

  // 거리를 구하는 공식의 단위를 맞춰서 계산해야 합니다.
  // 34000 * 초음파가 물체로 부터 반사되어 돌아오는시간 / 1000000 / 2 (왕복거리이므로 나누기 2를 해줍니다.)
  // 각각 m(미터) -> cm(센티미터), s(초) -> micro sec(마이크로 초)
  // 식을 정리하면 아래와 같습니다.
  distance = duration * 17 / 1000; 

  // PC모니터로 초음파 거리값을 확인 하는 코드 입니다.
  Serial.println(duration ); // 초음파가 반사되어 돌아오는 시간을 보여줍니다.
  Serial.print("\nDIstance : ");
  Serial.print(distance); // 측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" cm");

  return distance;
}