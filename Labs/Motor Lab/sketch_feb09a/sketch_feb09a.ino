int potPin = A1;
float potAngle = 0.0;

int encoderAPin = A4;
int encoderBPin = A5;
int encoderAValue = 0;
int encoderAPrev = 0;
int encoderBValue = 0;
int encoderBPrev = 0;

int DCMotorAngle = 0;
int DCMotorPinA = 7;
int DCMotorPinB = 7;

int IRPin = A0;
float IRDistance = 0.0;
int stepPin = 6; 
int dirPin = 5;
int toggle = 0;
float stepDistance = 0.0;

int limitSwitchPin = 4;

int flexPin = A2;
int servoPin = A3;

const int OFF_STATE = 0;
const int SERVO_STATE = 1;
const int DC_STATE = 2;
const int STEP_STATE = 3;

int state = OFF_STATE;

int button = HIGH;

void setup() {
   Serial.begin(9600); 
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
   
}

void loop() {
  //debounce handled in hardware 
  if(digitalRead(limitSwitchPin) == HIGH && button == LOW){
    state = (state+1)%4; 
  }
  button = digitalRead(limitSwitchPin);
  
  
  /* 
  switch(state){
    case OFF_STATE:
      digitalWrite(DCMotorPinA,LOW);
      digitalWrite(DCMotorPinB,LOW);
      break;
    case SERVO_STATE:
      //Servo Controlled by flex sensor
      analogWrite(servoPin,(analogRead(flexPin)-1.4)*4.4);
      digitalWrite(DCMotorPinA,LOW);
      digitalWrite(DCMotorPinB,LOW);
      break;
    case DC_STATE:
       //DC Motor Controlled by Potiometer and encoder
      encoderAPrev = encoderAValue;
      encoderAValue = digitalRead(encoderAPin);
      
      encoderBPrev = encoderBValue;
      encoderBValue = digitalRead(encoderBPin);
      
      if(encoderAPrev != encoderAValue || encoderBPrev != encoderBValue){
        DCMotorAngle = (DCMotorAngle+4)%360;
      }
      
      potAngle = analogRead(potPin)*5*360/1024;
      if(potAngle < DCMotorAngle - 4){
        digitalWrite(DCMotorPinA,LOW);
        digitalWrite(DCMotorPinB,HIGH);
      }else if(potAngle > DCMotorAngle + 4){
        digitalWrite(DCMotorPinA,HIGH);
        digitalWrite(DCMotorPinB,LOW);
      }else{
        digitalWrite(DCMotorPinA,LOW);
        digitalWrite(DCMotorPinB,LOW);
      }    
      break;
    case STEP_STATE:
      //Stepper Motor controlled by IR sensor
      IRDistance = 20/((float)analogRead(IRPin)); //approx distance in cm
      if(stepDistance < IRDistance - 1){
         digitalWrite(dirPin, HIGH);
         toggle = (!toggle) & 0x01;
      }else if(stepDistance > IRDistance + 1){
        digitalWrite(dirPin, LOW);
        toggle = (!toggle) & 0x01;
      }
      digitalWrite(DCMotorPinA,LOW);
      digitalWrite(DCMotorPinB,LOW);
      break;
    default:
     Serial.write("Error: unknown state");
     digitalWrite(DCMotorPinA,LOW);
     digitalWrite(DCMotorPinB,LOW);
     delay(10000);
     break; 
  }
*/    
  delay(500);                   
  Serial.flush();
}

