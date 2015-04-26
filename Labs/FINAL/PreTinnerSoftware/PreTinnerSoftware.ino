/*#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#include <CustomStepper.h>
#define ENCODER_OPTIMIZE_INTERRUPTS






//For the revolver preloading
 //4


void setup() {
 
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
     
}

void loop() {
  
  if(Serial.available()) {
      serialValue = Serial.read() - 48;
      LEDValue = serialValue;
  }
  
  if(start){
    switch(cameraState){
      case 1:
        //SPIN BACK
        //if(millis()-cameraTime < 300){
          //digitalWrite(hopper_pin_fow,LOW);
          //digitalWrite(hopper_pin_rev,HIGH);
        //}else{
          digitalWrite(hopper_pin_fow,LOW);
          digitalWrite(hopper_pin_rev,LOW);
        //}
    
        flipperServo.write(restingPos);
        cameraServo.write(holdingPos);
        digitalWrite(flipper_mag_pin,LOW);
        if(serialValue != 0 && serialValue != 5 && millis() - cameraTime > 1000){
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
        
        if(millis() - cameraTime > 100){
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
            //partPos = 1;
            cameraTime = millis();
          }else if(serialValue == 2){
            cameraState = 4;
            //partPos = 2;
            cameraTime = millis();
          }else if(serialValue == 3){
            cameraState = 3;
            //partPos = 1;
            cameraTime = millis();
          }else if(serialValue == 3){
            cameraState = 3;
            //partPos = 2;
            cameraTime = millis();
          }
                  
        }
        break;
    }      
    
    serialValue = 0; //only accept latest
   
         
    switch(revRelState){
    case 0:
      digitalWrite(wirefeederPin, HIGH);
      revRelState = 1;
      break;
      
    case 1:
      if(wireEnc.read() > 40)
      {
        wireEnc.write(0);
        digitalWrite(wirefeederPin, LOW);
        revRelState = 2;
      }
      break;
      
    case 2:
      digitalWrite(DCCutterPinCut, HIGH);
      digitalWrite(DCCutterPinRelease, LOW);
      if(myEnc.read() >= 1500)
      {
         digitalWrite(DCCutterPinCut, LOW);
         digitalWrite(DCCutterPinRelease, LOW);   
         revRelState = 3;
      } 
      break;
      
    case 3:
      digitalWrite(DCCutterPinCut, LOW);
      digitalWrite(DCCutterPinRelease, HIGH);
      if(myEnc.read() <= 29)
      {
         //myEnc.write(-5);
         digitalWrite(DCCutterPinCut, LOW);
         digitalWrite(DCCutterPinRelease, LOW);   
         revRelState = 4;
      } 
      break;
      
    case 4: //rotate the revolver
      digitalWrite(enPin3, LOW );
      digitalWrite(dirPin3, LOW);
      revStep.rotateDegrees(360/21*4);
      revRelState = 5;
      break;
      
    case 5:
      if(revStep.isDone())
      {
        digitalWrite(enPin3, HIGH);
        revRelState = 0; //lkj;asd;f
        revRelCount++;
        delay(1000);
        if(revRelCount == 20) //inserted in all the 20 pieces
        {
          revRelState = 100;
          fluxDispState = 0;//afkflhsf
          //Give indication that the machine is ready
        }
        
        
        
        
      }
      break;    
    }
    
    switch(fluxDispState)
    {
    case 0:
      //get an indication that the partPlacer finished
      if(partPlacerDone)
      {
        fluxDispState = 1;
      }
      break;
      
    case 1: //move flux to initial position
      digitalWrite(dirPin4, LOW); //move in -X
      digitalWrite(enPin4, LOW);
      fluxStep.rotateDegrees((fluxStartingPos)*4); //need modification
      fluxDispState = 2;
      break;
      
    case 2:
      if(fluxStep.isDone())
      {
        digitalWrite(enPin4, HIGH);
        fluxDispState = 3;
        //Serial.println("Should push down");
        digitalWrite(fluxDCPinDown, HIGH);
        digitalWrite(fluxDCPinUp, LOW);
        revFluxTimer = millis();
      }
      break;
      
    case 3: //pushing down time
      if(millis() - revFluxTimer > 100)
      {
        //Serial.println("finish pushing");
        fluxDispState = 4;
        digitalWrite(fluxDCPinDown, LOW);
        digitalWrite(fluxDCPinUp, LOW);
        revFluxTimer = millis();
      }
      break;
    
    case 4: //hold time
      if(millis() - revFluxTimer > 100)
      {
        fluxDispState = 5;
        digitalWrite(fluxDCPinDown, LOW);
        digitalWrite(fluxDCPinUp, HIGH);
        revFluxTimer = millis();
      }
      break;
      
    case 5: //pushing up timem
      if(millis() - revFluxTimer > 100)
      {
        fluxDispState = 6;
        digitalWrite(fluxDCPinDown, LOW);
        digitalWrite(fluxDCPinUp, LOW);
        
      }
      break;
      
    case 6: //rotate the revolver
      digitalWrite(enPin3, LOW);
      digitalWrite(dirPin3, LOW);
      revStep.rotateDegrees(360/21*4);
      fluxDispState = 7;
      break;
      
    case 7:
      if(revStep.isDone())
      {
        digitalWrite(enPin3, HIGH);
        fluxDispState = 8;
        revFluxTimer = millis();
      }
      break;
    
    case 8: //No correction needed ideally. wait for tube
      if(millis() - revFluxTimer > 300)
      {
        fluxDispState = 9; //move in the X direction
        //increase counter and ensure we are done
        fluxDispXCounter++;
        if(fluxDispXCounter == 5) //we did all five of them
        {
          fluxDispYCounter++;
          fluxDispState = 10; //move in the Y direction
          if(fluxDispYCounter == 4) //all 20 pieces have been fluxed and wired
          {
            fluxDispState = 100;
          }          
          
        }
      }
      break;
      
    case 9: //do flux movement in X direction and refresh to state 2
      digitalWrite(dirPin4, HIGH); //move in +X
      digitalWrite(enPin4, LOW);
      fluxStep.rotateDegrees((200)*4); //move forward in X
      fluxDispState = 2; //restart the process
      break;
      
    case 10: //move the flux back to original position
      digitalWrite(dirPin4, LOW); //move in -X
      digitalWrite(enPin4, LOW);
      fluxStep.rotateDegrees((800)*4); //move to original position
      fluxDispState = 11; 
      break;
      
    case 11:
      if(fluxStep.isDone())
      {
        digitalWrite(enPin4, HIGH);
        //Move the tray a little bit down
        //move to tray
        digitalWrite(dirPin2, LOW);
        digitalWrite(enPin2, LOW);
        trayStep.rotateDegrees((200)*4);
        fluxDispState = 12;
      }
      break;
      
    case 12:
      if(trayStep.isDone())
      {
        //start up state 3
        digitalWrite(enPin2, HIGH);
        fluxDispState = 3;
        digitalWrite(fluxDCPinDown, HIGH);
        digitalWrite(fluxDCPinUp, LOW);
        revFluxTimer = millis();                        
      }
      break;
      
      
      
    }

    

    
  
    
  if(fluxDispState == 2 || fluxDispState == 11)
    fluxStep.run();
  
  if(fluxDispState == 12)
    trayStep.run();
  
  if(revRelState == 5)
    revStep.run();
    
    
  }
}*/


