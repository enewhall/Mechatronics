#include <Stepper.h>



int s = 0;
int enable_pin = 2;
int dir_pin = 4;
int step_pin = 9;

int numSteps = 0;

Stepper motor(6400,step_pin,0);

void setup(){
  Serial.begin(9600);
  pinMode(enable_pin,OUTPUT);
  pinMode(step_pin,OUTPUT); 
  pinMode(dir_pin,OUTPUT);
  motor.setSpeed(5);
}

void loop(){
  digitalWrite(enable_pin,LOW);
  digitalWrite(dir_pin,LOW);
  motor.step(608);
  delay(1000);
    
}



