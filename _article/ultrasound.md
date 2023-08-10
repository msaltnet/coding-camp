author: Jeong Seongmoon
summary: 초음파 센서로 LED 점등 시켜보기
id: ultrasound
categories: codelab
environments: Web
status: Published
feedback link: https://github.com/msaltnet/coding-camp

# 초음파 센서로 LED 점등 시켜보기

## Overview
Duration: 0:01:00

초음파 센서에 대해서 알아보고 아두이노를 통해서 초음파로 거리를 측정하여 LED를 깜빡이는 방법에 대해서 설명한다.

### 사전 준비
1. 아두이노 보드
1. 아두이노와 연결 가능한 PC와 IDE
1. 브레드보드
1. LED 소자
1. 저항 220옴
1. 초음파 센서

### 배우게 될 것
1. 초음파란 무엇인가
1. LED와 저항의 연결 방법
1. LED를 깜빡이는 프로그램 작성 및 실습


## 초음파란
Duration: 0:02:00

초음파는 일반적으로 사람들이 들을 수 있는 소리보다 높은 주파수의 음파를 뜻합니다.

> 초음파(超音波, 영어: ultrasound(s), ultrasonic wave)는 인간이 들을 수 있는 가청 최대 한계 범위를 넘어서는 주파수를 갖는 주기적인 '음압'(音壓, sound pressure)을 의미한다. 비록, 이러한 한계값이 사람마다 다르지만, 건강한 젊은 사람의 경우 이 값은 약 20kHz(20,000 Hz)이고 따라서 20kHz는 초음파를 설명하는 데 있어 유용한 하한(下限)이 된다. - 위키백과

https://ko.wikipedia.org/wiki/%EC%B4%88%EC%9D%8C%ED%8C%8C

// 돌고래

돌고래가 내는 소리를 사람이 못 듣고, 젊은 사람들이 듣는 소리를 노인들이 못듣기도 합니다.

// 초음파 검사 및 관련 그림


## 초음파 센서
Duration: 0:03:00

초음파 센서는 초음파를 보낸후 반사되어 돌아오는 시간차를 측정해서 거리를 알 수 있는 센서로 초음파를 이용한 일종의 `거리 측정 센서` 입니다.

전방으로 발사된 초음파는 금속, 목재, 유리, 종이 등 단단한 물체에는 거의 100% 반사되어 돌아오지만 옷감과 같은 일부물질은 초음파를 흡수하기 때문에 정확한 측정값이 어렵다는 단점이 있습니다.

// 이미지

https://m.blog.naver.com/boilmint7/220926404472


왼쪽에 동그란 부분(TRIG)에서 초음파가 발생되고 , 오른쪽 부분(ECHO)에서 반사되어 돌아오는 초음파를 받습니다. 핀맵은 좌측부터 VCC,TRIG,ECHO,GND 입니다.

- 측정범위 : 2cm ~ 4M
- 측정각도 : 15도
- 사용전압 : 5V
- 사용전류 : 15mA

TRIG에 신호를 보내서 초음파를 출력하고, ECHO에 들어오는 신호를 입력으로 받아서 출력과 입력의 시간차이로 거리를 측정합니다.

## 초음파 센서부터 장애물까지 거리 측정 방법
Duration: 0:03:00

초음파 센서로부터 앞에 장애물까지 거리를 계산하는 방법은 과학시간에 배운 속도와 거리 공식을 사용합니다. (초등 5학년 2학기 4단원 물체의 운동)

물체의 이동 거리 = 물체의 속도 x 시간

우리가 사용하는 초음파의 속도는 340(m/s)으로 **음속**이라고 합니다. 따라서 아래 공식으로 초음파가 이동한 거리를 계산할 수 있습니다.

초음파가 이동한 거리 = 음속 340(m/s) x 시간(s)

이제 초음파 신호를 발사하고 나서 돌아온 시간을 알면 초음파가 이동한 거리를 알 수 있습니다.

그리고, 초음파는 초음파 센서부터 장애물까지 갔다가 돌아오므로 이동한 거리를 2로 나누면 초음파 센서부터 장애물까지의 거리가 됩니다.

