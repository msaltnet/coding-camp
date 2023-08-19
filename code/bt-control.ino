#define MOTOR_A_a 3     //모터A의 +출력핀은 3번핀입니다
#define MOTOR_A_b 11    //모터A의 -출력핀은 11번핀입니다
#define MOTOR_B_a 5     //모터B의 +출력핀은 5번핀입니다
#define MOTOR_B_b 6     //모터B의 -출력핀은 6번핀입니다
#define MOTOR_SPEED 150 //모터의 기준속력입니다(0~255)

struct motor { //모터의 속력과 방향을 저장하는 구조체
  unsigned int speed;
  boolean isForward; //전진, 후진 정보
};

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
    Serial.print(cmd);
    Serial.println(" 커맨드 수신 완료!");
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