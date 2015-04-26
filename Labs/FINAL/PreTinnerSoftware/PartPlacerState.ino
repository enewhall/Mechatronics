//Servo and magnets
const char partPlacerServoPin =  6;
const char placer_mag_pin = 7;
const char partServoPin = 10;


// Constants for part servo servo positions
const int cameraHeight = 130;
const int trayHeight = 59;
const int restingHeight = 0;

Servo partPlacerServo;
Servo partServo; //reorientator

//const char dirPin = 35;
//const char enPin = 45;
//const char stepPin = 47;

//const char dirPin2 = 49;
//const char enPin2 = 51;
//const char stepPin2 = 53;


StepperStruct partStep = STEPPERINIT(35,45,47,400,400);
StepperStruct trayStep = STEPPERINIT(49,51,53,200,800);

int partState = 0;
unsigned long partPlacerTimer = 0;
byte partPos = 0;
byte currentPartPos;
unsigned char partStepperXCounter = 0;
unsigned char partStepperYCounter = 0;
bool partPlacerDone = false;

void placerSetup() {
  pinMode(placer_mag_pin,OUTPUT);
  pinMode(partPlacerServoPin, OUTPUT);
  StepperSetup(&partStep);
  StepperSetup(&trayStep);
  partPlacerServo.attach(partPlacerServoPin);
  partServo.attach(partServoPin);
  //initial values
  digitalWrite(partStep.enPin, HIGH);
  digitalWrite(trayStep.enPin, HIGH);
  partServo.write(0);
  partPlacerServo.write(restingHeight);
  
  
}

void placerLoop() {
  
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
      rotateDegrees(&partStep, (1500 + 200*partStepperXCounter)*4, LOW);
      if(currentPartPos == 2)//ideally rotate as it moves
        partServo.write(170);
      partState = 5;
      break;
      
    case 5:
      if(Done(&partStep))
      {
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
      rotateDegrees(&partStep, (1550 + 200*partStepperXCounter)*4, HIGH);
      partState = 10;
      break;
      
    case 10:
      partServo.write(0); //ensure the servo is unrotated
      if(Done(&partStep))
      {
        //ensure we create a 5 by 4 layout of the parts
        //We will be using the X and Y counter to count
        //how much of the layout has been completed
        partState = 0;
        partStepperXCounter++;
        if(partStepperXCounter == 5) //did the fifth one already
        {
          partStepperYCounter++;
          partStepperXCounter = 0;
          if(partStepperYCounter == 4) //did all four of them
          {
            //prepare the flux dispenser state
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
      rotateDegrees(&trayStep, (400)*4, HIGH);
      partState = 12;
      break;
      
    case 12:
      if(Done(&trayStep))
      {
        //Start placing the pieces again
        partState = 0;
      }
      break;
  
    case 13:
      //move the tray to the proper part in the code
      rotateDegrees(&trayStep, (3400)*4, HIGH); //2*(2300 - 600)
      partState = 14;
      break;
  
    case 14: //flux is now ready to write upon
      if(Done(&trayStep)) 
      {
        partPlacerDone = true;
        partState = 100;
      }
      break;      
  }

  //Ensure the code runs when needed
  if(partState == 5 || partState == 10)
  {
    partStep.Step.run();
  }
  if(partState == 12 || partState == 14)
    trayStep.Step.run();
    
  
}


