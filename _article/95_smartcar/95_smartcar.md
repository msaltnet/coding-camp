author: Jeong Seongmoon
summary: 장애물을 피해 주행하는 자동차 프로그래밍
id: smart-car
categories: codelab
environments: Web
status: Published
feedback link: https://github.com/msaltnet/coding-camp

# 장애물을 피해 주행하는 자동차 프로그래밍

## 시작하기
Duration: 0:01:00

조립된 자동차가 장애물을 피해서 주행하도록 프로그래밍을 해봅시다.

### 사전 준비
1. 조립된 자동차와 아두이노 보드
1. 아두이노와 연결 가능한 PC와 IDE

### 배우게 될 것
1. 장애물과의 거리를 측정해서 자동차의 속도를 결정하는 방법
1. 장애물을 만났을 때 LED와 Buzzer를 사용해서 빛과 소리를 내는 방법
1. 장애물이 사라지지 않을때 방향을 전황해서 이동하는 방법

## LED 연결하기
Duration: 0:03:00

앞에서 조립한 자동차에 추가로 LED를 연결합니다.

LED 불 빛이 동작하도록 붉은 색과 초록 색 LED를 각각 저항과 함께 회로에 연결해 줍니다.

## Buzzer 연결하기
Duration: 0:03:00

장애물을 발견했을 때 소리를 낼 수 있도록 Buzzer를 연결해 줍니다.

## 프로그램의 전체 동작 설명
Duration: 0:03:00

프로그램의 전체 동작을 간단하게 정리하면 다음과 같습니다.

1. 초음파 센서로 장애물과의 거리를 측정해서 거리에 따라 속도를 다르게 한다.
2. 장애물을 발견하면 LED와 Buzzer를 동작하면서 대기한다.
3. 일정 시간동안 대기해도 장애물이 있다면 방향을 전환한다.
4. 반복적으로 거리를 측정하면서 스스로 동작한다.

세부 동작을 포함한 순서도는 아래와 같습니다. 매우 복잡해 보이지만 하나씩 차근차근 만들면 완성할 수 있습니다.

//순서도

## 거리에 따라 속도를 다르게 이동하기
Duration: 0:05:00

전체 프로그램을 모두 완성하기 전에 우선 거리에 따라 속도를 다르게 이동하는 부분만 먼저 구현을 해보겠습니다.

// 순서도에서 앞부분

다음과 같이 프로그램을 구성해서 업로드를 하고, 동작을 확인해 봅니다.

코드 내용은 천천히 혼자 스스로 이해해보세요.

```c
#define TRIG_PIN_NUM 9 //TRIG 핀과 연결된 아두이노 핀 번호 (초음파 보내는 핀)
#define ECHO_PIN_NUM 8 //ECHO 핀과 연결된 아두이노 핀 번호 (초음파 받는 핀)
#define STOP_DISTANCE_CM 15 //자동차가 정지하는 기준 거리
#define CHECK_INTERVAL 200 //초음파 센서로 거리를 측정하는 시간 간격

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
```

## LED를 켜고 끄기
Duration: 0:05:00

이번에는 앞에서 구현한 프로그램에 LED를 켜고 끄는 부분을 추가해 보겠습니다.

// 순서도에서 앞부분

녹색과 빨간색 LED가 연결된 핀에 대해서 설정해 줍니다.
```c
#define LED_GREEN_PIN_NUM 4 // 녹색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)
#define LED_RED_PIN_NUM 2 // 빨간색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)
```

`setup`에서 출력으로 설정해줍니다.
```c
  pinMode(LED_GREEN_PIN_NUM, OUTPUT); // 녹색 LED의 긴다리 핀을 출력으로 설정
  pinMode(LED_RED_PIN_NUM, OUTPUT); // 빨간색 LED의 긴다리 핀을 출력으로 설정
```

만들어서 녹색, 또는 빨간색 LED를 켜는 `setLed` 함수를 만들어서 호출해 주도록 합니다.
```c
void setLed(bool on, bool isRed) {
  if (!on) {
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW);
    return;
  }

  if (isRed) { // 빨간색인지 확인합니다.
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // 녹색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, HIGH); // 빨간색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
  } else {
    digitalWrite(LED_GREEN_PIN_NUM, HIGH); // 녹색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW); // 빨간색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
  }
}

```

전체 프로그램을 다음과 같이 구성해서 업로드를 하고, 동작을 확인해 봅니다.

코드 내용은 천천히 혼자 스스로 이해해보세요.

