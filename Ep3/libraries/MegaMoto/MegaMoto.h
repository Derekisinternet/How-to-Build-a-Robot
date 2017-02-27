#include "Arduino.h"
#ifndef MegaMoto_h
#define MegaMoto_h


class Motor {
	public:
		Motor(int enable, int pin_a, int pin_b);
    Motor();
		void forward(int speed);
		void reverse(int speed);
    void brake();
    void neutral();
    int getSpeed();
    void setSpeed(int speed);
    int getStatus();
    // void comeToAStop();

  private:
  	int _a;
  	int _b;
  	int _enable;
    int _speed;
    int _status;
    
};

#endif