#include "Arduino.h"
#include "MegaMoto.h"

Motor::Motor(int enable, int pin_a, int pin_b) {
	_enable = enable;
	_a = pin_a;
	_b = pin_b;
	_speed = 0;

	pinMode(_enable, OUTPUT);
	pinMode(_a, OUTPUT);
	pinMode(_b, OUTPUT);

	neutral();
}

//instantiate a blank motor object. For use with pointers.
Motor::Motor() {}

void Motor::brake() {
	analogWrite(_a, 0);
  analogWrite(_b, 0);
  digitalWrite(_enable, LOW);
  _speed = 0;
  _status = 0;
}

void Motor::forward(int speed){
	analogWrite(_a, speed);
  analogWrite(_b, 0);
  digitalWrite(_enable, HIGH);
  _speed = speed;
  _status = 1;
}

void Motor::reverse(int speed){
  analogWrite(_a, 0);
  analogWrite(_b,  speed);
  digitalWrite(_enable, HIGH);
  _speed = speed * -1;
  _status = 2;
}

void Motor::neutral() {
	analogWrite(_a, 0);
  analogWrite(_b, 0);
  digitalWrite(_enable, HIGH);
  _status = -1;
}

//A nice, abstract way to change speed and direction
//TODO: create method that adjusts large changes in speed slowly rather than all at once. #avoidmotorstrain.
void Motor::setSpeed(int speed) {
	if (speed > 0) {
		if (getStatus() == 2) {
			neutral();
			brake();
		}
		forward(speed);
	}
	else if (speed < 0) {
		if (getStatus() ==1) {
			neutral();
			brake();
		}
		reverse(speed);
	}
	else {
		neutral();
	}
}

int Motor::getStatus() {
	return _status;
}



int Motor::getSpeed() {
	//TODO: figure out what value should be returned if the motor is neutral
	if (getStatus() != -1 ) {
		return _speed;
	}
}

