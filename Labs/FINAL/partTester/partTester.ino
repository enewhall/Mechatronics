#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#include <CustomStepper.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

const char encoderAPin = 2;
const char encoderBPin = 3;
Encoder myEnc = Encoder(2, 3);

const char flipper_mag_pin = 4;
const char flipperServoPin = 5;
const char partPlacerServoPin =  6;
const char placer_mag_pin = 7;

const char partServoPin = 10;

const char cameraServoPin = 11;

const char wirefeederPin = 12;

Encoder wireEnc = Encoder(21, 20);

const char dirPin3 = 22;
const char enPin3 = 24;
const char stepPin3 = 26;

const char fluxDCPinUp = 30; 
const char fluxDCPinDown = 28; 

const char LED0 = 34; //34 
const char LED1 = 40;
const char LED2 = 38;
const char LED3 = 36; 
const char LED4 = 42;
char LEDValue = 0;

const char enPin4 = 39;
const char stepPin4 = 41;
const char dirPin4 = 37;

const char dirPin = 35;
const char enPin = 45;

const char DCCutterPinCut = 46;
const char DCCutterPinRelease = 48;

const char stepPin = 47;

const char dirPin2 = 49;

const char hopper_pin_fow = 50;
const char hopper_pin_rev = 52;

const char enPin2 = 51;
const char stepPin2 = 53;

// Constants for part servo servo positions
const int cameraHeight = 130;
const int trayHeight = 59;
const int restingHeight = 0;
// Constants for flipper servo positions
const int slidingPos = 25;
const int restingPos = 18;
const int flipPos = 180;
// Constant for camera Servo
const int holdingPos = 20;
const int viewingPos = 90;

//Stepper partStep = Stepper(400, stepPin, 0);
Stepper trayStep = Stepper(200, stepPin2, 0);
Stepper revStep = Stepper(6400, stepPin3, 0);
//Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partPlacerServo;
Servo partServo; //reorientator
Servo flipperServo;
Servo cameraServo;


//STATE VARIABLES
int cameraState = 100;
unsigned long cameraTime = 0;
int partState = 0;
unsigned long partPlacerTimer = 0;

char partPos = 0;

//add this for partplacer part
char currentPartPos = 0;
CustomStepper partStep(stepPin, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);
//CustomStepper trayStep(stepPin2, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 200, 100, CW);
unsigned char partStepperXCounter = 0;
unsigned char partStepperYCounter = 0;


//For the revolver preloading
int revRelState = 100; //4
int fluxDispState = 0; //starts when revRelState finishes
unsigned char revRelCount = 100;
unsigned long revFluxTimer = 0;
bool partPlacerDone = true; //remember
//CustomStepper revStep(stepPin3, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 6400, 5, CW);
CustomStepper fluxStep(stepPin4, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);//400, stepPin4, 0);
const int fluxStartingPos = 2270;

unsigned char fluxDispXCounter = 0;
unsigned char fluxDispYCounter = 0;

boolean start = false;
int serialValue = 6;

int dir = 0;

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
  
  partStep.setRPM(50);
  trayStep.setSpeed(400);
  revStep.setSpeed(10);
  fluxStep.setRPM(800);

  partPlacerServo.attach(partPlacerServoPin);
  flipperServo.attach(flipperServoPin);
  cameraServo.attach(cameraServoPin);
  partServo.attach(partServoPin);

  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  
  digitalWrite(LED0,LOW);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  
  partPlacerServo.write(restingHeight);
  flipperServo.write(restingPos);
  cameraServo.write(0);  
  partServo.write(0);
    
  cameraTime = millis();
  LEDValue = 0;
     
}

void loop() {
  
  if(Serial.available()) {
      serialValue = Serial.read() - 48;
      LEDValue = serialValue;
  }
  switch(LEDValue){ 
     case 0:
       digitalWrite(LED0,LOW);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;
     case 1:
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,LOW);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
     case 2:
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,LOW);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
     case 3:
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,LOW);
       digitalWrite(LED4,HIGH);
       break;  
     case 4:
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,LOW);
       break;  
     case 5:
       start = true;
       break;
         
  }
  if(start){
    
     //Endurance test. See if it able to run without freezing.
//     LEDValue = (LEDValue + 1) % 6;
//     delay(500);    

    
//     //See if the Stepper Motor is able to move
//     digitalWrite(enPin, LOW);
//     digitalWrite(dirPin, dir);
//     partStep.step(400);           
//     digitalWrite(enPin, HIGH);
//     Serial.println("We did a step");
//     dir = (dir + 1) % 2;
//     delay(500);

//     //See if the Stepper Motor is able to move(customStepper)
//     switch(partState) {
//       
//       case 0:
//         digitalWrite(enPin, LOW);
//         digitalWrite(dirPin, dir);
//         partStep.rotateDegrees(400*4);
//         partState = 1;
//         break;
//         
//       case 1:
//         if(partStep.isDone())
//         {                      
//           digitalWrite(enPin, HIGH);
//           Serial.println("We did a step");
//           dir = (dir + 1) % 2;
//           delay(500);
//           partState = 0;
//         }
//         break;
//     }
//     
//     if(partState)
//       partStep.run();




     //See if the tray motor moves well
//     digitalWrite(enPin2, HIGH);
//     digitalWrite(dirPin2, dir);
//     trayStep.step(400);
//     digitalWrite(enPin2, LOW);
//     Serial.println("We did a tray step");
//     dir = (dir + 1) % 2;
//     delay(500);     

//     //See if the rev motor moves well
//     digitalWrite(enPin3, LOW);
//     digitalWrite(dirPin3, dir);
//     revStep.step(6000);
//     digitalWrite(enPin3, HIGH);
//     Serial.println("We did a rev step");
//     dir = (dir + 1) % 2;
//     delay(500);     

      //test flipper servo
      Serial.println(partState);
      switch(partState)
      {
        case 0:
          cameraServo.write(0);
          delay(1000);
          partState = 1;
          break;
          
        case 1:
          cameraServo.write(180);
          delay(1000);
          partState = 0;
          break;
      }

  }
}


