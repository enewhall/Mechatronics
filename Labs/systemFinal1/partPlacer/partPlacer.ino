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
const int slidePos = 18;
const int restingPos = 18;
const int flipPos = 180;
// Constant for camera Servo
const int holdingPos = 80;
const int viewingPos = 15;


//Stepper partStep = Stepper(400, stepPin, 0);
//Stepper trayStep = Stepper(200, stepPin2, 0);
//Stepper revStep = Stepper(6400, stepPin3, 0);
//Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partPlacerServo;
Servo partServo; //reorientator
Servo flipperServo;
Servo cameraServo;

//already added in the original
char partPos = 2;


//add this for partplacer part
char currentPartPos = 0;
unsigned long partPlacerTimer = 0;
CustomStepper partStep(stepPin, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);
CustomStepper trayStep(stepPin2, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 200, 100, CW);
unsigned char partStepperXCounter = 0;
unsigned char partStepperYCounter = 0;
unsigned char fluxDispXCounter = 0;
unsigned char fluxDispYCounter = 0;


//STATE VARIABLE
int partState = 0;

//For the revolver preloading
int revRelState = 0;
int fluxDispState = 100;
unsigned char revRelCount = 0;
unsigned long revFluxTimer = 0;
bool partPlacerDone = false;
CustomStepper revStep(stepPin3, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 6400, 5, CW);
CustomStepper fluxStep(stepPin4, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);//400, stepPin4, 0);
const int fluxStartingPos = 100;



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
  partStep.setDirection(CW);
  trayStep.setRPM(800);
  trayStep.setDirection(CW);
  //
  revStep.setRPM(10);
  revStep.setDirection(CW);
  //
  fluxStep.setRPM(100);
  fluxStep.setDirection(CW);
  //

  partPlacerServo.attach(partPlacerServoPin);
  flipperServo.attach(flipperServoPin);
  cameraServo.attach(cameraServoPin);
  partServo.attach(partServoPin);

  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  
  partPlacerServo.write(restingHeight);
  partServo.write(0);
  flipperServo.write(restingPos);
  //cameraServo.write(holdingPos);  
  cameraServo.write(viewingPos);
  //
  while(!Serial.available())
  {
    ;
  }
  Serial.read();
  //
}

void loop() {
  
    
  switch(revRelState){
    case 0:
      digitalWrite(wirefeederPin, HIGH);
      revFluxTimer = millis();
      revRelState = 1;
      break;
      
    case 1:
      if(millis() - revFluxTimer > 300)
      {
        digitalWrite(wirefeederPin, LOW);
        revRelState = 2;
        Serial.println("enetering 2");
      }
      break;
      
    case 2:
      digitalWrite(DCCutterPinCut, HIGH);
      digitalWrite(DCCutterPinRelease, LOW);
      if(myEnc.read() >= 2100)
      {
         digitalWrite(DCCutterPinCut, LOW);
         digitalWrite(DCCutterPinRelease, LOW);   
         revRelState = 3;
         Serial.println("2 entering 3");
      } 
      break;
      
    case 3:
      digitalWrite(DCCutterPinCut, LOW);
      digitalWrite(DCCutterPinRelease, HIGH);
      if(myEnc.read() <= 29)
      {
         Serial.println("finishing 3");
         digitalWrite(DCCutterPinCut, LOW);
         digitalWrite(DCCutterPinRelease, LOW);   
         revRelState = 4;
      } 
      break;
      
    case 4: //rotate the revolver
      digitalWrite(enPin3, LOW);
      digitalWrite(dirPin3, LOW);
      revStep.rotateDegrees(360/21*4);
      revRelState = 5;
      break;
      
    case 5:
      if(revStep.isDone())
      {
        digitalWrite(enPin3, HIGH);
        revRelState = 0;
        revRelCount++;
        if(revRelCount == 20) //inserted in all the 20 pieces
        {
          revRelState = 100;
          fluxDispState = 0;
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
      digitalWrite(dirPin4, HIGH); //move in -X
      digitalWrite(enPin4, LOW);
      fluxStep.rotateDegrees((fluxStartingPos)*4); //need modification
      fluxDispState = 2;
      break;
      
    case 2:
      if(fluxStep.isDone())
      {
        digitalWrite(enPin4, HIGH);
        fluxDispState = 3;
        digitalWrite(fluxDCPinDown, HIGH);
        digitalWrite(fluxDCPinUp, LOW);
        revFluxTimer = millis();
      }
      break;
      
    case 3: //pushing down time
      if(millis() - revFluxTimer > 220)
      {
        fluxDispState = 4;
        digitalWrite(fluxDCPinDown, LOW);
        digitalWrite(fluxDCPinUp, LOW);
        revFluxTimer = millis();
      }
      break;
    
    case 4: //hold time
      if(millis() - revFluxTimer > 60)
      {
        fluxDispState = 5;
        digitalWrite(fluxDCPinDown, LOW);
        digitalWrite(fluxDCPinUp, HIGH);
        revFluxTimer = millis();
      }
      break;
    
    case 5: //pushing up time
      if(millis() - revFluxTimer > 150)
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
      digitalWrite(dirPin4, LOW); //move in +X
      digitalWrite(enPin4, LOW);
      fluxStep.rotateDegrees((200)*4); //move forward in X
      fluxDispState = 2; //restart the process
      break;
      
    case 10: //move the flux back to original position
      digitalWrite(dirPin4, HIGH); //move in -X
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

/*case 3:
      // Move placer to get part
      digitalWrite(dirPin, HIGH);
      digitalWrite(enPin, LOW);
      partStep.step(5280);
      digitalWrite(enPin, HIGH);            
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
     break;*/
