#define NOTE_C4  262 //4옥타브 도에 해당하는 주파수
#define NOTE_CS4 277 //4옥타브 도샾에 해당하는 주파수 
#define NOTE_D4  294 //4옥타브 레에 해당하는 주파수
#define NOTE_DS4 311 //4옥타브 레샵에 해당하는 주파수
#define NOTE_E4  330 //4옥타브 미에 해당하는 주파수
#define NOTE_F4  349 //4옥타브 파에 해당하는 주파수
#define NOTE_FS4 370 //4옥타브 파샵에 해당하는 주파수
#define NOTE_G4  392 //4옥타브 솔에 해당하는 주파수
#define NOTE_GS4 415 //4옥타브 솔샵에 해당하는 주파수
#define NOTE_A4  440 //4옥타브 라에 해당하는 주파수
#define NOTE_AS4 466 //4옥타브 라샵에 해당하는 주파수
#define NOTE_B4  494 //4옥타브 시에 해당하는 주파수
#define NOTE_C5  523 //5옥타브 도에 해당하는 주파수
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976

#define MUTE 0 //무음 처리를 위해서 추가

#define DURTION_WHOLE     0
#define DURTION_HALF      400
#define DURTION_QUARTER   200
#define DURTION_EIGHTH    100
#define DURTION_SIXTEENTH 50

struct sound {
  int tone;
  int durationMs;
};

#define BUZZER_PIN_NUM 8//아두이노와 연결된 핀 번호
struct sound soundList[] = { //주파수와 음의 길이 정보를 갖는 구조체의 배열
  {NOTE_G4, DURTION_QUARTER},
  {NOTE_A4, DURTION_QUARTER + DURTION_EIGHTH},
  {MUTE,    DURTION_SIXTEENTH},
  {NOTE_B4, DURTION_QUARTER + DURTION_EIGHTH},
  {MUTE,    DURTION_SIXTEENTH},
  {NOTE_E5, DURTION_QUARTER},
  {NOTE_D5, DURTION_HALF + DURTION_EIGHTH}
};
int soundListCount = 7;

void setup() {
  Serial.begin(9600); //PC와 시리얼 통신을 설정
}

void loop() {
  for(int i = 0; i < soundListCount; i++) //soundListCount 만큼 반복
  {
    if (soundList[i].tone == MUTE) { //무음인 경우
      noTone(BUZZER_PIN_NUM);
    } else {
      tone(BUZZER_PIN_NUM, soundList[i].tone); //soundList의 i번째 주파수를 재생
    }
    delay(soundList[i].durationMs); //1초 대기
  }
  noTone(BUZZER_PIN_NUM); //재생중지
  delay(1000); //1초 대기
}