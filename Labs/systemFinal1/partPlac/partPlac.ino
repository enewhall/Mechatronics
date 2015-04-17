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
const int slidePos = 18;
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

//STATE VARIABLE
int s = 1;


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
  //cameraServo.write(holdingPos);  
  cameraServo.write(viewingPos);
}

void loop() {
  
  int serialValue = 0;
  
  switch(s){
     case 1:
       // Get part to camera
       digitalWrite(hopper_pin_rev,HIGH);
       digitalWrite(hopper_pin_fow,LOW);
       delay(500);
       digitalWrite(hopper_pin_rev,LOW);
       digitalWrite(hopper_pin_fow,HIGH);
       delay(300);
 
       //We now give signal to execute the processing of current image
       serialValue = 0;
       if(Serial.available()) 
       {
          serialValue = Serial.read() - 48;
          Serial.print(serialValue);
       }
      
       if(serialValue != 0){
         cameraServo.write(viewingPos);
         delay(500);
         //s = 2;
       }
       
       //tell the vision processing to get current result
       Serial.write('0');
       break;
    case 2:
      // Flip the part
      digitalWrite(hopper_pin_rev,LOW);
      digitalWrite(hopper_pin_fow,LOW);
      
      digitalWrite(flipper_mag_pin,HIGH);
      delay(100);
      flipperServo.write(flipPos);
      delay(1500);
      digitalWrite(flipper_mag_pin,LOW);
      flipperServo.write(restingPos);
      delay(100);
      s = 3;
      
      break;
    case 3:
      // Move placer to get part
      digitalWrite(dirPin, HIGH);
      digitalWrite(enPin, LOW);
      partStep.step(5280);
      digitalWrite(enPin, HIGH);      
      digitalWrite(placer_mag_pin,HIGH);
      partPlacerServo.write(cameraHeight);
      delay(1500);
      partPlacerServo.write(restingHeight);
      delay(1000);
      s=4;      
      break;
    case 4:
      //move to tray
      digitalWrite(dirPin, LOW);
      digitalWrite(enPin, LOW);
      partStep.step(4500);
      digitalWrite(enPin, HIGH);      
      
      partPlacerServo.write(trayHeight);
      delay(1500);
      digitalWrite(placer_mag_pin,LOW);
      partPlacerServo.write(restingHeight);
      delay(1000);
      
      s=5;
      break;
      
      
   case 5:
     digitalWrite(dirPin2, LOW);
     digitalWrite(enPin2, LOW);
     trayStep.step(2450);
     digitalWrite(enPin2, HIGH);
     s = 6;
     break;
     
   
     
   case 6:
     digitalWrite(wirefeederPin, HIGH);
     delay(300);
     digitalWrite(wirefeederPin, LOW);
     s = 7;
     break;
     
   case 7:
     digitalWrite(DCCutterPinCut, HIGH);
     digitalWrite(DCCutterPinRelease, LOW);
     Serial.println(myEnc.read());
     if(myEnc.read() >= 2100)
     {
        digitalWrite(DCCutterPinCut, LOW);
        digitalWrite(DCCutterPinRelease, LOW);   
        s = 8;
     } 
     break;
     
   case 8:
     digitalWrite(DCCutterPinCut, LOW);
     digitalWrite(DCCutterPinRelease, HIGH);
     if(myEnc.read() <= 29)
     {
        digitalWrite(DCCutterPinCut, LOW);
        digitalWrite(DCCutterPinRelease, LOW);   
        s = 9;
     } 
     break;
     
   case 9:
     digitalWrite(dirPin4, HIGH);
     digitalWrite(enPin4, LOW);
     fluxStep.step(1400);
     digitalWrite(enPin4, HIGH);
     s = 10;
     break;  
   
   case 10:
     
     digitalWrite(fluxDCPinDown, HIGH);
     digitalWrite(fluxDCPinUp, LOW);
     delay(220);   
     digitalWrite(fluxDCPinDown, LOW);
     digitalWrite(fluxDCPinUp, LOW);
     delay(60);
     digitalWrite(fluxDCPinDown, LOW);
     digitalWrite(fluxDCPinUp, HIGH);
     delay(150);
     digitalWrite(fluxDCPinDown, LOW);
     digitalWrite(fluxDCPinUp, LOW);
     delay(300);
     s = 11;
     break;  
   case 11:
     digitalWrite(dirPin2, HIGH);
     digitalWrite(enPin2, LOW);
     trayStep.step(300);
     digitalWrite(enPin2, HIGH);
     
     digitalWrite(dirPin4, LOW);
     digitalWrite(enPin4, LOW);
     fluxStep.step(200);
     digitalWrite(enPin4, HIGH);
     
     
     s=12;
     break;
   case 12:
     digitalWrite(enPin3,LOW);
     digitalWrite(dirPin3,LOW);
     revStep.step(608);
     digitalWrite(enPin3, HIGH);
     delay(200);
     break;
     
   
  }      
 



}


