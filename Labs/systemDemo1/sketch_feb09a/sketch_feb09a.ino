int IRPin = A0;
float IRDistance = 0.0;
int stepPin = 6; 
int dirPin = 5;
int enPin = 2;
int toggle = 0;
float stepDistance = 0.0;

unsigned char serialValue = 0;
float primaryValue = 0; //for GUI
boolean primaryWrite = false;

void setup() {
   Serial.begin(9600); 
   while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }         
   pinMode(stepPin,OUTPUT);
   pinMode(dirPin,OUTPUT);
   pinMode(enPin,OUTPUT);
}

void loop() { 
  if(Serial.available()) //Read value and decide what to do with it
  {
    serialValue = Serial.read();
    if(primaryWrite)
    {
      primaryValue = serialValue;
      primaryValue = serialValue;
      primaryWrite = false;
    }
    else if(serialValue == 30)
    {
      primaryWrite = true; //primaryValue = next serial reading
    }
  } //attributed sensor readings

  //Stepper Motor controlled by IR sensor
  IRDistance = (primaryValue*2)/(255*2.5); //approx distance in cm
 
  if(stepDistance < IRDistance-.005 && IRDistance < 2.0){
     digitalWrite(enPin, LOW);
     digitalWrite(dirPin, HIGH);
     toggle = (!toggle) & 0x01;
     digitalWrite(stepPin, toggle);
     stepDistance += .001;
  }else if(stepDistance > IRDistance+.005 && IRDistance < 2.0){
    digitalWrite(enPin, LOW);
    digitalWrite(dirPin, LOW);
    toggle = (!toggle) & 0x01;
    digitalWrite(stepPin, toggle);
    stepDistance -= .001;
  }
  else {
    digitalWrite(enPin, HIGH);
  }
  //digitalWrite(DCMotorPinA,LOW);
  //digitalWrite(DCMotorPinB,LOW);
  //analogWrite(servoPin,0);
  delay(1);
  
  
  Serial.flush();
}