센서부터 장애물까지 거리 = 초음파가 이동한 거리 / 2

계산을 할 때는 시간과 거리의 단위를 정확하게 변환해서 계산해야 합니다.

## 초음파 센서부터 장애물까지 거리 측정 해보기
Duration: 0:05:00

이제 실제로 초음파 센서부터 장애물까지의 거리를 측정해 보겠습니다.

초음파 센서의 4개의 핀을 각각 다음과 같이 연결되도록 합니다.
- 초음파 센서 VCC -> 아두이노 5V
- 초음파 센서 GND -> 아두이노 GND
- 초음파 센서 TRIG -> 아두이노 PIN 9
- 초음파 센서 ECHO -> 아두이노 PIN 8

아래와 같이 회로를 구성해 주세요.

//회로도

아두이노 IDE를 실행해서 아래 코드를 입력해 주세요. 코드의 설명은 주석으로 달아놨으니 나중에 천천히 이해해 보세요.

```c
#define TRIG 9 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 8 //ECHO 핀 설정 (초음파 받는 핀)

void setup() {
  Serial.begin(9600); //PC와 

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); // 0.000002초 대기, 센서의 동작을 기다림

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);  // 0.00001초 대기, 센서의 동작을 기다림

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  // Returns the length of the pulse in microseconds or gives up and returns 0 if no complete pulse was received within the timeout.
  // 34000 * 초음파가 물체로 부터 반사되어 돌아오는시간 / 1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
  // 초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.

  distance = duration * 17 / 1000; 

  // PC모니터로 초음파 거리값을 확인 하는 코드 입니다.
  Serial.println(duration ); // 초음파가 반사되어 돌아오는 시간을 보여줍니다.
  Serial.print("\nDIstance : ");
  Serial.print(distance); // 측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" cm");

  delay(1000); // 1초 마다 측정값을 보여줍니다.
}
```

업로드를 진행합니다. PC모니터를 통해서 값을 확인할수 있도록 `시리얼모니터` 버튼을 눌러줍니다.

//이미지

아래 사진처럼 손바닥과 초음파센서의 거리를 측정해보며, PC에 측정된 거리가 잘 나오는지 확인합니다.

// 이미지

## 초음파 센서부터 장애물까지 거리 측정해서 LED 깜빡이기
Duration: 0:02:00

이번에는 앞에서 배운 LED 깜빡이기와 함께 회로를 구성해보겠습니다.

장애물의 거리를 5단계로 나눠서 LED의 깜빡임 속도를 변경해 보겠습니다.

앞에서 구성한 회로에 LED와 저항을 추가합니다.

LED는 7번 핀으로 연결해서 컨트롤해보겠습니다.

// 회로도

```c
#define TRIG 9 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 8 //ECHO 핀 설정 (초음파 받는 핀)

void setup() {
  Serial.begin(9600); //PC와 

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop()
{
  long duration, distance;

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); // 0.000002초 대기, 센서의 동작을 기다림

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);  // 0.00001초 대기, 센서의 동작을 기다림

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH); //물체에 반사되어돌아온 초음파의 시간을 변수에 저장합니다.
  // Returns the length of the pulse in microseconds or gives up and returns 0 if no complete pulse was received within the timeout.
  // 34000 * 초음파가 물체로 부터 반사되어 돌아오는시간 / 1000000 / 2(왕복값이아니라 편도값이기때문에 나누기2를 해줍니다.)
  // 초음파센서의 거리값이 위 계산값과 동일하게 Cm로 환산되는 계산공식 입니다. 수식이 간단해지도록 적용했습니다.

  distance = duration * 17 / 1000; 

  // PC모니터로 초음파 거리값을 확인 하는 코드 입니다.
  Serial.println(duration ); // 초음파가 반사되어 돌아오는 시간을 보여줍니다.
  Serial.print("\nDIstance : ");
  Serial.print(distance); // 측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" cm");

  delay(1000); // 1초 마다 측정값을 보여줍니다.
}
```

## 정리


