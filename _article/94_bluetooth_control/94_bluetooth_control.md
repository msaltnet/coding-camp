author: Jeong Seongmoon
summary: 블루투스로 자동차 조종하기
id: car-bt
categories: codelab
environments: Web
status: Published
feedback link: https://github.com/msaltnet/coding-camp

# 블루투스로 자동차 조종하기

## 시작하기
Duration: 0:01:00

조립된 자동차에 블루투스 모듈을 연결하고 스마트폰 앱으로 블루투스 통신을 하면서 자동차를 조정해 봅시다.

### 사전 준비
1. 조립된 자동차와 아두이노 보드
1. 블루투스 모듈
1. 아두이노와 연결 가능한 PC와 IDE

### 배우게 될 것
1. 블루투스 모듈의 회로 구성
1. 시리얼 통신으로 자동차 조정할 수 있는 프로그래밍
1. 블루투스 통신을 이용해서 스마트폰으로 자동자를 조정하는 방법

## 시리얼 통신
Duration: 0:03:00

시리얼 통신이란 병렬 데이터의 형태를 직렬 방식으로 전환하여 데이터를 전송하는 컴퓨터 하드웨어의 일종인데, 아두이노는 간단한 시리얼 통신을 통해서 손쉽게 아두이노 IDE와 데이터를 주고 받을 수 있습니다.

아래는 간단하게 시리얼 통신을 통해서 데이터를 주고 받는 프로그램입니다. 아두이노에 업로드해보세요.

```c
void setup()
{
  Serial.begin(9600);       //시리얼 통신 초기화
  Serial.println("Hello!"); //터미널 작동 확인용 문자열
}

void loop()
{
  char input = 0; //명령어 저장용 문자형 변수

  if (Serial.available()) {//데이터가 입력되었을 때
    input = Serial.read(); //변수에 입력된 데이터 저장
    Serial.print("Input: "); //시리얼 통신으로 "Input: " 전송
    Serial.println(input); //시리얼 통신으로 입력받은 문자 전송
  }
}
```

아두이노 IDE의 시리얼 모니터를 열어서 문자를 입력하고 전송해 보세요. 아두이노가 전송 받은 문자를 다시 아두이노 IDE로 전송하는 것을 확인 할 수 있습니다.

//

## 블루투스 모듈과 스마트폰 연결
Duration: 0:03:00

이번에는 블루투스 모듈과 스마트폰을 연결해 보겠습니다. 스마트폰의 블루투스 기능을 활용해서 아두이노의 블루투스 모듈과 시리얼 통신을 하는 것입니다.

꼭 스마트 폰이 아니라 테블릿이나 PC를 사용해도 가능합니다.

우선 자동차에 블루투스 모듈을 연결하겠습니다.

사진과 같은 위치에 블루투스를 삽입합니다. 배선이 완료되지 않은 사진이므로 블루투스의 위치만 참고해주세요.

//

블루투스 모듈의 VCC와 GND를 아두이노와 연결해 줍니다. VCC는 아두이노 5V에 연결해주세요.

//

블루투스 모듈의 Rx, Tx 핀은 각각 0번, 1번에 연결해 줍니다.

//

//

블루투스 모듈이 꼽힌 상태로는 아두이노 IDE에서 업로드가 제대로 되지 않을 수 있습니다. **반드시 모듈을 빼고 업로드를 진행하세요.**

