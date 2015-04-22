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


//STATE VARIABLES
int cameraState = 100;
unsigned long cameraTime = 0;
int partState = 100;
unsigned long partPlacerTimer = 0;

char partPos = 2;

//add this for partplacer part
char currentPartPos = 0;
CustomStepper partStep(stepPin, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);
CustomStepper trayStep(stepPin2, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 200, 100, CW);
unsigned char partStepperXCounter = 0;
unsigned char partStepperYCounter = 0;


//For the revolver preloading
int revRelState = 100; //4
int fluxDispState = 0; //starts when revRelState finishes
unsigned char revRelCount = 0;
unsigned long revFluxTimer = 0;
bool partPlacerDone = true; //remember
CustomStepper revStep(stepPin3, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 6400, 5, CW);
CustomStepper fluxStep(stepPin4, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);//400, stepPin4, 0);
const int fluxStartingPos = 2270;

unsigned char fluxDispXCounter = 0;
unsigned char fluxDispYCounter = 0;

boolean start = false;
int serialValue = 6;

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
  
  partStep.setRPM(400);
  trayStep.setRPM(800);
  revStep.setRPM(10);
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
  cameraServo.write(holdingPos);  
  partServo.write(0);
    
  cameraTime = millis();
     
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
        //digitalWrite(enPin, LOW );
        digitalWrite(dirPin, LOW);
        partStep.rotateDegrees((1500 + 200*partStepperXCounter)*4);
        if(currentPartPos == 2)//ideally rotate as it moves
          partServo.write(170);
        partState = 5;
        break;
        
      case 5:
        if(partStep.isDone())
        {
          digitalWrite(enPin, HIGH);
          //check if rotation is needed or not
          partState = 7;  
          partPlacerTimer = millis();
        }
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
        Serial.println("Should be turning back");
        //digitalWrite(dirPin, HIGH);
        //digitalWrite(enPin, LOW);
        partStep.rotateDegrees((1550 + 200*partStepperXCounter)*4);
        partState = 10;
        break;
        
      case 10:
        partServo.write(0); //ensure the servo is unrotated
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
              partState = 13; 
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
        digitalWrite(dirPin2, HIGH);
        digitalWrite(enPin2, LOW);
        trayStep.rotateDegrees((400)*4);
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
    
      case 13:
        //move the tray to the proper part in the code
        digitalWrite(dirPin2, HIGH);
        digitalWrite(enPin2, LOW);
        trayStep.rotateDegrees((3400)*4); //2*(2300 - 600)
        partState = 14;
        break;
    
      case 14: //flux is now ready to write upon
        if(trayStep.isDone()) 
        {
          digitalWrite(enPin2, HIGH);
          partPlacerDone = true;
          partState = 100;
        }
        break;      
     }
    
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

    

    
  //Ensure the code runs when needed
  if(partState == 5 || partState == 10)
  {
    partStep.run();
  }
  if(partState == 12 || partState == 14)
    trayStep.run();
    
    
  if(fluxDispState == 2 || fluxDispState == 11)
    fluxStep.run();
  
  if(fluxDispState == 12)
    trayStep.run();
  
  if(revRelState == 5)
    revStep.run();
    
    
  }
}


