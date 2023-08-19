#define TRIG_PIN_NUM 9 //TRIG 핀과 연결된 아두이노 핀 번호 (초음파 보내는 핀)
#define ECHO_PIN_NUM 8 //ECHO 핀과 연결된 아두이노 핀 번호 (초음파 받는 핀)
#define STOP_DISTANCE_CM 15 //자동차가 정지하는 기준 거리
#define CHECK_INTERVAL 300 //초음파 센서로 거리를 측정하는 시간 간격

#define MOTOR_A_a 3     //모터A의 +출력핀은 3번핀입니다
#define MOTOR_A_b 11    //모터A의 -출력핀은 11번핀입니다
#define MOTOR_B_a 5     //모터B의 +출력핀은 5번핀입니다
#define MOTOR_B_b 6     //모터B의 -출력핀은 6번핀입니다

#define MOTOR_SPEED_0 0 //모터의 속력을 단계별로 나눴습니다 (0~255)
#define MOTOR_SPEED_1 120
#define MOTOR_SPEED_2 150
#define MOTOR_SPEED_3 170
#define MOTOR_SPEED_4 200
#define MOTOR_SPEED_MAX 250

void setup() { //setup은 처음 한 번 실행되는 함수 입니다.
  //모터 제어 핀들을 출력으로 설정합니다.
  pinMode(MOTOR_A_a, OUTPUT);
  pinMode(MOTOR_A_b, OUTPUT);
  pinMode(MOTOR_B_a, OUTPUT);
  pinMode(MOTOR_B_b, OUTPUT);

  Serial.begin(9600);       //시리얼 통신 초기화
  Serial.println("Hello!"); //터미널 작동 확인용 문자열

  pinMode(TRIG_PIN_NUM, OUTPUT); //TRIG 핀과 연결된 아두이노 핀을 출력으로 설정
  pinMode(ECHO_PIN_NUM, INPUT); //ECHO 핀과 연결된 아두이노 핀을 입력으로 설정
}

void loop() { //loop는 계속 반복 실행되는 함수 입니다.
  long duration, distance;

  //거리를 측정
  distance = getDistance();
  if (distance > STOP_DISTANCE_CM) {
    //속도 계산하기
    int speed = getSpeed(distance);

    //정해진 속도로 전진하기
    driveCarForward(speed);

    Serial.print(distance); //터미널 작동 확인용 문자열
    Serial.print(" moving "); //터미널 작동 확인용 문자열
    Serial.println(speed); //터미널 작동 확인용 문자열
  } else {
    waitCar();
  }
  delay(CHECK_INTERVAL); // CHECK_INTERVAL 만큼 대기
}

void waitCar() {
  driveCarForward(MOTOR_SPEED_0); //자동차를 정지합니다.
}

int getSpeed(int distance) {
  // 거리에 따라서 속도를 다르게 설정합니다.
  if (distance > 100) {
    // 100cm보다 멀리 있을 때 설정
    return MOTOR_SPEED_MAX;
  } 
  if (distance > 80) {
    // 80cm보다 멀리 있을 때 설정
    return MOTOR_SPEED_4;
  }
  if (distance > 50) {
    // 50cm보다 멀리 있을 때 설정
    return MOTOR_SPEED_3;
  } 
  if (distance > 30) {
    // 30cm보다 멀리 있을 때 설정
    return MOTOR_SPEED_2;
  } 
  if (distance > 10) {
    // 10cm보다 멀리 있을 때 설정
    return MOTOR_SPEED_1;
  }

  // 10cm보다 가까이 있을 때 설정
  return MOTOR_SPEED_0;
}

long getDistance() { // 거리를 측정해서 반환하는 함수입니다.
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

  return distance;
}

void driveCarForward(unsigned int speed) //차를 전달받은 속도로 전진하는 함수
{
  if (speed > 255)
    return;

  digitalWrite(MOTOR_A_a, LOW); //모터A+ LOW
  analogWrite(MOTOR_A_b, speed); //모터A-의 속력을 PWM 출력

  analogWrite(MOTOR_B_a, speed); //모터B+의 속력을 PWM 출력
  digitalWrite(MOTOR_B_b, LOW); //모터B- LOW
}
