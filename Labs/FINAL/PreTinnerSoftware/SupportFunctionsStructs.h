//Introduce structures and Functions that simplifies code
//For the States

#define STEPPERINIT(dirPin, enPin, stepPin, SPR, RPM) {CustomStepper(stepPin, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, SPR, RPM, CW), dirPin, enPin, stepPin}
#define DCINIT(pinUp, pinDown) {0, pinUp, pinDown}
#define DCENCINIT(pinUp, pinDown, pinA, pinB) {Encoder(pinA, pinB), pinUp, pinDown}

struct StepperStruct {
  CustomStepper Step;
  byte dirPin;
  byte enPin;
  byte stepPin;
};

struct DCStruct {
  unsigned long time_t;
  byte pinUp;
  byte pinDown;  
};

struct DCEncStruct {
  Encoder enc;
  byte pinUp;
  byte pinDown;  
};

//Stepper structure functions

void rotateDegrees(StepperStruct * stepper, float deg, byte dirSig )
{
  digitalWrite(stepper->dirPin, dirSig);
  digitalWrite(stepper->enPin, LOW);
  stepper->Step.rotateDegrees(deg);  
}

bool Done(StepperStruct * stepper)
{
  if(stepper->Step.isDone())
  {
    digitalWrite(stepper->enPin, HIGH);
    return true;
  }
  return false;
}

void StepperSetup(StepperStruct * stepper)
{
  pinMode(stepper->dirPin,OUTPUT);
  pinMode(stepper->enPin, OUTPUT);
  pinMode(stepper->stepPin, OUTPUT);
}

//DCStructure
void rotateUp(DCStruct * DC)
{
  digitalWrite(DC->pinUp, HIGH);
  digitalWrite(DC->pinDown, LOW);
  //reset time
  DC->time_t = millis();
}

void rotateDown(DCStruct * DC)
{
  digitalWrite(DC->pinUp, LOW);
  digitalWrite(DC->pinDown, HIGH);
  //reset time
  DC->time_t = millis();
}

void rotateUp(DCEncStruct * DC)
{
  digitalWrite(DC->pinUp, HIGH);
  digitalWrite(DC->pinDown, LOW);
}

void rotateDown(DCEncStruct * DC)
{
  digitalWrite(DC->pinUp, LOW);
  digitalWrite(DC->pinDown, HIGH);
}

bool encoderGreater(DCEncStruct * DC, int steps)
{
  if(DC->enc.read() > steps)
  {
    digitalWrite(DC->pinUp, LOW);
    digitalWrite(DC->pinDown, LOW);
    return true;
  }
  return false;
}

bool encoderLess(DCEncStruct * DC, int steps)
{
  if(DC->enc.read() < steps)
  {
    digitalWrite(DC->pinUp, LOW);
    digitalWrite(DC->pinDown, LOW);
    return true;
  }
  return false;
}

bool TimerElapsed(DCStruct * DC, unsigned long elapse)
{
  if(millis() - DC->time_t > elapse)
  {
    digitalWrite(DC->pinUp, LOW);
    digitalWrite(DC->pinDown, LOW);
    return true;
  }
  return false;
  
}

void DCSetup(DCStruct * DC)
{
  pinMode(DC->pinUp,OUTPUT);
  pinMode(DC->pinDown,OUTPUT);
}

void DCSetup(DCEncStruct * DC)
{
  pinMode(DC->pinUp,OUTPUT);
  pinMode(DC->pinDown,OUTPUT);
}

//General Timer function
bool TimerElapsed(unsigned long time_t, unsigned long elapse)
{
  return (millis() - time_t) > elapse;
  
}


//initializing variables that should be accessed by all files

byte partPos = 0;

