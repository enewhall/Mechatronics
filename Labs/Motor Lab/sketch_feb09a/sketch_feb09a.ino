int potPin = A1;
float potAngle = 0.0;

int encoderAPin = 2;
int encoderBpin = 3;
int encoderAValue = 0;
int encoderAprev = 0;
int encoderB = 0;
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
int state = 1;

int flexPin = A2;
int servoPin = A3;

void setup() {
   Serial.begin(9600); 
}

void loop() {
  //debounce handled in hardware 
  if(digitalRead(limitSwitchPin) == HIGH){
    state = (!state) & 0x01; 
  }
  
  //(state == 1) imples Sensor Mode
  if(state == 1){  
  
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
    
    //Stepper Motor controlled by IR sensor
    IRDistance = 20/((float)analogRead(IRPin)); //approx distance in cm
    if(stepDistance < IRDistance - 1){
       digitalWrite(dirPin, HIGH);
       toggle = (!toggle) & 0x01;
    }else if(stepDistance > IRDistance + 1){
      digitalWrite(dirPin, LOW);
      toggle = (!toggle) & 0x01;
    }
    
    //Servo Controlled by flex sensor
    analogWrite(servoPin,analogRead(flexPin)-1.4)*4.4);
  }  
  
  delay(10);                   
  Serial.flush();
}

