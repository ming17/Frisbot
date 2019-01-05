#include <AccelStepper.h>
#include <MultiStepper.h>
#include <RedBot.h>
#include <Stepper.h>

//AccelStepper motor1(AccelStepper::DRIVER, 3,2);
//AccelStepper motor2(AccelStepper::DRIVER, 13,12);
AccelStepper shooter(AccelStepper::DRIVER, 8, 9);
//
//MultiStepper motors;
//
//RedBotBumper pistonLBumper(6);
//RedBotBumper pistonRBumper(7);

MultiStepper shooters;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  shooters.addStepper(shooter);
//  motor1.setMaxSpeed(6000);
//   motor1.setAcceleration(40);
//   motor2.setMaxSpeed(6000);
//   motor2.setAcceleration(40);
//   //51200 steps is 1 inch
//
//   motors.addStepper(motor1);
//   motors.addStepper(motor2);

shooter.setCurrentPosition(0);
shooter.setMaxSpeed(9000);

pinMode(8, OUTPUT);
//   motor1.setCurrentPosition(0);
//   motor2.setCurrentPosition(0);
  
}

void loop() {

//    if(pistonLBumper.read() == LOW)
//      Serial.println("Left bumper down.");
//
//    if(pistonRBumper.read() == LOW)
//      Serial.println("Right bumper down.");
    
//  if (motor.distanceToGo() == 0)
//      motor.moveTo(-motor.currentPosition());
//    motor.run();
    
  int start = 0;

  Serial.println("When you are ready enter 1 and press 'enter': ");
  while (Serial.available() == 0)
  {
    delay(1);
  }

  start = Serial.read();

  Serial.println("start: " + start);

  long pos[1] = {12800};
  shooters.moveTo(pos);
  shooters.runSpeedToPosition();
  
//  Serial.println(shooter.currentPosition());

//for(int i = 0; i < 1000; i++)
//{
//  digitalWrite(8, HIGH);
//  delay(1);
//  digitalWrite(8, LOW);
//  delay(1);
//}

//  shooter.setSpeed(9000);
//  shooter.setAcceleration(0);
//  shooter.runToNewPosition(12800);
//  delay(100);
//  shooter.runToNewPosition(0);
//  digitalWrite(6, HIGH);
//  delay(1300);
//  for(int i = 0; i < 32; i++)
//  {
//    digitalWrite(5, HIGH);
//    delay(1);
//    digitalWrite(5, LOW);
//    delay(1);
//  }
//  delay(950);
//  digitalWrite(6, LOW);

  
//   put your main code here, to run repeatedly:
//  Serial.println(motor.currentPosition());

//  motor1.setSpeed(10000);
//  motor2.setSpeed(10000);
//
// long positions [2] = {-100000, -100000};
//   
//   motors.moveTo(positions);
//   motors.runSpeedToPosition();


//
//motor1.moveTo(400);
////motor1.runToPosition();
//  while(motor1.distanceToGo() != 0)
//  {
//    motor1.runSpeedToPosition();
//  }


//  Serial.println(motor.distanceToGo());
//  if (motor.distanceToGo() == 0)
//    motor.moveTo(-motor.currentPosition());


//  motor.run();
//
//  Serial.println(motor.currentPosition());
//  Serial.println("target position: " + motor.targetPosition());
//
//  while(motor.distanceToGo() != 0)
//  {
//    motor.run();
//  }
//  
//  Serial.println(motor.currentPosition());
//  motor.setCurrentPosition(200);
//  Serial.println(motor.currentPosition());
//  motor.setCurrentPosition(0);
//  Serial.println(motor.currentPosition());
//
////  motor.moveTo(3200);
////  motor.runSpeedToPosition();
//
 // start = 0;
}
