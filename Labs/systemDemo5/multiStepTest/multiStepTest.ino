#include <CustomStepper.h>

//Full constructor, just the first 4 parameters are necessary, they are the pins connected to the motor,
//the others are optional, and default to the following below
//the 5th paramater is the steps sequence, where the 1st element of the array is the number of steps
//it can have a maximum of 8 steps
//the 6th parameter is the SPR (Steps Per Rotation)
//the 7th parameter is the RPM
//the 8th parameter is the rotation orientation
int s = 0;
int enable_pin = 2;
int dir_pin = 4;
int step_pin = 9;

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
  
}

void loop()
{
  switch(s)
  {
    case 0:
      stepper.setDirection(CW);
      stepper.rotate(608);
      s = 1;
      break;
    case 1:
      if(stepper.isDone())
      {
        s = 0;
        delay(1000);
        break;
      }
    
  }
  stepper.run();
}
