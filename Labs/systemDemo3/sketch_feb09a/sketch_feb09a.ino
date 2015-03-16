//variables for the three Stepper Motor
float IRDistance[] = {0.0, 0.0};
const int stepPin[] = {6, 4}; 
const int dirPin[] = {5, 10};
const int enPin[] = {9, 12};
int toggle[] = {0, 0};
float stepDistance[] = {0.0, 0.0};

//For our DC motors
int DCMotorPinA[] = {7};
int DCMotorPinB[] = {8};

//etc
const int limitsw = 13;
const int elePin = 2;
int ele = 0;

unsigned int j = 0; //our temporary variable for selecting proper index
unsigned int len; //length of iterating arrays

unsigned char serialValue = 0;
float Value[] = {0, 0}; //for GUI
unsigned char DCValue[] = {1};
boolean Write[] = {false, false};
boolean DCWrite[] = {false};
boolean Wrote = false; //Check if system wrote value

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
   
   pinMode(limitsw, INPUT);
   pinMode(elePin, OUTPUT);
   
   
   len = sizeof(DCMotorPinA);
   for(j=0; j<len; j++)
   {
     pinMode(DCMotorPinA[j], OUTPUT);
     pinMode(DCMotorPinB[j], OUTPUT);
   }
}

void loop() { 
  if(Serial.available()) //Read value and decide what to do with it
  {
    serialValue = Serial.read();
    Wrote = updateWrite();
    if( (Wrote == 0) && ( 100 > serialValue) &&  (serialValue >= 90) )
    {
      j = serialValue - 90; //get current index
      Write[j] = true;
    }
    else if( (Wrote == false) && ( 110 > serialValue) &&  (serialValue >= 100) )
    {
      j = serialValue - 100; //get current index
      DCWrite[j] = true;
    }
    else if( (Wrote == false) && ( (serialValue) == 50))
    {
      ele = (!ele) & 0x01;
    }
  } //attributed sensor readings

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
    }else if(stepDistance[j] > IRDistance[j]+.005 && IRDistance[j] < 2.0){
      digitalWrite(enPin[j], LOW);
      digitalWrite(dirPin[j], LOW);
      toggle[j] = (!toggle[j]) & 0x01;
      digitalWrite(stepPin[j], toggle[j]);
      stepDistance[j] -= .001;
    }
    else {
      digitalWrite(enPin[j], HIGH);
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
  
    return false; //No writing required  
}


