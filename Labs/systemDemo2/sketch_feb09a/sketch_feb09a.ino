float IRDistance = 0.0;
int stepPin = 6; 
int dirPin = 5;
int enPin = 9;
int toggle = 0;
float stepDistance = 0.0;

//Second Motor need to access pin values
float IRDistance2 = 0.0;
int stepPin2 = 4; 
int dirPin2 = 10;
int enPin2 = 12;
int toggle2 = 0;
float stepDistance2 = 0.0;

//For our DC motor
float potAngle = 0.0;
//int DCMotorAngle = 0;
int DCMotorPinA = 7;
int DCMotorPinB = 8;

//etc
const int limitsw = 13;
const int elePin = 2;
int ele = 0;

unsigned char serialValue = 0;
float primaryValue = 0; //for GUI
boolean primaryWrite = false;

float secondaryValue = 0;
boolean secondaryWrite = false;

unsigned char trimaryValue = 1;
boolean trimaryWrite = false;

void setup() {
   Serial.begin(9600); 
   while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }         
   pinMode(stepPin,OUTPUT);
   pinMode(dirPin,OUTPUT);
   pinMode(enPin,OUTPUT);
   
   pinMode(stepPin2,OUTPUT);
   pinMode(dirPin2,OUTPUT);
   pinMode(enPin2,OUTPUT);
   
   pinMode(limitsw, INPUT);
   pinMode(elePin, OUTPUT);
   
   pinMode(DCMotorPinA, OUTPUT);
   pinMode(DCMotorPinB, OUTPUT);
}

void loop() { 
  if(Serial.available()) //Read value and decide what to do with it
  {
    serialValue = Serial.read();
    if(primaryWrite)
    {
      primaryValue = serialValue;
      primaryWrite = false;
    }
    else if(secondaryWrite)
    {
      secondaryValue = serialValue;
      secondaryWrite = false;
    }
    else if(trimaryWrite)
    {
      trimaryValue = serialValue;
      trimaryWrite = false;
    }
    else if(serialValue == 90)
    {
      trimaryWrite = true;
    }
    else if(serialValue == 30)
    {
      primaryWrite = true; //primaryValue = next serial reading
    }
    else if(serialValue == 80)
    {
      secondaryWrite = true;
    }
    else if(serialValue == 50)
    {
      ele = (!ele) & 0x01;
    }
  } //attributed sensor readings

  //Stepper Motor controlled by IR sensor
  IRDistance = (primaryValue*2.5)/(255*2.5); //approx distance in cm
  IRDistance2 = (secondaryValue*2.5)/(255*2.5);
  
  //Motor 1
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
  
  //Motor 2
  if(stepDistance2 < IRDistance2-.005 && IRDistance2 < 2.0){
     digitalWrite(enPin2, LOW);
     digitalWrite(dirPin2, HIGH);
     toggle2 = (!toggle2) & 0x01;
     digitalWrite(stepPin2, toggle2);
     stepDistance2 += .001;
  }else if(stepDistance2 > IRDistance2+.005 && IRDistance2 < 2.0){
    digitalWrite(enPin2, LOW);
    digitalWrite(dirPin2, LOW);
    toggle2 = (!toggle2) & 0x01;
    digitalWrite(stepPin2, toggle2);
    stepDistance2 -= .001;
  }
  else {
    digitalWrite(enPin2, HIGH);
    digitalWrite(dirPin2, LOW);
  }
  
  //DC Motor Implementation(TO DO)
 // if(digitalRead(limitsw) == LOW)
  //{
    switch(trimaryValue) {
      case 0:
        //turn left
        digitalWrite(DCMotorPinA,LOW);
        digitalWrite(DCMotorPinB,HIGH);
        break;
      case 1:
        digitalWrite(DCMotorPinA,LOW);
        digitalWrite(DCMotorPinB,LOW);
        break;
      case 2:
        digitalWrite(DCMotorPinA,HIGH);
        digitalWrite(DCMotorPinB,LOW);
      
    }
  //}
//  else
//  {
//        digitalWrite(DCMotorPinA,LOW);
//        digitalWrite(DCMotorPinB,LOW);
//  }
  
//  if(potAngle < DCMotorAngle - 8.0){
//    digitalWrite(DCMotorPinA,LOW);
//    digitalWrite(DCMotorPinB,HIGH);
//  }else if(potAngle > DCMotorAngle + 8.0){
//    digitalWrite(DCMotorPinA,HIGH);
//    digitalWrite(DCMotorPinB,LOW);
//  }else{
//    digitalWrite(DCMotorPinA,LOW);
//    digitalWrite(DCMotorPinB,LOW);
//  }
  

   //electro magnetism
   digitalWrite(elePin, ele);
  
  delay(1); //For fast speed
  
  
  Serial.flush();
}



//void PinA(){
//   encoderAPrev = encoderAValue;
//   encoderAValue = digitalRead(encoderAPin);
//  if(encoderAPrev){
//    if(encoderBPrev){
//      //counterclockwise
//      DCMotorAngle -= 4;
//    } else{
//      //clockwise
//      DCMotorAngle += 4;
//    }  
//  }else{
//    if(encoderBPrev){
//      //clockwise
//      DCMotorAngle += 4;
//    } else{
//      //counterclockwise
//      DCMotorAngle -= 4;
//    }
//  } 
//}
//
//void PinB(){
//   encoderBPrev = encoderBValue;
//   encoderBValue = digitalRead(encoderBPin);
//  if(encoderBPrev){
//    if(encoderAPrev){
//      //clockwise
//      DCMotorAngle += 4;
//    } else{
//      //counterclockwise
//      DCMotorAngle -= 4;
//    }  
//  }else{
//    if(encoderAPrev){
//      //counterclockwise
//      DCMotorAngle -= 4;
//    } else{
//      //clockwise
//      DCMotorAngle += 4;
//    }
//  } 
//}
//

