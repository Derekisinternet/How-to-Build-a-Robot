#include "Arduino.h"
#include "Hcsr04ping.h"

Pinger::Pinger(int trig, int echo){
  _trig = trig;
	_echo = echo;

	pinMode(_trig, OUTPUT);
	pinMode(_echo, INPUT);
}

float Pinger::ping(){
	digitalWrite(_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);
  float duration = pulseIn(_echo, HIGH);
  float distance = (duration/2/29);
  return distance;
}