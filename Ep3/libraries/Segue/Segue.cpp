#include "Arduino.h"
#include "Segue.h"
#include "MegaMoto.h"

//axle length should be set in Centimeters.
Segue::Segue(Motor left, Motor right, float axleLength)  : _left(left), _right(right), _axleLength(axleLength)
{
  //TODO: read up on member initializer list for clarity on the above syntax
  _pi = 3.14159;
  brake();
  _heading = 0;
}

void Segue::neutral() {
  _left.neutral();
  _right.neutral();
  _heading = -1;
}

void Segue::brake() {
  _left.brake();
  _right.brake();
  _heading = 0;
}

void Segue::forward(int speed) {
  _left.forward(speed);
  _right.forward(speed);
  _heading = 1;
}

void Segue::clockwise(int speed) {
  _left.forward(speed);
  _right.reverse(speed);
  _heading = 2;
}
void Segue::counterclockwise(int speed) {
  _left.reverse(speed);
  _right.forward(speed);
  _heading = 3;
}

void Segue::reverse(int speed) {
  _left.reverse(speed);
  _right.reverse(speed);
  _heading = 4;
}

// this method only allows the the smallest turn radius to be the axle length. Any
//smaller and we have to do different math.
// innerRadius = the length from the pivot to the inner wheel
void Segue::arc(bool positiveRotation, int speed, float innerRadius){
  if (innerRadius < 0){
    innerRadius = 0;
  }
  float turnRatio = getTurnRatio(innerRadius);

  // positive rotation = counterclockwise
  if (positiveRotation == true) {
    _right.setSpeed(speed);
    _left.setSpeed(speed * turnRatio);
    _heading = 3;
  }
  else {
    _right.setSpeed(speed * turnRatio);
    _left.setSpeed(speed);
    _heading = 2;
  }
}  

float Segue::getTurnRatio(float innerRadius) {
  float outerRadius = innerRadius + _axleLength;
  float ratio = innerRadius / outerRadius;
  return ratio;
}

void Segue::setMotorSpeeds(int leftSpeed, int rightSpeed) {
  _left.setSpeed(leftSpeed);
  _right.setSpeed(rightSpeed);
}

//experimental. do not use yet
void Segue::slowToStop() {
  while (_left.getSpeed() != 0 && _right.getSpeed() != 0) {
    int leftSpeed = _left.getSpeed();
    int rightSpeed = _right.getSpeed();
    if (leftSpeed > 0) {
      _left.setSpeed( leftSpeed -1);
    }
    else if (leftSpeed < 0) {
      _left.setSpeed(leftSpeed + 1);
    }
    else if (rightSpeed > 0) {
      _right.setSpeed(rightSpeed - 1);
    }
    else if (rightSpeed < 0) {
      _right.setSpeed(rightSpeed + 1);
    }
  }
}

int Segue::getHeading(){
  return _heading;
}

// float Segue::degreesToRadians(float degrees) {
//   float radians = _pi * (degrees/180);
//   return radians;
// }

