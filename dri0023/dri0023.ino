#include <TimerThree.h>
#include <TimerOne.h>

int buttonpin = 9;

int m1stp = 6;  //첫벗째 스텝모터의 stp를 5번핀에 연결합니다.
int m1dir = 7;  //첫번째 스텝모터의 dir를 4번핀에 연결합니다.
int m2stp = 5;  //두번째 스텝모터의 stp를 6번핀에 연결합니다.
int m2dir = 4;  //두번째 스텝모터의 dir을 7번핀에 연결합니다.

int dir1 = 0;
long position1 = 0;

int dir2 = 0;
long position2 = 0;

void stepper1Callback() {
  if(dir1 == -1 || dir1 == 1) {
    digitalWrite(m1stp, HIGH); //stp를 HIGH로 출력하고,
    delayMicroseconds(2);
    digitalWrite(m1stp, LOW); //stp를 LOW로 출력합니다.
    position1 += dir1;
  }
}

void stepper2Callback() {
  if(dir2 == -1 || dir2 == 1) {
    digitalWrite(m2stp, HIGH); //stp를 HIGH로 출력하고,
    delayMicroseconds(2);
    digitalWrite(m2stp, LOW); //stp를 LOW로 출력합니다.
    position2 += dir2;
  }
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);//시리얼통신을 시작합니다.
  pinMode(m1stp, OUTPUT);//m1stp를 출력으로 설정합니다.
  pinMode(m1dir, OUTPUT);//m1dir을 출력으로 설정합니다.    
  pinMode(m2stp, OUTPUT);//m2stp를 출력으로 설정합니다.
  pinMode(m2dir, OUTPUT);//m2dir을 출력으로 설정합니다.
  
  Timer1.initialize(5000);
  Timer1.attachInterrupt(stepper1Callback);
  
  Timer3.initialize(5000);
  Timer3.attachInterrupt(stepper2Callback); 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Forward!!!");
  digitalWrite(m1dir, HIGH);
  dir1 = 1;
  while(position1 < 200) {
    Timer1.setPeriod(700);
  }

  Serial.println("Stop!!!");
  dir1 = 0;
  delay(1000);

  Serial.println("Inverse!!!");
  digitalWrite(m1dir, LOW);
  dir1 = -1;
  while(position1 > 0) {
    Timer1.setPeriod(700);
  }

  Serial.println("Stop!!!");
  dir1 = 0;
  delay(1000);
}
