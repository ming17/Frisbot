#include <AccelStepper.h>
#include <MultiStepper.h>
#include <RedBot.h>
#include <string.h>

#define stpL 3
#define dirL 2
#define stpR 13
#define dirR 12
//#define stpT 9 ROTATION
//#define dirT 8 ROTATION
#define bumpPistL 6
#define bumpPistR 11
//#define bumpTurn 4 ROTATION
#define stpS 8
#define dirS 9

const int stepsPerRevolution = 200;
const int STEPS_PER_INCH = 51200;
const int LOADING_TIME = 100;
//const long TURN_22_L = -1000; ROTATION
//const long TURN_45_L = -2000; ROTATION
//const long TURN_22_R = 200; ROTATION
//const long TURN_45_R = 400; ROTATION
const long ANGLE_HALF_DIFFERENCE = 51200;
const long ANGLE_FULL_DIFFERENCE = 102400;
const long LEVEL_HEIGHT = 51200;
const long LOW_HEIGHT = 102400;
const long MED_HEIGHT = 204800;
const long HIGH_HEIGHT = 307200;

AccelStepper pistonL(AccelStepper::DRIVER, stpL, dirL);
AccelStepper pistonR(AccelStepper::DRIVER, stpR, dirR);
//AccelStepper willTurner(AccelStepper::DRIVER, stpT, dirT); ROTATION
AccelStepper shooter(AccelStepper::DRIVER, stpS, dirS);
MultiStepper pistons;
MultiStepper shoots;

RedBotBumper pistonLBumper(bumpPistL);
RedBotBumper pistonRBumper(bumpPistR);

void setup() {
  Serial.begin(9600);
  
  pistonL.setMaxSpeed(16000);
  pistonR.setMaxSpeed(16000);
  //willTurner.setMaxSpeed(1000); ROTATION
  //willTurner.setAcceleration(50); ROTATION
  pistons.addStepper(pistonL);
  pistons.addStepper(pistonR);
  shoots.addStepper(shooter);
  shooter.setMaxSpeed(9000);

  pistonL.setCurrentPosition(0);
  pistonR.setCurrentPosition(0);
  //willTurner.setCurrentPosition(0); ROTATION
  shooter.setCurrentPosition(0);
}

void loop() {
  int rot = 3;
  int height = 2;
  int tilt = 3;
  int frequency = 5;
  int numThrows = 10;

 // bumperTest(); //TESTING
  
 // STANLEY "THE INVISIBLE MAN" UMEWENI
 
  //testing(); //TESTING

  Serial.println("Welcome to Frisbot! Please enter your required settings and enjoy!");
  
  Serial.println("First enter a number (1-5) to decide how much to turn the shooter. \nThe default setting is '3'.\n");
//  Serial.println("1) Enter a '1' to point the shooter 45 degrees to the left.");
//  Serial.println("2) Enter a '2' to point the shooter 22 degrees to the left.");
//  Serial.println("3) Enter a '3' to point the shooter straight.");
//  Serial.println("4) Enter a '4' to point the shooter 22 degrees to the right.");
//  Serial.println("5) Enter a '5' to point the shooter 45 degrees to the right.");

  while(Serial.available() == 0) {}
  rot = Serial.read() - '0';

  Serial.println("\nNow enter a number (1-5) to determine the tilt of the launcher, \npointing the left edge or the right edge of the frisbee up or down. \nThere are two different angles, a large angle and a small angle. \nThe default setting is '3'.\n");
//  Serial.println("1) Enter a '1' to angle the shooter with the left edge pointing down at a large angle.");
//  Serial.println("2) Enter a '2' to angle the shooter with the left edge pointing down at a small angle.");
//  Serial.println("3) Enter a '3' to angle the shooter straight.");
//  Serial.println("4) Enter a '4' to angle the shooter with the right edge pointing down at a small angle.");
//  Serial.println("5) Enter a '5' to angle the shooter with the right edge pointing down at a large angle.");

  while(Serial.available() == 0) {}
  tilt = Serial.read() - '0';

  Serial.println("\nNow enter a number (1-5) to determine the angle of the launcher, \npointing the front edge of the frisbee up. \nThe default setting is '2'.\n");
//  Serial.println("1) Enter a '1' to point the shooter slightly down.");
//  Serial.println("2) Enter a '2' to point the shooter level with the ground.");
//  Serial.println("3) Enter a '3' to point the shooter at a slight upward angle.");
//  Serial.println("4) Enter a '4' to point the shooter at a medium upward angle.");
//  Serial.println("5) Enter a '5' to point the shooter at a large upward angle.");

  while(Serial.available() == 0) {}
  height = Serial.read() - '0';

  frequency = getFrequency();
  numThrows = getNumThrows();

  Serial.println("\nWhen you are ready to start press '1' and hit 'enter'.");
  while(Serial.available() == 0) {};

  rotate(rot);
  changeAngle(height, tilt);
  //Serial.println(frequency); TESTING
  for(int thro = 0; thro < numThrows; thro++)
  {
    shoot();
    delay(1000 * frequency);
  }

  resetPosition();
}

