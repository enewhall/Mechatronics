#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

const int encoderAPin = 2;
const int encoderBPin = 3;
Encoder myEnc = Encoder(2, 3);

const int flipper_mag_pin = 4;
const int flipperServoPin = 5;
//part reorientation servo pin 6
const int placer_mag_pin = 7;
const int partPlacerServoPin = 10;

const int cameraServoPin = 11;

const int wirefeederPin = 12;

Encoder fluxEnc = Encoder(21, 20);

const int dirPin4 = 22;
const int enPin4 = 24;
const int stepPin4 = 26;

const int fluxDCPinUp = 30; 
const int fluxDCPinDown = 28; 

const int LED0 = 42; 
const int LED1 = 36;
const int LED2 = 38;
const int LED3 = 40; 
const int LED4 = 34;


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
const int slidingPos = 35;
const int restingPos = 18;
const int flipPos = 180;
// Constant for camera Servo
const int holdingPos = 80;
const int viewingPos = 15;


Stepper partStep = Stepper(400, stepPin, 0);
Stepper trayStep = Stepper(200, stepPin2, 0);
Stepper revStep = Stepper(6400, stepPin3, 0);
Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partPlacerServo;
Servo flipperServo;
Servo cameraServo;

//STATE VARIABLES
int cameraState = 1;
unsigned long cameraTime = 0;

char partPos = 0;

void setup() {
 
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);

  pinMode(placer_mag_pin,OUTPUT);
  
  pinMode(hopper_pin_rev,OUTPUT);
  pinMode(hopper_pin_fow,OUTPUT);
  
  pinMode(flipper_mag_pin,OUTPUT);
  
  
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
  pinMode(cameraServoPin,OUTPUT);
 
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
  cameraServo.attach(cameraServoPin);

  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  
  partPlacerServo.write(restingHeight);
  flipperServo.write(restingPos);
  cameraServo.write(holdingPos);  
  
  cameraTime = millis();
}

void loop() {
  
  int serialValue = 0;
   if(Serial.available()) {
      serialValue = Serial.read() - 48;
   }

  switch(cameraState){
    case 1:
      //SPIN BACK
      digitalWrite(hopper_pin_fow,LOW);
      digitalWrite(hopper_pin_rev,HIGH);
      flipperServo.write(restingPos);
      cameraServo.write(holdingPos);  
      digitalWrite(flipper_mag_pin,LOW);
      
      if(serialValue != 0){
        cameraState = 5;
        cameraTime = millis();
      }else if(partPos == 0 && millis() - cameraTime > 5000){
        cameraState = 2;
        cameraTime = millis();
      }
      break;
    case 2:
      //SPIN FOWARD
      digitalWrite(hopper_pin_fow,HIGH);
      digitalWrite(hopper_pin_rev,LOW);
      flipperServo.write(restingPos);
      cameraServo.write(holdingPos);  
      digitalWrite(flipper_mag_pin,LOW);
      
      if(millis() - cameraTime > 300){
        cameraState = 1;
        cameraTime = millis();
      }
      break;
    case 3:
      //FLIP PART
      digitalWrite(hopper_pin_fow,LOW);
      digitalWrite(hopper_pin_rev,HIGH);
      flipperServo.write(flipPos);
      cameraServo.write(holdingPos);
      digitalWrite(flipper_mag_pin,HIGH);  
      
      if(millis() - cameraTime > 1000){
        cameraState = 2;
        cameraTime = millis();
      }
      break;
    case 4:
      //SLIDE PART
      digitalWrite(hopper_pin_fow,LOW);
      digitalWrite(hopper_pin_rev,HIGH);
      flipperServo.write(slidingPos);
      cameraServo.write(viewingPos);  
      digitalWrite(flipper_mag_pin,LOW);
      
      if(millis() - cameraTime > 1000){
        cameraState = 2;
        cameraTime = millis();
      }
      break;
    case 5:
      //VIEWING PART
      digitalWrite(hopper_pin_fow,LOW);
      digitalWrite(hopper_pin_rev,LOW);
      flipperServo.write(restingPos);
      cameraServo.write(viewingPos);
      digitalWrite(flipper_mag_pin,HIGH);  
      
      if(millis() - cameraTime > 2500){
        if(serialValue == 1 ){
          cameraState = 4;
          partPos = 1;
          cameraTime = millis();
        }else if(serialValue == 2){
          cameraState = 4;
          partPos = 2;
          cameraTime = millis();
        }else if(serialValue == 3){
          cameraState = 3;
          partPos = 1;
          cameraTime = millis();
        }else if(serialValue == 3){
          cameraState = 3;
          partPos = 2;
          cameraTime = millis();
        }
          
      }
      
      break;
  }      
 



}


