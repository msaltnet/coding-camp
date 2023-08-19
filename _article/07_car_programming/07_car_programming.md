author: Jeong Seongmoon
summary: 장애물을 인식 자동차 프로그래밍
id: car-programming
categories: codelab
environments: Web
status: Published
feedback link: https://github.com/msaltnet/coding-camp

# 장애물을 인식 자동차 프로그래밍

## 시작하기
Duration: 0:01:00

조립된 자동차가 장애물을 인식해서 속도를 변경하도록 프로그래밍을 해봅시다.

### 사전 준비
1. 조립된 자동차와 아두이노 보드
1. 아두이노와 연결 가능한 PC와 IDE

### 배우게 될 것
1. 장애물과의 거리를 측정해서 자동차의 속도를 결정하는 방법
1. 결정된 속도로 자동차를 전진하는 방법

## 프로그램의 전체 동작 설명
Duration: 0:03:00

프로그램의 전체 동작을 간단하게 정리하면 다음과 같습니다.

1. 초음파 센서로 장애물과의 거리를 측정한다.
1. 거리에 따라 속도를 다르게 한다.
1. 잠시 기다렸다가 반복한다.

세부 동작을 포함한 순서도는 아래와 같습니다. 매우 복잡해 보이지만 하나씩 차근차근 만들면 완성할 수 있습니다.

//순서도

## 앞으로 이동하기
Duration: 0:05:00

우선 자동차를 앞으로 이동하는 부분만 먼저 구현을 해보겠습니다.

전달 받은 속력으로 앞으로 이동하는 함수를 `driveCarForward`로 만들어서 `loop`에서 실행해주었습니다.

다음과 같이 프로그램을 구성해서 업로드를 하고, 동작을 확인해 봅니다.

코드 내용은 천천히 혼자 스스로 이해해보세요.

```c
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
}

void loop() { //loop는 계속 반복 실행되는 함수 입니다.
  //정해진 속도로 전진하기
  driveCarForward(MOTOR_SPEED_3);
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

## 거리가 가까울 때 정지하기
Duration: 0:05:00

이번에는 초음파 센서로부터 거리를 측정하고, 거리가 가까운 경우 자동차를 정지하는 프로그램을 만들어 보겠습니다.

거리를 측정하는 부분은 앞에서 배운 내용을 그대로 다시 사용합니다. `getDistance`를 동일하게 사용합니다.

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
    //정해진 속도로 전진하기
    driveCarForward(MOTOR_SPEED_3);
  } else {
    waitCar();
  }
  delay(CHECK_INTERVAL); // CHECK_INTERVAL 만큼 대기
}

void waitCar() {
  driveCarForward(MOTOR_SPEED_0); //자동차를 정지합니다.
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

<aside class="positive">
코드를 수정해서 거리를 바꿔서 프로그램을 만들어 보세요.
</aside>

## 거리에 따라 속도를 다르게 이동하기
Duration: 0:05:00

이번에는 초음파 센서로부터 거리를 측정하고, 거리에 따라 속도를 다르게 이동하도록 프로그램을 만들어 보겠습니다.

거리를 측정한 다음 측정된 거리에 따라 속력을 결정하는 `getSpeed` 함수를 만들었습니다.

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
```

<aside class="positive">
코드를 수정해서 거리와 속도를 바꿔서 프로그램을 만들어 보세요.
</aside>

## 정리
Duration: 0:03:00

초음파 센서를 사용해서 장애물을 탐지해서 거리가 가까운 경우 정지하도록 하였습니다. 그리고 거리에 따라 주행 속도를 바꿔서 주행하는 프로그램을 작성하였습니다. 상당히 복잡한 프로그램이지만 차근차근 기능을 추가하면서 완성하였습니다.

**아무리 어렵고 힘든 일이라고 차근차근 하다보면 성공할 수 있다는 것을 잊지 마세요!**

프로그램에 대해서 아주 간단하게 설명했는데, 스스로 이해해보고 또 궁금한 것은 인터넷을 찾아보면서 공부해 보세요.

- 프로그램이 어떻게 동작하는지 프로그래밍 전에 먼저 정리해보세요.
- 복잡한 프로그램이라도 기능 별로 함수를 만들어서 사용하면 좀 더 편해요.

### 참고자료
- [블루RC카 사용설명서](https://www.devicemart.co.kr/goods/download?id=1385495&rank=1)
- [아두이노 스마트 RC카 블록코딩 메뉴얼](https://www.devicemart.co.kr/goods/download?id=1385495&rank=2)
