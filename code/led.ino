#define LED_PIN_NUM 8 // LED의 긴다리 핀과 연결된 아두이노 핀 번호 (+핀)

void setup() { //setup은 처음 한 번 실행되는 함수 입니다.
  pinMode(LED_PIN_NUM, OUTPUT); // LED의 긴다리 핀을 출력으로 설정
}

void loop() { //loop는 계속 반복 실행되는 함수 입니다.
  digitalWrite(LED_PIN_NUM, HIGH); // LED와 연결된 핀에 전압을 5V로 설정
  delay(1000); // 1초(1000밀리초) 동안 대기
  digitalWrite(LED_PIN_NUM, LOW); // LED와 연결된 핀에 전압을 0V로 설정
  delay(1000);
}