//Servo and magnets
const char partPlacerServoPin =  6;
const char placer_mag_pin = 7;
const char partReorientatorServoPin = 10;


// Constants for part servo servo positions
const int cameraHeight = 125;
const int trayHeight = 59;
const int restingHeight = 0;

Servo partPlacerServo;
Servo partServo; //reorientator

//const char dirPin = 43;
//const char enPin = 45;
//const char stepPin = 47;




StepperStruct partStep = STEPPERINIT(43,45,47,400,800);
unsigned long partPlacerTimer = 0;

byte currentPartPos;
unsigned char partStepperXCounter = 0;
unsigned char partStepperYCounter = 0;


void placerSetup() {
  pinMode(placer_mag_pin,OUTPUT);
  pinMode(partPlacerServoPin, OUTPUT);
  StepperSetup(&partStep);
  StepperSetup(&trayStep);
  partPlacerServo.attach(partPlacerServoPin);
  partServo.attach(partReorientatorServoPin);
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
        if(partStepperYCounter != 0) //ignore first
          partState = 1;
        else
          partState = 11;
        partState = 1;
        
        partPlacerTimer = millis();
        
      }
      break;
    
    case 1: //wait a while for part to settle
      if(millis() - partPlacerTimer > 1000)
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
        partState = 11;
      }
      break;
      
    case 11: //update counter
      partState = 0;
      partStepperXCounter++;
      if(partStepperXCounter == 5) //did the fifth one already
      {
        partStepperYCounter++;
        partStepperXCounter = 0;
        if(partStepperYCounter == 4) //did all four of them
        {
          //prepare the flux dispenser state
          partState = 14; 
        }
        else
        {
          partState = 12;
          
        }
      }
      break;
      
    case 12:
      //Move the tray a little bit down
      //move to tray
      rotateDegrees(&trayStep, (400)*4, LOW);
      partState = 13;
      break;
      
    case 13:
      if(Done(&trayStep))
      {
        //Start placing the pieces again
        partState = 0; //Debug: originally the code
      }
      break;
  
    case 14:
      //move the tray to the proper part in the code
      rotateDegrees(&trayStep, (2275)*4, LOW); //2*(2300 - 600)
      partState = 15;
      break;
  
    case 15: //flux is now ready to write upon
      if(Done(&trayStep)) 
      {
        partPlacerDone = true;
        revRelState = 0;
        partState = 100;
      }
      break;      
  }

  //Ensure the code runs when needed
  if(partState == 5 || partState == 10)
  {
    partStep.Step.run();
  }
  if(partState == 13 || partState == 15)
    trayStep.Step.run();
    
  
}


