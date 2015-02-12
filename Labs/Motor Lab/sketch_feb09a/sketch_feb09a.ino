int potPin = A1;
float potAngle = 0.0;

int encoderAPin = 2;
int encoderBPin = 3;
int encoderAValue = 0;
int encoderAPrev = 0;
int encoderBValue = 0;
int encoderBPrev = 0;

int DCMotorAngle = 0;
int DCMotorPinA = 7;
int DCMotorPinB = 8;

int IRPin = A0;
float IRDistance = 0.0;
int stepPin = 6; 
int dirPin = 5;
int toggle = 0;
float stepDistance = 0.0;

int limitSwitchPin = 4;

int flexPin = A2;
int servoPin = 9;

const int OFF_STATE = 0;
const int SERVO_STATE = 1;
const int DC_STATE = 2;
const int STEP_STATE = 3;

int state = OFF_STATE;

int button = HIGH;

char serialValue = 0;
float primaryValue = 0; //for GUI
float secondaryValue = 0;
boolean sensorUse = true;
boolean primaryWrite = false;
boolean secondaryWrite = false;
float sensorValue;

void setup() {
   Serial.begin(9600); 
   while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
   pinMode(potPin,INPUT);
   
   pinMode(limitSwitchPin,INPUT);
   
   pinMode(encoderAPin,INPUT);
   pinMode(encoderBPin,INPUT);
   
   pinMode(DCMotorPinA,OUTPUT);
   pinMode(DCMotorPinB,OUTPUT);
   
   pinMode(IRPin,INPUT);
   
   pinMode(flexPin,INPUT);
   pinMode(servoPin,OUTPUT);
   
   pinMode(stepPin,OUTPUT);
   pinMode(dirPin,OUTPUT);

  attachInterrupt(0, PinA, CHANGE);
  attachInterrupt(1, PinB, CHANGE);

   
}

void loop() { 
  if(Serial.available())
  {
    serialValue = Serial.read();
    if(primaryWrite)
    {
      primaryValue = serialValue;
      primaryValue = serialValue;
      primaryWrite = false;
    }
    else if(secondaryWrite)
    {
      secondaryValue = serialValue;
      secondaryWrite = false;
    }
    else if(serialValue == 30)
    {
      primaryWrite = true;
    }
    else if(serialValue == 80)
    {
      secondaryWrite = true;
    }
    else if(serialValue == 100)
    {
      sensorUse = true;
    }
    else if(serialValue == 101)
    {
      sensorUse = false;
    }
  } //attributed sensor readings


  if(digitalRead(limitSwitchPin) == HIGH && button == LOW){
    state = (state+1)%4; 
  }
  button = digitalRead(limitSwitchPin);
  
   
  switch(state){
    case OFF_STATE:
      digitalWrite(DCMotorPinA,LOW);
      digitalWrite(DCMotorPinB,LOW);
      analogWrite(servoPin,0);
      Serial.println("OFF_STATE");
      break;
    case SERVO_STATE:
      //Servo Controlled by flex sensor
      sensorValue = (analogRead(flexPin)-1.4)*4.4;
      if(sensorUse)
        primaryValue = sensorValue; // copy
      analogWrite(servoPin,primaryValue);
      digitalWrite(DCMotorPinA,LOW);
      digitalWrite(DCMotorPinB,LOW);
      Serial.print("SERVO_STATE: FLEX reading: ");
      Serial.println(sensorValue);
      break;
    case DC_STATE:
       //DC Motor Controlled by Potiometer and encoder
   
      potAngle = analogRead(potPin);
      if(!sensorUse)
        potAngle = 40*primaryValue; // copy
      analogWrite(servoPin,potAngle);
      if(potAngle < DCMotorAngle - 8.0){
        digitalWrite(DCMotorPinA,LOW);
        digitalWrite(DCMotorPinB,HIGH);
      }else if(potAngle > DCMotorAngle + 8.0){
        digitalWrite(DCMotorPinA,HIGH);
        digitalWrite(DCMotorPinB,LOW);
      }else{
        digitalWrite(DCMotorPinA,LOW);
        digitalWrite(DCMotorPinB,LOW);
      }
      Serial.print("DC_STATE: Angle for pot and Motor: ");
      Serial.print(potAngle);
      Serial.print(" ");
      Serial.println(DCMotorAngle);
      
      analogWrite(servoPin,0);    
      break;
    case STEP_STATE:
      //Stepper Motor controlled by IR sensor
      IRDistance = 200/((float)analogRead(IRPin)); //approx distance in cm
   
      if(stepDistance < IRDistance-.005 && IRDistance < 2.0){
         digitalWrite(dirPin, HIGH);
         toggle = (!toggle) & 0x01;
         digitalWrite(stepPin, toggle);
         stepDistance += .001;
      }else if(stepDistance > IRDistance+.005 && IRDistance < 2.0){
        digitalWrite(dirPin, LOW);
        toggle = (!toggle) & 0x01;
        digitalWrite(stepPin, toggle);
        stepDistance -= .001;
      }
      digitalWrite(DCMotorPinA,LOW);
      digitalWrite(DCMotorPinB,LOW);
      analogWrite(servoPin,0);
      Serial.print("STEP_STATE: IRDistance reading: ");
      Serial.println(IRDistance);
      break;
    default:
     Serial.write("Error: unknown state");
     digitalWrite(DCMotorPinA,LOW);
     digitalWrite(DCMotorPinB,LOW);
     analogWrite(servoPin,0);
     delay(10000);
     break; 
  }    
  
  Serial.flush();
}


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










