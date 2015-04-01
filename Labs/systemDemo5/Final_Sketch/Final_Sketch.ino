//Final Sketch.ino
//Issue: must comment out all code for an individual motor type if there is no motor of that type.
//For Example: if there are no servo pin, we must comment out all code involving servos.


 //variables for the Stepper Motors
float IRDistance[] = {0.0, 0.0, 0.0, 0.0, 0.0}; //scale version of Value[]
const int stepPin[] = {25, 26, 27, 28, 29}; 
const int dirPin[] = {35, 36, 37, 38, 39};
const int enPin[] = {30, 31, 32, 33, 34};
int toggle[] = {0, 0, 0, 0, 0};
float stepDistance[] = {0.0, 0.0, 0.0, 0.0, 0.0};
boolean stepDone[] = {false, false, false, false, false}; //indicate if a stepper motor finished moving

//For our DC motors with encoders(implement)
const int DCEMotorPinA[] = {2, 21, 19};
const int DCEMotorPinB[] = {3, 20, 18};
int encoderAValue[] = {0, 0, 0};
int encoderAPrev[] = {0,0,0};
int encoderBValue[] = {0,0,0};
int encoderBPrev[] = {0,0,0};
int DCMotorAngle = {0,0,0};



//For our DC motors
const int DCMotorPinA[] = {46, 47, 48};
const int DCMotorPinB[] = {50, 51, 52};

//For our Servo motors
const int servoPin[] = {9, 10};

//etc
unsigned char psw = 0;
const int limitsw = 13;
const int elePin = 2;
int ele = 0;

unsigned int j = 0; //our temporary variable for selecting proper index
unsigned int len; //length of iterating arrays

unsigned char serialValue = 0;
float Value[] = {0, 0, 0, 0, 0}; //stepper motor value
unsigned char DCValue[] = {1, 1, 1};
boolean Write[] = {false, false, false, false, false};
boolean DCWrite[] = {false, false, false};
unsigned char servoValue[] = {0, 0};
boolean servoWrite[] = {false, false};
boolean Wrote = false; //Check if system wrote value

//For calibration
boolean calibrated = true; //true ignores calibration step.
unsigned char cState = 0;
boolean cDone = true; //indicates if all motors have moved to the proper place

//Part Placer State setup
unsigned char ppState = 0; //GO_TO_PICKUP
unsigned char image_orientation = 0; //Invalid value to prevent state from transitioning too early
boolean get_orientation = true; //must ensure the orientation is saved throughout the ppStates
const float pickup_loc = 50;
const float drop_loc = 0;
const float tray_drop = 0;

//For time keeping
unsigned long time; //in millisecond
const unsigned long motordelay = 300; //The time for motor to reach bottom



void setup() {
   Serial.begin(9600); 
   while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
   len = sizeof(stepPin)/sizeof(int);
   for(j=0; j<len; j++)
   {  
     pinMode(stepPin[j],OUTPUT);
     pinMode(dirPin[j],OUTPUT);
     pinMode(enPin[j],OUTPUT);
   }
   
   pinMode(elePin, OUTPUT);
   
   
   len = sizeof(DCMotorPinA)/sizeof(int);
   for(j=0; j<len; j++)
   {
     pinMode(DCMotorPinA[j], OUTPUT);
     pinMode(DCMotorPinB[j], OUTPUT);
   }
   
   len = sizeof(servoPin)/sizeof(char);
   for(j=0; j<len; j++)
   {
     pinMode(servoPin[j], OUTPUT);
   }
   
   attachInterrupt(0, PinA, CHANGE);
   attachInterrupt(1, PinB, CHANGE);
   
}