#include <Servo.h>
#include <Encoder.h>
#include <CustomStepper.h>
#include "SupportFunctionsStructs.h"

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

Servo flipperServo;
Servo cameraServo;




const char flipper_mag_pin = 4;
const char flipperServoPin = 5;
const char cameraServoPin = 11;
const char hopper_pin_fow = 50;
const char hopper_pin_rev = 52;

// Constants for flipper servo positions
const int slidingPos = 25;
const int restingPos = 18;
const int flipPos = 180;
// Constant for camera Servo
const int holdingPos = 80;
const int viewingPos = 15;
//STATE VARIABLES
int cameraState = 100;
unsigned long cameraTime = 0;

int fluxDispState = 100; //starts when revRelState finishes



CustomStepper fluxStep(stepPin4, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);//400, stepPin4, 0);
const int fluxStartingPos = 2270;

unsigned char fluxDispXCounter = 0;
unsigned char fluxDispYCounter = 0;

boolean start = false;
int serialValue = 6;


void setup()
{
  placerSetup();
  
  
  //code for emergency
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);


  
  
  pinMode(hopper_pin_rev,OUTPUT);
  pinMode(hopper_pin_fow,OUTPUT);
  
  pinMode(flipper_mag_pin,OUTPUT);
  
  pinMode(enPin4, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
 
  
  pinMode(flipperServoPin, OUTPUT);
  pinMode(cameraServoPin,OUTPUT);
  
  pinMode(fluxDCPinUp, OUTPUT);
  pinMode(fluxDCPinDown, OUTPUT);
  flipperServo.attach(flipperServoPin);
  cameraServo.attach(cameraServoPin);
  digitalWrite(enPin4, HIGH);
  
  digitalWrite(LED0,LOW);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);
  
  
  flipperServo.write(restingPos);
  cameraServo.write(holdingPos);  
  
    
  cameraTime = millis();
  
  
  Serial.begin(9600);
  while(!Serial.available());
  LEDValue = Serial.read();
  
  //code useful for modification or debug
  //partState = ;
  //partPos = ;
  //partPlacerDone = ;
}

void loop()
{
  if(Serial.available()) {
      serialValue = Serial.read();
      LEDValue = serialValue;
  }
  
  switch(LEDValue){ 
     case '0':
       digitalWrite(LED0,LOW);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;
     case '1':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,LOW);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
     case '2':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,LOW);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
     case '3':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,LOW);
       digitalWrite(LED4,HIGH);
       break;  
     case '4':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,LOW);
       break;  
     case '5':
       start = true;
       break;
         
  }
  /*
  switch(cameraState){
      case 1:
        //HOLD
        digitalWrite(hopper_pin_fow,LOW);
        digitalWrite(hopper_pin_rev,LOW);
        
        flipperServo.write(restingPos);
        cameraServo.write(holdingPos);
        digitalWrite(flipper_mag_pin,LOW);
        if(serialValue != '0' && serialValue != '5' && millis() - cameraTime > 1000){
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
        
        if(millis() - cameraTime > 100){
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
          if(serialValue == '1' ){
            cameraState = 4;
            partPos = 1;
            cameraTime = millis();
          }else if(serialValue == '2'){
            cameraState = 4;
            partPos = 2;
            cameraTime = millis();
          }else if(serialValue == '3'){
            cameraState = 3;
            partPos = 1;
            cameraTime = millis();
          }else if(serialValue == '4'){
            cameraState = 3;
            partPos = 2;
            cameraTime = millis();
          }
                  
        }
        break;
    }      
    
  serialValue = 0; //only accept latest*/
  partPos = 1;
  placerLoop();
}


