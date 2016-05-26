/*
    Getting Started Code for IEEE Ottawa Robotics Competition - Defy The Maze Competition
    Written by David Bascelli
    Febuary 25, 2016

    This code is provided as an example to demonstrate how use the orc libraries to get
    started on programming your robot to compete in the competition.
    All it does is go forward until the ir sensors detect black.
    If the ultrasonic sensor detects something it turns right
    Find out more at:
      http://www.orc.ieeeottawa.ca/arduino-challenge/
*/

//This is where you must declare what libraries you are using
#include <IRControl.h>
#include <MotorControl.h>
#include <UltrasonicControl.h>

//In this section you declare what pins you are using, modify this to work with your specific robot
const int echo_pin = 3;
const int trig_pin = 2;
const int left_ir_pin = 0;
const int right_ir_pin = 1;
const int right_motor_port = 1; //What port 1 or 0 is the right motor connected to.
const int left_motor_port = 2;

//In this section the different objects are created to represent the various motors and sensors. These will be used throughout the code
MotorControl rightMotor(right_motor_port);
MotorControl leftMotor(left_motor_port);
IRControl rightIR(right_ir_pin);
IRControl leftIR(left_ir_pin);
UltrasonicControl ultrasonic(trig_pin, echo_pin);

//All sketches must have setup and loop. setup runs ones at when the Arduino turns on or resets,
//loop repeats forever
void setup() {
  //All the setup happens when we declare the objects so nothing is needed where
}

bool obstacleAhead = false;
int forward = 60;
int lChange = 0;
int rChange = 0;
int posX = 0;
int posY = 0;
int direction = 'u';
bool reverse = false;

bool trapped = true;////////ADDITION////////

void MoveForwards() {
   reverse = false;////////ADDITION////////
  rightMotor.forward((forward + rChange));
  leftMotor.forward((forward + lChange)*90/75);
}
void MoveBackwards() {
  reverse = true;////////ADDITION////////
  rightMotor.reverse((forward + rChange));
  leftMotor.reverse((forward + lChange));
}

void TurnRight() {
   while (leftIR.isBlack() || rightIR.isBlack()) {
    rightMotor.reverse(0);
    leftMotor.forward(90);
  }
   while (!leftIR.isBlack() && !rightIR.isBlack()) {
    rightMotor.reverse(0);
    leftMotor.forward(90);
  }

}
void TurnLeft() {
  while (leftIR.isBlack() || rightIR.isBlack()) {
    rightMotor.forward(150);
    leftMotor.reverse(0);
  }
}
void TurnUp() {
  while (rightIR.isBlack() || leftIR.isBlack()) {
    lChange = 0;
    rChange=0;
    MoveForwards();
  }
}
void TurnBack() {
 while (leftIR.isBlack() || rightIR.isBlack()) {
   leftMotor.forward(100);
   rightMotor.reverse(100);
  }
  while(!leftIR.isBlack()&&!rightIR.isBlack()){
    leftMotor.forward(100);
    rightMotor.reverse(100);
  }
}
void Stop() {
  rightMotor.halt();
  leftMotor.halt();
}

void MoveUp() {
  switch (direction) {
    case 'd':
      TurnBack();
      break;
    case 'r':
      TurnLeft();
      break;
    case 'l':
      TurnRight();
      break;
    default:
      TurnUp();
  }
  direction = 'u';
}
void MoveRight() {
  switch (direction) {
    case 'd':
      TurnLeft();
      break;
    case 'u':
      TurnRight();
      break;
    case 'l':
      TurnBack();
      break;
    default:
      TurnUp();
  }
  direction = 'r';
}

void Align(char offset) {
  int align =8;
  if (offset == 'l' && !reverse) {
    lChange = -align;
    rChange = align;
    while(rightIR.isBlack()&&!leftIR.isBlack()){
    MoveForwards();
    }
  }
  else if (offset == 'r' && !reverse) {
    lChange = align;
    rChange = -align;
    while(leftIR.isBlack() && !rightIR.isBlack()){
    MoveForwards();
    }
  }
  else if (offset == 'l' && reverse) {
    lChange = align;
    rChange = -align;
    MoveBackwards();
  }
  else if (offset == 'r' && reverse) {
    lChange = align;
    rChange = -align;
    MoveBackwards();
  }
}

void loop() {
  if (posX == 3 && posY == 3) {
    while (true) {
      Stop();
    }
  }
  if (rightIR.isBlack() && leftIR.isBlack()) {
   if(!obstacleAhead){
    if (direction == 'u') {
      posY++;
    }
    else if (direction == 'r') {
      posX++;
    }
    else if (direction == 'd') {
      posY--;
    } else {
      posX--;
    }
   }
    if (ultrasonic.detect()||obstacleAhead) {
      if (direction == 'u') {
        MoveRight();
      }
      else if (direction == 'r') {
        MoveUp();
      }
      else {
      }
    } else {
      if (direction == 'u') {
        if (posY >= 3) {
          MoveRight();
        } else {
          MoveUp();
        }
      }
      else if (direction == 'r') {
        if (posX >= 3) {
          MoveUp();
        } else {
          MoveRight();
        }
      }
      else {
      }
    }
    obstacleAhead=false;
  }
  else if (rightIR.isBlack()) {
    Align('l');
  }
  else if (leftIR.isBlack()) {
    Align('r');
  }
  else {
    lChange = 0;
    rChange = 0;
    MoveForwards();
  }

}