```c
#define LED_GREEN_PIN_NUM 4 // 녹색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)
#define LED_RED_PIN_NUM 2 // 빨간색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)

#define TRIG_PIN_NUM 9 //TRIG 핀과 연결된 아두이노 핀 번호 (초음파 보내는 핀)
#define ECHO_PIN_NUM 8 //ECHO 핀과 연결된 아두이노 핀 번호 (초음파 받는 핀)
#define STOP_DISTANCE_CM 15 //자동차가 정지하는 기준 거리
#define CHECK_INTERVAL 200 //초음파 센서로 거리를 측정하는 시간 간격

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

  pinMode(LED_GREEN_PIN_NUM, OUTPUT); // 녹색 LED의 긴다리 핀을 출력으로 설정
  pinMode(LED_RED_PIN_NUM, OUTPUT); // 빨간색 LED의 긴다리 핀을 출력으로 설정
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

    setLed(true, false); // 녹색 LED를 켭니다.
  } else {
    waitCar();
  }
  delay(CHECK_INTERVAL); // CHECK_INTERVAL 만큼 대기
}

void waitCar() {
  driveCarForward(MOTOR_SPEED_0); //자동차를 정지합니다.

  setLed(true, true); // 빨간색 LED를 켭니다.
}

void setLed(bool on, bool isRed) {
  if (!on) {
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW);
    return;
  }

  if (isRed) { // 빨간색인지 확인합니다.
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // 녹색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, HIGH); // 빨간색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
  } else {
    digitalWrite(LED_GREEN_PIN_NUM, HIGH); // 녹색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW); // 빨간색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
  }
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
```

## 삐삐 소리를 내기
Duration: 0:05:00

이번에는 앞에서 구현한 프로그램에 Buzzer를 이용해서 소리를 내는 부분을 추가하겠습니다.

// 순서도에서 앞부분

Buzzer와 연결된 핀과 소리를 낼 주파수 그리고 소리가 나는 시간을 정해줍니다.
```c
#define BUZZER_PIN_NUM 7//아두이노와 연결된 Buzzer 핀 번호
#define BUZZER_FREQUENCY 784 // 5옥타브 솔 주파수
#define BUZZER_DURATION 100 // 삐-소리 나는 시간
```

짧게 삐-소리를 내는 함수 `makeBeep`을 만들어서 호출해 주도록 합니다.
```c
void makeBeep() {
  // delay 함수가 호출되는 동안에는 다른 동작을 할 수 없기 때문에 삐- 소리를 짧게 내야합니다.
  tone(BUZZER_PIN_NUM, BUZZER_FREQUENCY); // BUZZER_FREQUENCY 주파수로 소리재생
  delay(BUZZER_DURATION); // BUZZER_DURATION 밀리세컨드 동안 소리재생
  noTone(BUZZER_PIN_NUM); // 소리재생 중지
}
```

전체 프로그램을 다음과 같이 구성해서 업로드를 하고, 동작을 확인해 봅니다.

코드 내용은 천천히 혼자 스스로 이해해보세요.

```c
#define BUZZER_PIN_NUM 7//아두이노와 연결된 Buzzer 핀 번호
#define BUZZER_FREQUENCY 784 // 5옥타브 솔 주파수
#define BUZZER_DURATION 100 // 삐-소리 나는 시간

#define LED_GREEN_PIN_NUM 4 // 녹색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)
#define LED_RED_PIN_NUM 2 // 빨간색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)

#define TRIG_PIN_NUM 9 //TRIG 핀과 연결된 아두이노 핀 번호 (초음파 보내는 핀)
#define ECHO_PIN_NUM 8 //ECHO 핀과 연결된 아두이노 핀 번호 (초음파 받는 핀)
#define STOP_DISTANCE_CM 15 //자동차가 정지하는 기준 거리
#define CHECK_INTERVAL 200 //초음파 센서로 거리를 측정하는 시간 간격

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

  pinMode(LED_GREEN_PIN_NUM, OUTPUT); // 녹색 LED의 긴다리 핀을 출력으로 설정
  pinMode(LED_RED_PIN_NUM, OUTPUT); // 빨간색 LED의 긴다리 핀을 출력으로 설정
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

    setLed(true, false); // 녹색 LED를 켭니다.
  } else {
    waitCar();
  }
  delay(CHECK_INTERVAL); // CHECK_INTERVAL 만큼 대기
}

void waitCar() {
  driveCarForward(MOTOR_SPEED_0); //자동차를 정지합니다.

  setLed(true, true); // 빨간색 LED를 켭니다.

  makeBeep(); // 삐- 소리를 짧게 재생합니다.
}

void makeBeep() {
  // delay 함수가 호출되는 동안에는 다른 동작을 할 수 없기 때문에 삐- 소리를 짧게 내야합니다.
  tone(BUZZER_PIN_NUM, BUZZER_FREQUENCY); // BUZZER_FREQUENCY 주파수로 소리재생
  delay(BUZZER_DURATION); // BUZZER_DURATION 밀리세컨드 동안 소리재생
  noTone(BUZZER_PIN_NUM); // 소리재생 중지
}

void setLed(bool on, bool isRed) {
  if (!on) {
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW);
    return;
  }

  if (isRed) { // 빨간색인지 확인합니다.
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // 녹색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, HIGH); // 빨간색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
  } else {
    digitalWrite(LED_GREEN_PIN_NUM, HIGH); // 녹색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW); // 빨간색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
  }
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
```

