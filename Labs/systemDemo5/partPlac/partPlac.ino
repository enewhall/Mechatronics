#include <Stepper.h>
#include <Servo.h>

//Servo control
const int servoPin = 10;

//Steppper
const int enPin = 45;
const int stepPin = 47;
const int dirPin = 43;

const int enPin2 = 51;
const int stepPin2 = 53;
const int dirPin2 = 49;

const int enPin3 = 39;
const int stepPin3 = 41;
const int dirPin3 = 37;

const int enPin4 = 24;
const int stepPin4 = 26;
const int dirPin4 = 22;

const int wirefeederPin = 12;

//Wire Cutter
const int encoderAPin = 2;
const int encoderBPin = 3;
int encoderAValue = 0;
int encoderAPrev = 0;
int encoderBValue = 0;
int encoderBPrev = 0;

int DCMotorAngle = 0;
const int DCMotorPinA = 46;
const int DCMotorPinB = 48;



//magnet
const int magnetPin = 11;

int s = 0;

Stepper partStep = Stepper(400, stepPin, 0);

Stepper trayStep = Stepper(200, stepPin2, 0);

Stepper revStep = Stepper(6400, stepPin3, 0);

Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partServo;

void setup() {
  // put your setup code here, to run once:
  
//  Serial.begin(9600);
//  while (!Serial) { //Copy
//    ; // wait for serial port to connect. Needed for Leonardo only
//  }
  
  
  
  
  pinMode(encoderAPin,INPUT);
  pinMode(encoderBPin,INPUT);
  
  pinMode(enPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enPin3, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(enPin4, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
  pinMode(magnetPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(wirefeederPin, OUTPUT);
  pinMode(DCMotorPinA, OUTPUT);
  pinMode(DCMotorPinB, OUTPUT); 
  partStep.setSpeed(100);
  trayStep.setSpeed(200);
  revStep.setSpeed(5);
  fluxStep.setSpeed(100);
  partServo.attach(servoPin);
  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  partServo.write(90);
  
  attachInterrupt(0, PinA, CHANGE);
  attachInterrupt(1, PinB, CHANGE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
 switch(s) {
   
   case 0: //move to pick up
     digitalWrite(dirPin, HIGH);
     digitalWrite(enPin, LOW);
     partStep.step(3000);
     digitalWrite(enPin, HIGH);
     s = 1;
     break;
     
   case 1:
     digitalWrite(magnetPin, HIGH);
     partServo.write(45);
     delay(300);
     partServo.write(90);
     s = 2;
     break;
     
   case 2:
     delay(50);
     partServo.write(135);
     delay(300);
     partServo.write(90);
     s = 3;
     break;
     
   case 3:
     digitalWrite(dirPin, LOW);
     digitalWrite(enPin, LOW);
     partStep.step(1500);
     digitalWrite(enPin, HIGH);
     s = 4;
     break;
     
   case 4:
     partServo.write(45);
     delay(300);
     partServo.write(90);
     digitalWrite(magnetPin, LOW);
     s = 5;
     break;
     
   case 5:
     delay(50);
     partServo.write(135);
     delay(300);
     partServo.write(90);
     s = 6;
     break;
     
   case 6:
     digitalWrite(dirPin2, LOW);
     digitalWrite(enPin2, LOW);
     trayStep.step(2250);
     digitalWrite(enPin2, HIGH);
     s = 7;
     break;
     
   
     
   case 7:
     digitalWrite(wirefeederPin, HIGH);
     delay(350);
     digitalWrite(wirefeederPin, LOW);
     s = 8;
     break;
     
   case 8:
     digitalWrite(DCMotorPinA, HIGH);
     digitalWrite(DCMotorPinB, LOW);
     if(DCMotorAngle >= 1650)
     {
        digitalWrite(DCMotorPinA, LOW);
        digitalWrite(DCMotorPinB, LOW);   
        s = 9;
     } 
     break;
     
   case 9:
     digitalWrite(DCMotorPinA, LOW);
     digitalWrite(DCMotorPinB, HIGH);
     if(DCMotorAngle <= 500)
     {
        digitalWrite(DCMotorPinA, LOW);
        digitalWrite(DCMotorPinB, LOW);   
        s = 10;
     } 
     break;
     
   case 10:
     digitalWrite(dirPin4, HIGH);
     digitalWrite(enPin4, LOW);
     fluxStep.step(1250);
     digitalWrite(enPin4, HIGH);
     s = 11;
     break;  
     
     
   case 11:
     digitalWrite(enPin3,LOW);
     digitalWrite(dirPin3,LOW);
     revStep.step(608);
     digitalWrite(enPin3, HIGH);
     delay(200);
     break;
     
     
   
   
 }
 
 
  
}



void PinA(){
   encoderAPrev = encoderAValue;
   encoderAValue = digitalRead(encoderAPin);
  if(encoderAPrev){
    if(encoderBPrev){
      //counterclockwise
      DCMotorAngle -= 1;
    } else{
      //clockwise
      DCMotorAngle += 1;
    }  
  }else{
    if(encoderBPrev){
      //clockwise
      DCMotorAngle += 1;
    } else{
      //counterclockwise
      DCMotorAngle -= 1;
    }
  }
   
}

void PinB(){
   encoderBPrev = encoderBValue;
   encoderBValue = digitalRead(encoderBPin);
  if(encoderBPrev){
    if(encoderAPrev){
      //clockwise
      DCMotorAngle += 1;
    } else{
      //counterclockwise
      DCMotorAngle -= 1;
    }  
  }else{
    if(encoderAPrev){
      //counterclockwise
      DCMotorAngle -= 1;
    } else{
      //clockwise
      DCMotorAngle += 1;
    }
  }
}

