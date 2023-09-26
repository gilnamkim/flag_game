#include <SoftwareSerial.h>
#include <Servo.h>

int RX = 7;
int TX = 8;
SoftwareSerial bluetooth(RX, TX);

Servo rightServo;
Servo leftServo;
int rightAngle = 90;
int leftAngle = 90;
bool flagRightServo = false;
bool flagLeftServo = false;

String command = "";
String tempString = "";
String actString = "";
int tempIdx = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Serial port connect..");
  bluetooth.begin(9600);
  Serial.println("Bluetooth Start..");
  rightServo.attach(10);
  leftServo.attach(9);

  // 깃발 초기화
  rightServo.write(90);
  leftServo.write(90);
}

void loop() {
  // 작업 수행 후 깃발을 초기화 합니다.
  leftServo.write(90);
  rightServo.write(90);
  
  while(bluetooth.available()) {
    tempString = bluetooth.readStringUntil(' ');
    if(tempString == "청기" || tempString == "천기") {
      actString = bluetooth.readStringUntil(' ');
      if(actString == "올려") {
        leftAngle = 180;
        flagLeftServo = true;
      } else if(actString == "내려") {
        leftAngle = 0;
        flagLeftServo = true;
      }
    }
    if(tempString == "백기" || tempString == "밝기") {
      actString = bluetooth.readStringUntil(' ');
      if(actString == "올려") {
        rightAngle = 180;
        flagRightServo = true;
      } else if(actString == "내려") {
        rightAngle = 0;
        flagRightServo = true;
      }
    }
  }
  delay(1000);
  if(flagLeftServo == true) {
    leftServo.write(leftAngle);
    flagLeftServo = false;
  }
  if(flagRightServo == true) {
    rightServo.write(180 - rightAngle);
    flagRightServo = false;
  }
  delay(1000);
}