void loop() { 
  if(Serial.available()) //Read value and decide what to do with it
  {
    serialValue = Serial.read();

////Code for GUI: Do not Delete.    
//    
//  Wrote = updateWrite();
//      if( (Wrote == 0) && ( 100 > serialValue) &&  (serialValue >= 90) )
//      {
//        j = serialValue - 90; //get current index
//        Write[j] = true;
//      }
//      else if( (Wrote == false) && ( 110 > serialValue) &&  (serialValue >= 100) )
//      {
//        j = serialValue - 100; //get current index
//        DCWrite[j] = true;
//      }
//      else if( (Wrote == false) && ( 120 > serialValue) &&  (serialValue >= 110) )
//      {
//        j = serialValue - 110;
//        servoWrite[j] = true;
//      }
//      else if( (Wrote == false) && ( (serialValue) == 50))
//      {
//        ele = (!ele) & 0x01;
//      }
//
//Code for computer vision communication.(can only have one ON at a time)
    if(get_orientation)
    {
      image_orientation = serialValue - 30; //converts char number to number
      get_orientation = false;
    }
  } //attributed sensor readings
  
  //Reading any other essential inputs
  psw = digitalRead(limitsw);
  //Implementation of calibration
  
  if(calibrated == false)
  {
    //perform calibration
    switch(cState)
    {
      case 0: //pull DC up
        DCValue[0] = 0; //Must verify this!!!!
        if(psw == 1) //Must Verify this!!!
        {
          DCValue[0] = 1; //Stop the DC
          cState = 1; //transition to next step
          //set new coordinates
          len = sizeof(stepPin)/sizeof(int);
          for(j=0; j<len; j++)
          {  
            Value[j] = 255;
          }
        }
        break;
        
      case 1: //Stepper goes to 255
        len = sizeof(stepPin)/sizeof(int);
        cDone = true;
        for(j=0; j<len; j++)
        {  
          cDone = cDone && stepDone[j];
        }
        if(cDone) //all components are finished moving
        {
          cState = 2;
          len = sizeof(stepPin)/sizeof(int);
          for(j=0; j<len; j++)
          {  
            Value[j] = 0;
          }
        }
        break;
        
      case 2: //Stepper goes to 0
        len = sizeof(stepPin)/sizeof(int);
        cDone = true;
        for(j=0; j<len; j++)
        {  
          cDone = cDone && stepDone[j];
        }
        calibrated = cDone; //we are done!
        break;
              
        
    }
  }
  else
  {
    //implement all states here
    //using cDone as a temporary variable on boolean checks
    
    //implementation of ppState
    switch(ppState)
    {
      case 0: //GO_TO_PICKUP
        cDone = (Value[1] == pickup_loc);
        Value[1] = pickup_loc; 
        if(cDone && stepDone[1] && (image_orientation != 0)) 
        { //the stepDone array has been updated and signals that the stepper finished moving and we got an orientation
          ppState = 1; //T2.1
          time = millis(); //reset timer         
        }
        break;
      
      case 1: //EXTEND
        //implement timing directions
        DCValue[0] = 2; //should go down
        if(millis() - time > motordelay)
        {
          DCValue[0] = 1; //stop
          ppState = 2;
        }
        break;
      
      case 2: //RETRACT
        ele = 1; //turn on magnet
        DCValue[0] = 0; //Ensure this is DC up
        if(psw == 1) //Must Verify this!!!
        {
          DCValue[0] = 1; //Stop the DC
          if(image_orientation == 1 || image_orientation == 3)
          {
            ppState = 4; //Go to Drop off
          }
          else if(image_orientation == 2 || image_orientation == 4)
          {
            ppState = 3;//perform twist
          }
        }
        break;
        
      case 3: //TWIST
        //implement timing directions
        DCValue[0] = 2; //should go down
        if(millis() - time > motordelay)
        {
          DCValue[0] = 1; //stop
          ppState = 4;
        }
        break;
        
      case 4: //GO_TO_DROP_OFF(This section needs to account tray position TODO)
        cDone = (Value[1] == drop_loc);
        Value[1] = drop_loc;
        Value[0] = tray_drop; //ensure
        if(cDone && stepDone[1] && stepDone[0] && (image_orientation != 0)) 
        { //the stepDone array has been updated and signals that the stepper finished moving and we got an orientation
          ppState = 5; //T2.6
          time = millis();         
        }
        break;
        
        
      case 5: //DROP_PART(copy of extend state
        //implement timing
        ppState = 6;
        DCValue[0] = 2; //should go down
        if(millis() - time > motordelay)
        {
          DCValue[0] = 1; //stop
          ppState = 2;
        }
        break;
        
      case 6: //RESET(copy of retract)
        ele = 0; //turn off magnet
        DCValue[0] = 0; //Ensure this is DC up
        if(psw == 1) //Must Verify this!!!
        {
          DCValue[0] = 1; //Stop the DC
          ppState = 0;
          get_orientation = true;
        }
        break;
      
    }
    
    
    //additional state control
    
    
    
  }
  
  
  
  
  
  //Update each motor properly

  //Stepper Motor controlled by IR sensor
  len = sizeof(stepPin)/sizeof(int);
  for(j=0; j<len; j++)
  {
    IRDistance[j] = (Value[j]*2.5)/(255*2.5); //approx distance in cm
    //Motor 1
    if(stepDistance[j] < IRDistance[j]-.005 && IRDistance[j] < 2.0){
       digitalWrite(enPin[j], LOW);
       digitalWrite(dirPin[j], HIGH);
       toggle[j] = (!toggle[j]) & 0x01;
       digitalWrite(stepPin[j], toggle[j]);
       stepDistance[j] += .001;
       stepDone[j] = false;
    }else if(stepDistance[j] > IRDistance[j]+.005 && IRDistance[j] < 2.0){
      digitalWrite(enPin[j], LOW);
      digitalWrite(dirPin[j], LOW);
      toggle[j] = (!toggle[j]) & 0x01;
      digitalWrite(stepPin[j], toggle[j]);
      stepDistance[j] -= .001;
      stepDone[j] = false;
    }
    else {
      digitalWrite(enPin[j], HIGH);
      stepDone[j] = true;
    }
  }
  
  //DC Motor Implementation
  len = sizeof(DCWrite)/sizeof(boolean);
  for(j=0; j<len; j++)
  {
    switch(DCValue[j]) {
      case 0:
        //turn left
        digitalWrite(DCMotorPinA[j],LOW);
        digitalWrite(DCMotorPinB[j],HIGH);
        break;
      case 1:
        digitalWrite(DCMotorPinA[j],LOW);
        digitalWrite(DCMotorPinB[j],LOW);
        break;
      case 2:
        digitalWrite(DCMotorPinA[j],HIGH);
        digitalWrite(DCMotorPinB[j],LOW);
      
    }
  }

  //Servo Motor implementation
  len = sizeof(servoPin)/sizeof(char);
   for(j=0; j<len; j++)
   {
     
     analogWrite(servoPin[j],servoValue[j]);
     //ensure it finished moving
   }
  
  
  // Write Pin
  digitalWrite(elePin, ele);
  
  delay(1); //For fast speed
  
  
  Serial.flush();
}


