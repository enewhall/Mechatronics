#include <CustomStepper.h>
//It worked :)
//Full constructor, just the first 4 parameters are necessary, they are the pins connected to the motor,
//the others are optional, and default to the following below
//the 5th paramater is the steps sequence, where the 1st element of the array is the number of steps
//it can have a maximum of 8 steps
//the 6th parameter is the SPR (Steps Per Rotation)
//the 7th parameter is the RPM
//the 8th parameter is the rotation orientation
int s = 0;

const int enPin = 45;
const int enPin2 = 51;
const int enPin3 = 24;

int enable_pin = 39;
int dir_pin = 37;
int step_pin = 41;

int numSteps = 0;



CustomStepper stepper(step_pin, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 6400, 12, CW);
boolean rotate1 = false;
boolean rotatedeg = false;
boolean crotate = false;

void setup()
{
  //sets the RPM
  stepper.setRPM(5);
  pinMode(enable_pin,OUTPUT);
  pinMode(step_pin,OUTPUT); 
  pinMode(dir_pin,OUTPUT);
  pinMode(enPin, OUTPUT);
  pinMode(enPin2, OUTPUT);
  pinMode(enPin3, OUTPUT);
  
  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enable_pin, HIGH);
  stepper.setDirection(CW);
  
  
  
}

void loop()
{
  switch(s)
  {
    case 0:
      digitalWrite(enable_pin, LOW);
      digitalWrite(dir_pin, LOW);
      stepper.rotateDegrees(360/21*4);
      //digitalWrite(enable_pin, HIGH);
      s = 1;
      break;
    case 1:
      if(stepper.isDone())
      {
        s = 0;
        digitalWrite(enable_pin, HIGH);
        delay(1000);
        break;
      }
    
  }
  Serial.println("v");
  stepper.run();
}
