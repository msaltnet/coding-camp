author: Jeong Seongmoon
summary: 멜로디를 재생하기
id: buzzer-quiz
categories: codelab
environments: Web
status: Published
feedback link: https://github.com/msaltnet/coding-camp

# Buzzer로 멜로디를 재생하기

## Overview
Duration: 0:01:00

Buzzer에 대해서 알아보고 아두이노를 통해서 Buzzer로 소리를 내는 방법에 대해서 알아봅니다.

### 사전 준비
1. 아두이노 보드
1. 아두이노와 연결 가능한 PC와 IDE
1. Buzzer 소자

### 배우게 될 것
1. Buzzer란 무엇인가
1. Buzzer와 아두이노 연결방법
1. Buzzer로 소리를 내는 프로그램 작성 및 실습

### 퀴즈!
Buzzer로 엘리제를 위하여를 재생해보자

## Buzzer란
Duration: 0:02:00

**전기가 통하면 소리가 나는 반도체 소자!**

Buzzer란 우리가 일상 생활에서 이미 많이 사용하고 있는 소자입니다. 버스 벨이나 초인종과 같은 기능으로 사용하기도 합니다.

// 이미지 
https://m.blog.naver.com/geniusus/221549772862

Buzzer가 우리가 원하는 소리를 내게 하기 위해서는 주파수의 개념을 이해해야 합니다. 주파수는 1초 동안 전파나 음파가 진동하는 횟수를 뜻합니다.

https://news.samsungsemiconductor.com/kr/%EC%8A%AC%EA%B8%B0%EB%A1%9C%EC%9A%B4-%EC%A0%84%EA%B8%B0%EC%83%9D%ED%99%9C%EC%9D%84-%EC%9C%84%ED%95%9C-%EC%A0%84%EA%B8%B0%EC%83%81%EC%8B%9D%EC%9A%A9%EC%96%B4-%EC%A3%BC%ED%8C%8C%EC%88%98/
// 주파수란

소리는 주파수에 따라서 음의 높낮이가 다르며, Buzzer에 흐르는 전류를 주파수를 변경하면 소리를 변경할 수 있습니다. Buzzer에 입력되는 전류의 주파수가 높을 수록 고음이 발생합니다.

## Buzzer로 도레미파솔라시도 소리내기
Duration: 0:05:00

Buzzer 소자는 아두이노와 바로 연결해서 사용할 수 있습니다. Buzzer의 +극을 아두이노 핀에 연결하고 -극을 GND에 연결해줍니다.

//회로도

음계마다 어떤 주파수를 갖는지는 표를 보고 확인 할 수 있습니다. 4옥타브를 기준으로 프로그램을 작성해 보겠습니다.

// 음계 주파수 이미지
https://m.blog.naver.com/geniusus/221549772862

```c
int buzzer_pin_num = 8; // 아두이노와 연결된 핀 번호
int tones_num = 8; // tones 갯수 도레미파솔라시도 8개
int tones[] = {261, 294, 330, 349, 392, 440, 494, 523}; //4옥타브 도레미파솔라시도에 해당하는 주파수

void setup() {
}

void loop() {
  for(int i = 0; i < tones_num; i++) //tones_num 만큼 반복
  {
    tone(buzzer_pin_num, tones[i]); //tones의 i번째 주파수를 재생
    delay(500); //0.5초 동안 재생
  }
  noTone(buzzer_pin_num); //재생중지
  delay(1000); //1초 대기
}
```

## Buzzer로 짧은 멜로디 재생하기
Duration: 0:05:00

도레미파솔라시도에 대한 소리를 발생시켜봤습니다. 모두 0.5초 동안 소리가 나게했는데, 이번에는 소리가 나는 시간까지 정해서 멜로디를 재생해 보겠습니다.




## Buzzer로 엘리제를 위하여 재생하기 - 퀴즈
Duration: 0:06:00


## Buzzer로 엘리제를 위하여 재생하기 - 답안
Duration: 0:06:00


<aside class="positive">
코드를 수정해서 깜빡이는 속도를 조절해 보세요. 눈으로 깜빡임을 확인할 수 있는 정도는 얼마나 될까요?
</aside>

## 정리
Duration: 0:01:00

아두이노와 브레드보드, LED, 저항을 이용해서 간단한 프로그래밍을 해보았습니다.

처음 배운것이 많아서 복잡해 보이지만 사실 매우 간단합니다.

1. LED는 전기가 흐르면 빛이 나도록 만든 반도체 소자다.
1. 반도체를 통해서 신호를 마음대로 프로그래밍 할 수 있는 전자제품을 만들 수 있다.
1. 그리고 그것들을 이용해서 LED를 깜빡거리게 할 수 있다.

![semiconductor](./img/samsung-semi.png)

### 참고
[슬기로운 전기생활을 위한 전기상식용어 ‘주파수’](https://news.samsungsemiconductor.com/kr/%EC%8A%AC%EA%B8%B0%EB%A1%9C%EC%9A%B4-%EC%A0%84%EA%B8%B0%EC%83%9D%ED%99%9C%EC%9D%84-%EC%9C%84%ED%95%9C-%EC%A0%84%EA%B8%B0%EC%83%81%EC%8B%9D%EC%9A%A9%EC%96%B4-%EC%A3%BC%ED%8C%8C%EC%88%98/)