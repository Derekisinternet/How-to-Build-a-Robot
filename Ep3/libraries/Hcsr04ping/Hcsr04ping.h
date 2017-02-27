#ifndef Hcsr04_h
#define Hcsr04_h
#include "Arduino.h"

class Pinger {
	public:
		Pinger(int trig, int echo);
		float ping();
	private:
		// if the pins get changed, the object won't work, so I
  	// made them private variables. #security
		int _trig;
		int _echo;
};
#endif