void testing()
{
  int test = 0;
  int rot = 3;
  int height = 2;
  int tilt = 3;
  int tryAgain = 1;
  String toPrint = "";
  
  while (tryAgain == 1)
  {
    toPrint = pistonL.currentPosition();
    toPrint += " ";
    toPrint += pistonR.currentPosition();
    toPrint += " ";
//    toPrint += willTurner.currentPosition();
    Serial.println(toPrint); 
    Serial.println("Testing.\nEnter 1 to test shoot.\nEnter 2 to test rotate.\nEnter 3 to test changeAngle.\nEnter 4 to test resetPosition.");
  
    while(Serial.available() == 0) {}
    test = Serial.read() - '0';
    Serial.println(test);

//    if(pistonLBumper.read() == LOW)
//    {
//      Serial.println("Left Bumper down.");
//      //digitalWrite(bumpPistL, HIGH);
//    }
//    if(pistonRBumper.read() == LOW)
//    {
//      Serial.println("Right Bumper down.");
//    }
    
    switch (test)
    {
      case 1:
        shoot();
        break;
      case 2:
        Serial.println("Enter number for rotation");
        while(Serial.available() == 0) {}
        rot = Serial.read() - '0';
        toPrint = "rotate: ";
        toPrint += rot;
        Serial.println(toPrint);
        rotate(rot);
        break;
      case 3:
        Serial.println("Enter number for height and tilt");
        while(Serial.available() == 0) {}
        height = Serial.read() - '0';
        while(Serial.available() == 0) {}
        tilt = Serial.read() - '0';
        toPrint = "height: ";
        toPrint += height;
        toPrint += " tilt: ";
        toPrint += tilt;
        Serial.println(toPrint);
        changeAngle(height, tilt);
        break;
      case 4:
        resetPosition();
        break;
    }

    Serial.println("If you want to try again enter 1.");
    while(Serial.available() == 0) {}
    tryAgain = Serial.read() - '0';
  }
  
}

void shoot()
{
  long pos[1] = {12800};
  shoots.moveTo(pos);
  shoots.runSpeedToPosition();
  delay(100);
  pos[0] = 0;
  shoots.moveTo(pos);
  shoots.runSpeedToPosition();
  Serial.println("shoot");
}

void rotate(int direction) //ROTATION
{
  String turnTestPrint = " "; //TESTING
  switch (direction)
  {
    case 1: 
      turnTestPrint += " 1 "; //USED FOR TESTING
//      willTurner.moveTo(TURN_45_L);
      break;
    case 2:
      turnTestPrint += " 2 "; //USED FOR TESTING
//     willTurner.moveTo(TURN_22_L);
      break;
    case 3:
      turnTestPrint += " 3 "; //USED FOR TESTING
      break;
    case 4:
      turnTestPrint += " 4 "; //USED FOR TESTING
//      willTurner.moveTo(TURN_22_R);
      break;
    case 5:
      turnTestPrint += " 5 "; //USED FOR TESTING
//      willTurner.moveTo(TURN_45_R);
      break;
  }

//  willTurner.setSpeed(100);
//  while(willTurner.distanceToGo() != 0)
  {
//  willTurner.runSpeedToPosition();
  }
}

