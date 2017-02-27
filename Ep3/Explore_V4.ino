//last updated 12-13-2016

#include <Hcsr04ping.h>
#include <MegaMoto.h>
#include <Segue.h>

Motor motorL(8,11,3);
Motor motorR(12, 9, 10);
Segue segue(motorL, motorR, 56.0);
int segueSpeed = 30;

//### sensor array ###
//forward facing:
Pinger forwardL(50, 51);
Pinger forwardR(52, 53);
Pinger forwardC(34,35);
//right facing:
Pinger rightF(48,49);
Pinger rightA(42,43);
//left facing:
Pinger leftF(46,47);
Pinger leftA(44,45);
//rear facing:
Pinger rearL(38,39);
Pinger rearR(40,41);
Pinger rearC(36,37);

void setup() {
 Serial.begin(9600); 
}

void loop(){
  Serial.println();
  Serial.println(getHeadingClearance(segue.getHeading()));
  //can I move forward?
  if (pathClear(1) == true) {
    //am I clear on the sides?
    if (pathClear(5)) {
      if (segue.getHeading() !=1) {
        //let the motors slow down a bit before changing:
        segue.neutral();
        delay(100);
        segue.brake();
        segue.forward(segueSpeed);
      }
      else {Serial.println("Still forward!");}
    }
    //obstructions on one side. Adjust heading to arc away:
    else {
      if (pathClear(leftF)) {
        segue.arc(true, segueSpeed, 0);
      }
     else if (pathClear(rightF)){
      segue.arc(false, segueSpeed, 0); 
     }
     else {
       reverseAndAdjust();
     }
    }
  }
  //can't move forward
  else {
    if (segue.getHeading() == 1) {
      //let the motors slow down a bit before braking:
      segue.neutral();
      delay(100);
      segue.brake();
      //if not forward, which direction can I turn?
      //are both paths available?
      if (pathClear(2) && pathClear(3)) {
        //cool, pick the direction with most clearance:
        if (getHeadingClearance(2) > getHeadingClearance(3)) {
          segue.clockwise(segueSpeed);
        }
        else { 
          segue.counterclockwise(segueSpeed);
        }
      }
      //If one of my paths is blocked. Find which one, and move the opposite:
      if (pathClear(3) == true) {
        segue.counterclockwise(segueSpeed); 
      }
      else if (pathClear(2) == true) {
        segue.clockwise(segueSpeed);
      }
      //both ways are blocked. Back up:
      else {
        reverseAndAdjust();
      }
    }
  }
  delay(500);
}

boolean pathClear(long direct) {
  float minDist = 30.0;
  float maxDist = 530.0;
  float clearance = getHeadingClearance(direct);
  return  (clearance > minDist && clearance < maxDist);
}

boolean pathClear(Pinger &pinger){
  float minDist = 30.0;
  float maxDist = 530.0;
  float clearance = pinger.ping();
  return  (clearance > minDist && clearance < maxDist);
}

float getHeadingClearance(long direct) {
  Serial.print("Checking clearance for: ");
  Serial.println(direct);
  Serial.print("Clearance: ");
 switch (direct) {
   case 1: {
     float result1 = getSmaller(forwardL.ping(), forwardR.ping());
     float result2 = getSmaller(result1, forwardC.ping());
     return result2;
   }
   break;
   //clockwise
   case 2: {
     float result = getSmaller(rightF.ping(), leftA.ping());
     return result;
   }
   break;
   //counterclockwise
   case 3: {
    float result = getSmaller(leftF.ping(), rightA.ping());
    return result;
   }
   break;
   //reverse
   case 4: {
     float result1 = getSmaller(rearL.ping(), rearR.ping());
     float result2 = getSmaller(result1, rearC.ping());
     return result2;
   }
   break;
   //forward-mounted, side-viewing
   case 5: {
     float result = getSmaller(leftF.ping(), rightF.ping());
     return result;
   }
   break;
   case 6: {
     float result = getSmaller(leftA.ping(), rightA.ping());
     return result;
   }
   break;
   default: {
     float result = 0.0;
     return result;
   }
   break;
 }
}

float getSmaller(float a, float b) {
  if (a < b) {
  return a;
  }
  else {return b;}
}

void reverseAndAdjust() {
  //back up an arbitrary distance:
  float numSec = 0;
  while (numSec < 3) {
    if (pathClear(4)) {
      segue.reverse(segueSpeed);
    }
    else {
       if ( segue.getHeading() == 4) {
         segue.neutral();
         delay(100);
         segue.brake();
       } 
    }
    delay(500);
    numSec +=0.5;
  }
  //turn in the most open direction:
  float turnSec = 0;
  while (turnSec < 2 ){
    if (pathClear(2) && pathClear(3)) {
      if (getHeadingClearance(2) > getHeadingClearance(3)) {
          segue.clockwise(segueSpeed);
       }
       else{
         segue.counterclockwise(segueSpeed);
       }
    }
    else {
      if (pathClear(2)) {
        segue.clockwise(segueSpeed);
      }
      if (pathClear(3)) {
        segue.counterclockwise(segueSpeed); 
      }
    }
    delay(500);
    turnSec += 0.5; 
   }
 }

