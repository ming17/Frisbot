#include <RedBot.h>

RedBotMotors loadingMotors;

const int LOADING_TIME = 3000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

//  loadingMotors.drive(255);
//    delay(LOADING_TIME);
//    loadingMotors.drive(-255);
//    delay(LOADING_TIME);
//    loadingMotors.stop();
}

void loop() {
  int start = 0;
  // put your main code here, to run repeatedly:
  Serial.println("Enter 1 when ready to start");

  while(Serial.available() == 0) {}
  start = Serial.read() - 48;

  if(start == 1)
  {
    loadingMotors.drive(100);
    delay(LOADING_TIME);
    loadingMotors.drive(-100);
    delay(LOADING_TIME);
    loadingMotors.stop();
  }
  start = 0;
  
}