void changeAngle(int height, int tilt)
{
  String angleTestPrint = " ";
  
  long difference = 0;
  long newPositions [2] = {0,0};
  
  switch (tilt)
  {
    case 1:
      difference = -ANGLE_FULL_DIFFERENCE;
      break;
    case 2:
      difference = -ANGLE_HALF_DIFFERENCE;
      break;
    case 3:
      difference = 0;
      break;
    case 4:
      difference = ANGLE_HALF_DIFFERENCE;
      break;
    case 5:
      difference = ANGLE_FULL_DIFFERENCE;
      break;
  }

  angleTestPrint = "\ndifference: ";  
  angleTestPrint += difference;  
  
  switch (height)
  {
    case 1:
      angleTestPrint+=" 1 ";  
      if(difference < 0)
      {
        newPositions[1] = abs(difference);
      }
      else
      {
        newPositions[0] = difference;
      }
      break;
    case 2:
      angleTestPrint +=" 2 ";  
      if(difference < 0)
      {
        newPositions[0] = LEVEL_HEIGHT - (abs(difference) / 2);
        newPositions[1] = LEVEL_HEIGHT + (abs(difference) / 2);
      }
      else 
      {
        newPositions[0] = LEVEL_HEIGHT + difference / 2;
        newPositions[1] = LEVEL_HEIGHT - difference / 2;
      }
      break;
    case 3:
      angleTestPrint += " 3 ";  
      if(difference < 0)
      {
        newPositions[0] = LOW_HEIGHT - (abs(difference) / 2);
        newPositions[1] = LOW_HEIGHT + (abs(difference) / 2);
      }
      else 
      {
        newPositions[0] = LOW_HEIGHT + difference / 2;
        newPositions[1] = LOW_HEIGHT - difference / 2;
      }
      break;
    case 4:
      angleTestPrint += " 4 ";  
      if(difference < 0)
      {
        newPositions[0] = MED_HEIGHT - (abs(difference) / 2);
        newPositions[1] = MED_HEIGHT + (abs(difference) / 2);
      }
      else 
      {
        newPositions[0] = MED_HEIGHT + difference / 2;
        newPositions[1] = MED_HEIGHT - difference / 2;
      } 
      break;
    case 5:
      angleTestPrint += " 5 ";  
      if(difference < 0)
      {
        newPositions[0] = HIGH_HEIGHT - (abs(difference) / 2);
        newPositions[1] = HIGH_HEIGHT + (abs(difference) / 2);
      }
      else 
      {
        newPositions[0] = HIGH_HEIGHT + difference / 2;
        newPositions[1] = HIGH_HEIGHT - difference / 2;
      }
      break;

  }
  angleTestPrint += "\nnew positions are L: "; 
  angleTestPrint += newPositions[0];
  angleTestPrint += " and R: "; 
  angleTestPrint += newPositions[1]; 

  //Serial.println(angleTestPrint); TESTING
  pistons.moveTo(newPositions);
  pistons.runSpeedToPosition();
}

int getFrequency()
{
  Serial.println("\nHow much time would you like in between throws? Enter a time in seconds from 1 to 60: ");
  while (Serial.available() == 0) {}

  int freq = Serial.read() - '0';
  return freq;
}

int getNumThrows()
{
  int numThrows = 10;
  
  Serial.println("\nHow many discs would you like to be thrown? Enter a number from 0 to 30. If you would like the robot to throw continuously enter 0: ");
  while (Serial.available() == 0) {}

  int response = Serial.read() - '0';
  if(response == 0)
    numThrows = 99999;
  else
    numThrows = response;

  return numThrows;
}

void resetPosition()
{
  long tempPositions [2] = {-pistonL.currentPosition(),-pistonR.currentPosition()};  
  pistons.moveTo(tempPositions);
  //willTurner.moveTo(0); ROTATION

//  while(willTurner.distanceToGo() != 0)
//  {
//    if(digitalRead(bumpTurn) == LOW)
//    {
//      willTurner.stop();
//      willTurner.setCurrentPosition(0);
//      willTurner.moveTo(0);
//    }
//
//    willTurner.run();
//  }

  while(pistonL.distanceToGo() != 0 || pistonR.distanceToGo() != 0)
  {
    if(pistonLBumper.read() == LOW)
    {
      pistonL.stop();
      pistonL.setCurrentPosition(0);
      pistonL.moveTo(0);
      //Serial.println("Left Bumper down.");  
    }
    if(pistonRBumper.read() == LOW)
    {
      pistonR.stop();
      pistonR.setCurrentPosition(0);
      pistonR.moveTo(0);
      //Serial.println("Right Bumper down.");  
    }

    pistons.run();
  }
}

void bumperTest()
{
  int again = 1;

  Serial.println("Enter 1 to test bumpers");
    while(Serial.available() == 0) {}
    again = Serial.read() - 48;
    
  while(again == 1)
  { 
    if(pistonLBumper.read() == LOW)
      {
        Serial.println("Left Bumper down.");
        //digitalWrite(bumpPistL, HIGH);
      }
    if(pistonRBumper.read() == LOW)
      {
        Serial.println("Right Bumper down.");
      }
  
    if(pistonLBumper.read() == HIGH)
      Serial.println("Left Bumper Up.");
    if(pistonRBumper.read() == HIGH)
      Serial.println("Right Bumper up.");
  
    Serial.println("Enter 1 to test bumpers");
    while(Serial.available() == 0) {}
    again = Serial.read() - 48;
  }
  
}