## 장애물 피해가기
Duration: 0:05:00

이번에는 마지막으로 5회(5초이상) 기다렸다가 장애물을 피해가는 기능을 추가해보갰습니다.

// 순서도에서 뒷부분

현재 주행중인지 확인하는 변수와 몇 번 기다렸는지 기억하는 변수를 추가해 줍니다. 두 개의 변수는 `loop()` 가 끝나도 상태를 기억하고 있어야 하므로 `loop()` 함수 밖에 추가해 줍니다. 이런 변수를 전역 변수라고 합니다.

```c
bool isMoving = false;
int waitingCount = 0;
```

자동차를 오른쪽으로 조금 회전하는 함수 `turnRight`를 만들어서 사용하도록 합니다.
```c
void turnRight() {
  //두 모터를 반대 방향으로 돌립니다.
  digitalWrite(MOTOR_A_a, LOW); //모터A+ LOW
  analogWrite(MOTOR_A_b, MOTOR_SPEED_3); //모터A-의 속력을 PWM 출력

  analogWrite(MOTOR_B_a, LOW); //모터B+의 속력을 PWM 출력
  digitalWrite(MOTOR_B_b, MOTOR_SPEED_3); //모터B- LOW

  delay(300); // 0.3초 동안 회전합니다.

  //모터를 정지합니다.
  digitalWrite(MOTOR_A_a, LOW); //모터A+ LOW
  analogWrite(MOTOR_A_b, MOTOR_SPEED_0); //모터A-의 속력을 PWM 출력

  analogWrite(MOTOR_B_a, MOTOR_SPEED_0); //모터B+의 속력을 PWM 출력
  digitalWrite(MOTOR_B_b, LOW); //모터B- LOW

}
```

자동차와 장애물의 거리가 가까울때 기다리는 동작을 처리하는 `waitCar`함수에 내용을 채워줍니다. 이로써 복잡해 보였던 전체 프로그램을 모두 완성하였습니다!

```c
void waitCar() {
  if (isMoving) { // 주행중 상태인지 체크합니다.
    driveCarForward(MOTOR_SPEED_0); //자동차를 정지합니다.

    setLed(true, false); // 빨간색 LED를 켭니다.

    makeBeep(); // 삐- 소리를 짧게 재생합니다.

    waitingCount = 1; // 기다린 횟수를 1로 만듭니다.
    isMoving = false;
  } else {
    if (waitingCount < WAINTING_COUNT) {
      waitingCount = waitingCount + 1;
    } else {
      turnRight(); //자동차를 오른쪽으로 회전합니다.

      waitingCount = 0; // 기다린 횟수를 0로 만듭니다.

      isMoving = true; // 주행중 상태로 변경합니다.
    }
  }
}
```

전체 프로그램을 다음과 같이 구성해서 업로드를 하고, 동작을 확인해 봅니다.

코드 내용은 천천히 혼자 스스로 이해해보세요.

