
#ifndef Segue_h
#define Segue_h

#include "Arduino.h"
#include "MegaMoto.h"

class Segue {
    public:
        Segue(Motor left, Motor right, float axleLength);
        void forward(int speed);
        void reverse(int speed);
        void brake();
        void counterclockwise(int speed);
        void clockwise(int speed);
        void neutral();
        void arc(bool positiveRotation, int speed, float innerRadius);
        void slowToStop();
        int getHeading();
        

 
	private:
        Motor _left;
        Motor _right;
        float _axleLength;
        float _pi;
        int _heading;
        void setMotorSpeeds(int leftSpeed, int rightSpeed);
        float getTurnRatio(float innerRadius);
        void setHeading(int heading);
};

#endif

