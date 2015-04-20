#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#include <CustomStepper.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

const int encoderAPin = 2;
const int encoderBPin = 3;
Encoder myEnc = Encoder(2, 3);

const int flipper_mag_pin = 4;
const int flipperServoPin = 5;
const int partPlacerServoPin =  6;
const int placer_mag_pin = 7;
const int partServoPin = 10;

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


//Stepper partStep = Stepper(400, stepPin, 0);
//Stepper trayStep = Stepper(200, stepPin2, 0);
Stepper revStep = Stepper(6400, stepPin3, 0);
Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partPlacerServo;
Servo partServo; //reorientator
Servo flipperServo;
Servo cameraServo;

//STATE VARIABLES
int cameraState = 1;
unsigned long cameraTime = 0;
int partState = 0;
unsigned long partPlacerTimer = 0;

char partPos = 0;

//add this for partplacer part
char currentPartPos = 0;
CustomStepper partStep(stepPin, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);
CustomStepper trayStep(stepPin2, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 200, 100, CW);
unsigned char partStepperXCounter = 0;
unsigned char partStepperYCounter = 0;








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
  
  partStep.setRPM(800);
  trayStep.setRPM(200);
  revStep.setSpeed(5);
  fluxStep.setSpeed(100);

  partPlacerServo.attach(partPlacerServoPin);
  flipperServo.attach(flipperServoPin);
  cameraServo.attach(cameraServoPin);
  partServo.attach(partServoPin);

  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  
  partPlacerServo.write(restingHeight);
  flipperServo.write(restingPos);
  cameraServo.write(holdingPos);  
  partServo.write(0);
    
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
        digitalWrite(hopper_pin_rev,LOW);
      
      flipperServo.write(restingPos);
      cameraServo.write(holdingPos);  
      digitalWrite(flipper_mag_pin,LOW);
      
      if(serialValue != 0 && millis() - cameraTime > 1000){
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
      
      if(millis() - cameraTime > 400){
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
 
switch(partState){
    
    case 0:
      //wait until signal received
      if(partPos)
      {
        currentPartPos = partPos;
        partState = 1;
        partPlacerTimer = millis();
        
      }
      break;
    
    case 1: //wait a while for part to settle
      if(millis() - partPlacerTimer > 1500)
      {
        partState = 2;
        partPlacerTimer = millis();
        
      }
      break;
    
    case 2:
      digitalWrite(placer_mag_pin,HIGH);
      partPlacerServo.write(cameraHeight);
      if(millis() - partPlacerTimer > 800)
      {
        partState = 3;
        partPlacerTimer = millis();
      }
      break;
    
    case 3:
      partPlacerServo.write(restingHeight);
      if(millis() - partPlacerTimer > 800)
      {
        partPos = 0;
        partState = 4;
      }
      break;
      
    case 4:
      //move to tray
      digitalWrite(dirPin, LOW);
      digitalWrite(enPin, LOW);
      partStep.rotateDegrees((1500 + 200*partStepperXCounter)*4);
      partState = 5;
      break;
      
    case 5:
      partServo.write(170);
      if(partStep.isDone())
      {
        digitalWrite(enPin, HIGH);
        //check if rotation is needed or not
        if(currentPartPos == 2) //rotation is needed
        {
          partState = 6;
        }
        else
        {
          partState = 7;
        }  
        partPlacerTimer = millis();
      }
      break;
      
    case 6:
      //rotate piece
      partState = 7;
      break;
    
    case 7:
      //put piece down
      partPlacerServo.write(trayHeight);
      if(millis() - partPlacerTimer > 800)
      {
        partState = 8;
        digitalWrite(placer_mag_pin,LOW);
        partPlacerTimer = millis();
      }
      break;
    
    case 8:
      partPlacerServo.write(restingHeight);
      if(millis() - partPlacerTimer > 800)
      {
        partState = 9;
        partPlacerTimer = millis();
      }
      break;
      
    case 9: //return back
      digitalWrite(dirPin, HIGH);
      digitalWrite(enPin, LOW);
      partStep.rotateDegrees((1550 + 200*partStepperXCounter)*4);
      partState = 10;
      break;
      
    case 10:
      partServo.write(0);
      if(partStep.isDone())
      {
        digitalWrite(enPin, HIGH);
        //we did it. now we do it again
        partState = 0;
        partStepperXCounter++;
        if(partStepperXCounter == 5) //did the fifth one already
        {
          partStepperYCounter++;
          partStepperXCounter = 0;
          if(partStepperYCounter == 4) //did all four of them
          {
            //we are done
            partState = 100; 
          }
          else
          {
            partState = 11;
            
          }
        }
      }
      break;
      
    case 11:
      //Move the tray a little bit down
      //move to tray
      digitalWrite(dirPin2, LOW);
      digitalWrite(enPin2, LOW);
      trayStep.rotateDegrees((200)*4);
      partState = 12;
      break;
      
    case 12:
      if(trayStep.isDone())
      {
        digitalWrite(enPin2, HIGH);
        //check if rotation is needed or not
        partState = 0;
      }
      break;      
    
     
   
  }      
  //Ensure the code runs when needed
  if(partState == 5 || partState == 10)
    partStep.run();
  if(partState == 12)
    trayStep.run();

}