이제 스마트폰에 블루투스 시리얼 통신을 사용할 수 있는 앱을 설치해야 하는데, 여기서는 [Arduino Bluetooth Control](https://play.google.com/store/apps/details?id=com.broxcode.arduinobluetoothfree&hl=ko&gl=US)를 기준으로 설명을 하겠습니다.

//

앱을 실행하기 전에 스마트폰의 블루투스 기능과 아두이노 블루투스 모듈을 연결(페어링)해주어야 합니다.

자동차에 전원을 넣고, 블루투스 모듈에 전원이 들어가는 것을 확인한 후 스마트폰 설정에서 블루투스 모듈을 찾아서 연결해줍니다.

// 스마트폰 스크린샷

연결시에 비밀번호를 입력해야 하는데, 1234를 넣어주면됩니다.

## 블루투스로 시리얼 통신
Duration: 0:03:00

이제 스마트폰에 설치한 앱을 실행하고, 블루투스 모듈을 선택합니다.

// 선택화면

여러가지 화면이 있는데, 버튼으로 구성된 화면을 사용해서 통신을 해보겠습니다.

// 버튼화면

화면의 버튼을 누르면 버튼의 문자가 블루투스를 통해서 전송되는 것을 확인 할 수 있습니다.

//

이제 스마트폰과 아두이노가 블루투스로 서로 통신할 수 있게 되었습니다.

아두이노에 앞서 설치한 아래의 프로그램이 업로드 되어 있어야 합니다.

```c
void setup()
{
  Serial.begin(9600);       //시리얼 통신 초기화
  Serial.println("Hello!"); //터미널 작동 확인용 문자열
}

void loop()
{
  char input = 0; //명령어 저장용 문자형 변수

  if (Serial.available()) {//데이터가 입력되었을 때
    input = Serial.read(); //변수에 입력된 데이터 저장
    Serial.print("Input: "); //시리얼 통신으로 "Input: " 전송
    Serial.println(input); //시리얼 통신으로 입력받은 문자 전송
  }
}
```

## 시리얼 통신으로 자동자 조종
Duration: 0:03:00

본격적으로 자동차를 조정해보기전에 블루투스 없이 시리얼 통신으로 자동차를 조종해보겠습니다.

시리얼 통신을 통해서 문자를 수신하면 수신한 문자에 따라서 자동차가 전진, 좌/우회전, 후진, 정지하는 프로그램을 먼저 업로드 해보겠습니다.

아래 프로그램은 각각 다음의 문자를 수신하여 동작하도록 만들어졌습니다.

- 'w' -> 전진
- 'a' -> 좌회전
- 'd' -> 우회전
- 's' -> 후진
- 'x' -> 정지

아래 프로그램을 아두이노에 업로드 해주세요.

```c
#define MOTOR_A_a 3     //모터A의 +출력핀은 3번핀입니다
#define MOTOR_A_b 11    //모터A의 -출력핀은 11번핀입니다
#define MOTOR_B_a 5     //모터B의 +출력핀은 5번핀입니다
#define MOTOR_B_b 6     //모터B의 -출력핀은 6번핀입니다
#define MOTOR_SPEED 150 //모터의 기준속력입니다(0~255)

struct motor { //모터의 속력과 방향을 저장하는 구조체
    unsigned int speed;
    boolean isForward; //전진, 후진 정보
}

static struct motor motorA; //A모터의 속력과 방향을 저장하는 구조체 전역변수
static struct motor motorB; //B모터의 속력과 방향을 저장하는 구조체 전역변수

void setup()
{
  //모터 제어 핀들을 출력으로 설정합니다.
  pinMode(MOTOR_A_a, OUTPUT);
  pinMode(MOTOR_A_b, OUTPUT);
  pinMode(MOTOR_B_a, OUTPUT);
  pinMode(MOTOR_B_b, OUTPUT);

  Serial.begin(9600);       //시리얼 통신 초기화
  Serial.println("Hello!"); //터미널 작동 확인용 문자열
}

void loop()
{
  char cmd = 0; //명령어 저장용 문자형 변수

  if (Serial.available()) //데이터가 입력되었을 때
  {
    cmd = Serial.read(); //변수에 입력된 데이터 저장
    updateMotorControl(cmd); //입력된 데이터에 따라 모터에 입력될 변수를 조정하는 함수
  }
  driveCar(); //모터를 구동하는 함수
}

void updateMotorControl(char cmd) //입력된 데이터에 따라 모터에 입력될 전역변수를 변경하는 함수
{
  if(cmd == 'w')  //'w'가 입력되었을 때, 전진
  {
    motorA.isForward = true; //모터A 정방향
    motorB.isForward = true; //모터B 정방향
    motorA.speed = MOTOR_SPEED;  //모터A의 속력값 조정
    motorB.speed = MOTOR_SPEED;  //모터B의 속력값 조정
  }
  else if(cmd == 'a')  //'a'가 입력되었을 때, 제자리 좌회전
  {
    motorA.isForward = false;  //모터A 역방향
    motorB.isForward = true;  //모터B 정방향
    motorA.speed = MOTOR_SPEED;  //모터A의 속력값 조정
    motorB.speed = MOTOR_SPEED;  //모터B의 속력값 조정
  }
  else if(cmd == 'd')  //'d'가 입력되었을 때, 제자리 우회전
  {
    motorA.isForward = true;  //모터A 정방향
    motorB.isForward = false;  //모터B 역방향
    motorA.speed = MOTOR_SPEED;  //모터A의 속력값 조정
    motorB.speed = MOTOR_SPEED;  //모터B의 속력값 조정
  }
  else if(cmd == 's')  //'s'가 입력되었을 때, 후진
  {
    motorA.isForward = false;  //모터A 역방향
    motorB.isForward = false;  //모터B 역방향
    motorA.speed = MOTOR_SPEED;  //모터A의 속력값 조정
    motorB.speed = MOTOR_SPEED;  //모터B의 속력값 조정
  }
  else if(cmd == 'x')
  {
    motorA.isForward = true;  //모터A 정방향
    motorB.isForward = true;  //모터B 정방향
    motorA.speed = 0;  //모터A의 정지
    motorB.speed = 0;  //모터B의 정지
  }
}

void driveCar()  //모터를 구동하는 함수
{
  if(motorA.isForward)
  {
    digitalWrite(MOTOR_A_a, LOW); //모터A+ LOW
    analogWrite(MOTOR_A_b, motorA.speed); //모터A-의 속력을 PWM 출력
  }
  else
  {
    analogWrite(MOTOR_A_a, motorA.speed); //모터A+의 속력을 PWM 출력
    digitalWrite(MOTOR_A_b, LOW); //모터A- LOW
  }
  if(!motorB.isForward) //방향이 반대이므로 A모터와 a,b 출력을 반대로 해줘야 함
  {
    digitalWrite(MOTOR_B_a, LOW); //모터B+ LOW
    analogWrite(MOTOR_B_b, motorB.speed); //모터B-의 속력을 PWM 출력
  }
  else
  {
    analogWrite(MOTOR_B_a, motorB.speed); //모터B+의 속력을 PWM 출력
    digitalWrite(MOTOR_B_b, LOW); //모터B- LOW
  }
}
```

프로그램을 업로드하고 아두이노 IDE의 실리얼 모니터를 사용해서 `w`, `a`, `s`, `d`, `x`문자를 전송해서 자동차를 조종해보세요.

## 스마트폰으로 자동차 조종하기
Duration: 0:03:00

이제 스마트폰으로 조종하는 것만 남았습니다. 앞서 사용한 프로그램은 시리얼 통신을 통해서 자동차를 조종하는 프로그램인데요, 스마트폰을 사용할 때도 그대로 사용할 수 있습니다.

**스마트폰으로도 동일하게 시리얼 통신으로 문자를 전송하여 자동차를 조종하는 것이기 때문입니다.**

업데이트를 완료하고, 아두이노 IDE와 케이블 연결을 분리해주세요.

블루투스 모듈을 브레드보드에 연결해주세요. 배선이 잘 맞는지 확인하면서 연결해주세요.

//

스마트폰 앱을 실행하고, 버튼의 설정 값을 `w`, `a`, `s`, `d`, `x`문자로 변경해 주세요.

문자를 입력하는 대신 버튼을 눌러서 문자가 전송되도록 매칭을 시켜주는 것입니다.

원하는 버튼과 매칭해서 설정을 한 후에는 버튼으로 자동차를 조종할 수 있습니다.

## 정리
Duration: 0:03:00

시리얼 통신에 대해서 알아보았고, 블루투스를 이용하여 스마트폰과 아두이노가 시리얼 통신을 하면서 자동차를 조종할 수 있게되었습니다.

- 시리얼 통신으로 수신한 문자에 따라서 자동차를 움직이는 프로그램을 만들 수 있다.
- 스마트폰의 블루투스 기능과 앱을 사용해서 아두이노와 시리얼 통신을 할 수 있다.
- 스마트폰으로 시리얼 통신을 통해 자동차를 무선으로 조종할 수 있다.

### 참고자료
[블루RC카 사용설명서](https://www.devicemart.co.kr/goods/download?id=1385495&rank=1)
[아두이노 스마트 RC카 블록코딩 메뉴얼](https://www.devicemart.co.kr/goods/download?id=1385495&rank=2)
