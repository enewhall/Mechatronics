#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

//Servo control
const int servoPin = 10;
const int holdUp = 93;
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
Encoder myEnc = Encoder(2, 3);
Encoder fluxEnc = Encoder(21, 20);
const int DCMotorPinA = 46;
const int DCMotorPinB = 48;
const int fluxDCPinA = 30; //down
const int fluxDCPinB = 28; //up



//magnet
const int magnetPin = 11;

int s = 8;

Stepper partStep = Stepper(400, stepPin, 0);

Stepper trayStep = Stepper(200, stepPin2, 0);

Stepper revStep = Stepper(6400, stepPin3, 0);

Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partServo;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  
  
  
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
  pinMode(fluxDCPinA, OUTPUT);
  pinMode(fluxDCPinB, OUTPUT);
  partStep.setSpeed(100);
  trayStep.setSpeed(200);
  revStep.setSpeed(5);
  fluxStep.setSpeed(100);
  partServo.attach(servoPin);
  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  partServo.write(150); //calibration
  delay(200);
  partServo.write(holdUp); //Hold speed
  //attachInterrupt(0, PinA, CHANGE);
  //attachInterrupt(1, PinB, CHANGE);
  
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
     partServo.write(holdUp);
     s = 2;
     break;
     
   case 2:
     delay(50);
     partServo.write(135);
     delay(300);
     partServo.write(holdUp);
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
     partServo.write(holdUp);
     digitalWrite(magnetPin, LOW);
     s = 5;
     break;
     
   case 5:
     delay(50);
     partServo.write(135);
     delay(300);
     partServo.write(holdUp);
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
     Serial.println(myEnc.read());
     if(myEnc.read() >= 500)
     {
        digitalWrite(DCMotorPinA, LOW);
        digitalWrite(DCMotorPinB, LOW);   
        s = 9;
     } 
     break;
     
   case 9:
     digitalWrite(DCMotorPinA, LOW);
     digitalWrite(DCMotorPinB, HIGH);
     if(myEnc.read() <= 29)
     {
        digitalWrite(DCMotorPinA, LOW);
        digitalWrite(DCMotorPinB, LOW);   
        s = 11;
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
   //Serial.println(fluxEnc.read());
//     digitalWrite(enPin3,LOW);
//     digitalWrite(dirPin3,LOW);
//     revStep.step(608);
//     digitalWrite(enPin3, HIGH);
//     delay(200);
     break;
     
   case 12:
     digitalWrite(fluxDCPinA, HIGH);
     digitalWrite(fluxDCPinB, LOW);
     delay(90);   
     s = 11;
     digitalWrite(fluxDCPinA, LOW);
     digitalWrite(fluxDCPinB, LOW);
     delay(100);
     digitalWrite(fluxDCPinA, LOW);
     digitalWrite(fluxDCPinB, HIGH);
     delay(20);
     digitalWrite(fluxDCPinA, LOW);
     digitalWrite(fluxDCPinB, LOW);
     break;
     
     
   
   
 }
 
 
  
}


//
//void PinA(){
//  // look for a low-to-high on channel A
//  if (digitalRead(encoderAPin) == HIGH) { 
//
//    // check channel B to see which way encoder is turning
//    if (digitalRead(encoderBPin) == LOW) {  
//      DCMotorAngle = DCMotorAngle + 1;         // CW
//    } 
//    else {
//      DCMotorAngle = DCMotorAngle - 1;         // CCW
//    }
//  }
//
//  else   // must be a high-to-low edge on channel A                                       
//  { 
//    // check channel B to see which way encoder is turning  
//    if (digitalRead(encoderBPin) == HIGH) {   
//      DCMotorAngle = DCMotorAngle + 1;          // CW
//    } 
//    else {
//      DCMotorAngle = DCMotorAngle - 1;          // CCW
//    }
//  }
//  //Serial.println (DCMotorAngle, DEC);          
//  // use for debugging - remember to comment out 
//  
//   
//}
//
//void PinB(){
//  // look for a low-to-high on channel B
//  if (digitalRead(encoderBPin) == HIGH) { 
//
//    // check channel A to see which way encoder is turning
//    if (digitalRead(encoderAPin) == HIGH) {  
//      DCMotorAngle = DCMotorAngle + 1;         // CW
//    } 
//    else {
//      DCMotorAngle = DCMotorAngle - 1;         // CCW
//    }
//  }
//
//  else   // must be a high-to-low edge on channel B                                       
//  { 
//    // check channel B to see which way encoder is turning  
//    if (digitalRead(encoderAPin) == LOW) {   
//      DCMotorAngle = DCMotorAngle + 1;          // CW
//    } 
//    else {
//      DCMotorAngle = DCMotorAngle - 1;          // CCW
//    }
//  }
//  //Serial.println (DCMotorAngle, DEC);          
//  // use for debugging - remember to comment out 
//}

