#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

const int encoderAPin = 2;
const int encoderBPin = 3;
Encoder myEnc = Encoder(2, 3);

const int flipper_mag_pin = 4;
const int flipperServoPin = 5;
const int spinner_pin = 6;
const int partPlacerServoPin = 10;

const int wirefeederPin = 12;

Encoder fluxEnc = Encoder(21, 20);

const int dirPin4 = 22;
const int enPin4 = 24;
const int stepPin4 = 26;

const int fluxDCPinUp = 28; 
const int fluxDCPinDown = 30; 

const int enPin3 = 39;
const int stepPin3 = 41;
const int dirPin3 = 37;

const int dirPin = 43;
const int enPin = 45;

const int DCCutterPinCut = 46;
const int DCCutterPinRelease = 48;

const int stepPin = 47;

const int dirPin2 = 49;

const int hopper_pin_fow = 50;
const int hopper_pin_rev = 52;

const int enPin2 = 51;
const int stepPin2 = 53;

// Constants for part servo servo positions
const int cameraHeight = 130;
const int trayHeight = 59;
const int restingHeight = 0;
// Constants for flipper servo positions
const int slidePos = 18;
const int restingPos = 15;
const int flipPos = 180;

Stepper partStep = Stepper(400, stepPin, 0);
Stepper trayStep = Stepper(200, stepPin2, 0);
Stepper revStep = Stepper(6400, stepPin3, 0);
Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partPlacerServo;
Servo flipperServo;

//STATE VARIABLE
int s = 1;


void setup() {
 
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  pinMode(hopper_pin_rev,OUTPUT);
  pinMode(hopper_pin_fow,OUTPUT);
  
  pinMode(flipper_mag_pin,OUTPUT);
  
  pinMode(spinner_pin,OUTPUT);
  
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
 
  pinMode(partPlacerServoPin, OUTPUT);
  pinMode(flipperServoPin, OUTPUT);
 
  pinMode(wirefeederPin, OUTPUT);
  pinMode(DCCutterPinCut, OUTPUT);
  pinMode(DCCutterPinRelease, OUTPUT); 
  pinMode(fluxDCPinUp, OUTPUT);
  pinMode(fluxDCPinDown, OUTPUT);
  
  partStep.setSpeed(100);
  trayStep.setSpeed(200);
  revStep.setSpeed(5);
  fluxStep.setSpeed(100);

  partPlacerServo.attach(partPlacerServoPin);
  flipperServo.attach(flipperServoPin);

  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  
  partPlacerServo.write(restingHeight);
  flipperServo.write(restingPos);
  
}

void loop() {
    
  
  switch(s){
     case 1:
       //get part to camera
       digitalWrite(hopper_pin_rev,HIGH);
       digitalWrite(hopper_pin_fow,LOW);
       delay(5000);
       digitalWrite(hopper_pin_rev,LOW);
       digitalWrite(hopper_pin_fow,HIGH);
       delay(300);
 
       
      break;
      
  }
  
  
 



}