boolean updateWrite()
{
    //Stepper Case
    len = sizeof(Write)/sizeof(boolean);
    for(j=0; j<len; j++)
    {
      if(Write[j])
      { //update value return true
        Value[j] = serialValue;
        Write[j] = false;
        return true;
      }
    }
    //DC Motor Case
    len = sizeof(DCWrite)/sizeof(boolean);
    for(j=0; j<len; j++)
    {
      if(DCWrite[j])
      { //update value return true
        DCValue[j] = serialValue;
        DCWrite[j] = false;
        return true;
      }
    } 
    
    //Servo Motor Case
   len = sizeof(servoPin)/sizeof(char);
   for(j=0; j<len; j++)
   {
     if(servoWrite[j])
     {
       servoValue[j] = serialValue;
       servoWrite[j] = false;
       return true;
     }
   }
  
    return false; //No writing required  
}

//interrupt handling
void PinA(){
   encoderAPrev = encoderAValue;
   encoderAValue = digitalRead(encoderAPin);
  if(encoderAPrev){
    if(encoderBPrev){
      //counterclockwise
      DCMotorAngle -= 4;
    } else{
      //clockwise
      DCMotorAngle += 4;
    }  
  }else{
    if(encoderBPrev){
      //clockwise
      DCMotorAngle += 4;
    } else{
      //counterclockwise
      DCMotorAngle -= 4;
    }
  } 
}

void PinB(){
   encoderBPrev = encoderBValue;
   encoderBValue = digitalRead(encoderBPin);
  if(encoderBPrev){
    if(encoderAPrev){
      //clockwise
      DCMotorAngle += 4;
    } else{
      //counterclockwise
      DCMotorAngle -= 4;
    }  
  }else{
    if(encoderAPrev){
      //counterclockwise
      DCMotorAngle -= 4;
    } else{
      //clockwise
      DCMotorAngle += 4;
    }
  } 
}