```c
#define BUZZER_PIN_NUM 7//아두이노와 연결된 Buzzer 핀 번호
#define BUZZER_FREQUENCY 784 // 5옥타브 솔 주파수
#define BUZZER_DURATION 100 // 삐-소리 나는 시간
#define CHECK_INTERVAL 200 //초음파 센서로 거리를 측정하는 시간 간격
#define WAINTING_COUNT 5

#define LED_GREEN_PIN_NUM 4 // 녹색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)
#define LED_RED_PIN_NUM 2 // 빨간색 LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)

#define TRIG_PIN_NUM 9 //TRIG 핀과 연결된 아두이노 핀 번호 (초음파 보내는 핀)
#define ECHO_PIN_NUM 8 //ECHO 핀과 연결된 아두이노 핀 번호 (초음파 받는 핀)
#define STOP_DISTANCE_CM 15 //자동차가 정지하는 기준 거리

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

bool isMoving = false;
int waitingCount = 0;

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

  pinMode(LED_GREEN_PIN_NUM, OUTPUT); // 녹색 LED의 긴다리 핀을 출력으로 설정
  pinMode(LED_RED_PIN_NUM, OUTPUT); // 빨간색 LED의 긴다리 핀을 출력으로 설정
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

    setLed(true, false); // 녹색 LED를 켭니다.
    waitingCount = 0; // 기다린 횟수를 0로 만듭니다.
    isMoving = true; // 주행중 상태로 변경합니다.
  } else {
    waitCar();
  }
  delay(CHECK_INTERVAL); // CHECK_INTERVAL 만큼 대기
}

void waitCar() {
  Serial.print(isMoving); //터미널 작동 확인용 문자열
  Serial.print(" waiting "); //터미널 작동 확인용 문자열
  Serial.println(waitingCount); //터미널 작동 확인용 문자열

  if (isMoving) { // 주행중 상태인지 체크합니다.
    driveCarForward(MOTOR_SPEED_0); //자동차를 정지합니다.

    setLed(true, true); // 빨간색 LED를 켭니다.

    makeBeep(); // 삐- 소리를 짧게 재생합니다.

    waitingCount = 1; // 기다린 횟수를 1로 만듭니다.
    isMoving = false;
  } else {
    if (waitingCount < WAINTING_COUNT) {
      waitingCount = waitingCount + 1;
    } else {
      turnRight(); //자동차를 오른쪽으로 회전합니다.

      waitingCount = 0; // 기다린 횟수를 0로 만듭니다.

      isMoving = true; // 주행중 상태로 변경합니다.
    }
  }
}

void turnRight() {
  Serial.println("turnRight"); //터미널 작동 확인용 문자열

  //두 모터를 반대 방향으로 돌립니다.
  digitalWrite(MOTOR_A_a, LOW); //모터A+ LOW
  analogWrite(MOTOR_A_b, MOTOR_SPEED_3); //모터A-의 속력을 PWM 출력

  analogWrite(MOTOR_B_a, LOW); //모터B+의 속력을 PWM 출력
  digitalWrite(MOTOR_B_b, MOTOR_SPEED_3); //모터B- LOW

  delay(300); // 0.5초 동안 이동합니다.

  //모터를 정지합니다.
  digitalWrite(MOTOR_A_a, LOW); //모터A+ LOW
  analogWrite(MOTOR_A_b, MOTOR_SPEED_0); //모터A-의 속력을 PWM 출력

  analogWrite(MOTOR_B_a, MOTOR_SPEED_0); //모터B+의 속력을 PWM 출력
  digitalWrite(MOTOR_B_b, LOW); //모터B- LOW
}

void makeBeep() {
  // delay 함수가 호출되는 동안에는 다른 동작을 할 수 없기 때문에 삐- 소리를 짧게 내야합니다.
  tone(BUZZER_PIN_NUM, BUZZER_FREQUENCY); // BUZZER_FREQUENCY 주파수로 소리재생
  delay(BUZZER_DURATION); // BUZZER_DURATION 밀리세컨드 동안 소리재생
  noTone(BUZZER_PIN_NUM); // 소리재생 중지
}

void setLed(bool on, bool isRed) {
  Serial.print(on); //터미널 작동 확인용 문자열
  Serial.print(" LED "); //터미널 작동 확인용 문자열
  Serial.println(isRed); //터미널 작동 확인용 문자열

  if (!on) {
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW);
    return;
  }

  if (isRed) { // 빨간색인지 확인합니다.
    digitalWrite(LED_GREEN_PIN_NUM, LOW); // 녹색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, HIGH); // 빨간색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
  } else {
    digitalWrite(LED_GREEN_PIN_NUM, HIGH); // 녹색 LED와 연결된 핀의 출력을 HIGH로 설정합니다.
    digitalWrite(LED_RED_PIN_NUM, LOW); // 빨간색 LED와 연결된 핀의 출력을 LOW로 설정합니다.
  }
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
```

## 정리
Duration: 0:03:00

장애물을 탐지해서 주행 속도를 결정하고, LED와 Buzzer를 이용해서 빛과 소리로 상태를 알려주는 프로그램을 작성하였습니다. 상당히 복잡한 프로그램이지만 차근차근 기능을 추가하면서 완성하였습니다.

**아무리 어렵고 힘든 일이라고 차근차근 하다보면 성공할 수 있다는 것을 잊지 마세요!**

프로그램에 대해서 아주 간단하게 설명했는데, 스스로 이해해보고 또 궁금한 것은 인터넷을 찾아보면서 공부해 보세요.

- LED 회로와 Buzzer 회로를 연결해 주었습니다.
- 프로그램이 어떻게 동작하는지 프로그래밍 전에 먼저 정리해보세요.
- 복잡한 프로그램이라도 기능 별로 함수를 만들어서 사용하면 좀 더 편해요.

### 참고자료
- [블루RC카 사용설명서](https://www.devicemart.co.kr/goods/download?id=1385495&rank=1)
- [아두이노 스마트 RC카 블록코딩 메뉴얼](https://www.devicemart.co.kr/goods/download?id=1385495&rank=2)
