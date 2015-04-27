Servo flipperServo;
Servo cameraServo;

const char flipper_mag_pin = 4;
const char flipperServoPin = 5;
const char cameraServoPin = 11;

//const char hopper_pin_fow = 50;
//const char hopper_pin_rev = 52;
DCStruct hopperDC = DCINIT(50, 52);


// Constants for flipper servo positions
const int slidingPos = 25;
const int restingPos = 18;
const int flipPos = 180;
// Constant for camera Servo
const int holdingPos = 80;
const int viewingPos = 15;
//STATE VARIABLES
unsigned long cameraTime = 0;
int serialValue = '6';

byte partPosTemp = 0;

void cameraSetup() { //Also sets up serial communications
  
  DCSetup(&hopperDC);
  
  pinMode(flipper_mag_pin,OUTPUT);
  pinMode(flipperServoPin, OUTPUT);
  pinMode(cameraServoPin,OUTPUT);
  
  flipperServo.attach(flipperServoPin);
  cameraServo.attach(cameraServoPin);
      
  flipperServo.write(restingPos);
  cameraServo.write(holdingPos);  
  
  Serial.begin(9600);
  while(!Serial.available() && Serial.read() == '5');
  cameraTime = millis();    
}


void cameraLoop() {
  if(Serial.available()) {
    serialValue = Serial.read();
    LEDValue = serialValue;
  }
  
  switch(cameraState){
      case 1:
        //HOLD
        DCStop(&hopperDC);
        
        flipperServo.write(restingPos);
        cameraServo.write(holdingPos);
        digitalWrite(flipper_mag_pin,LOW);
        
        
        if(serialValue != '0' && serialValue != '5' && millis() - cameraTime > 1000){
          cameraState = 5;
          cameraTime = millis();
        }else if(partPos == 0 && millis() - cameraTime > 5000){
          cameraState = 2;
          cameraTime = millis();
        }
        break;
      case 2:
        //SPIN FOWARD
        rotateUp(&hopperDC);
        flipperServo.write(restingPos);
        cameraServo.write(holdingPos);  
        digitalWrite(flipper_mag_pin,LOW);
        
        if(millis() - cameraTime > 100){
          cameraState = 1;
          cameraTime = millis();
        }
        break;
      case 3:
        //FLIP PART
        rotateDown(&hopperDC);
        flipperServo.write(flipPos);
        cameraServo.write(holdingPos);
        digitalWrite(flipper_mag_pin,HIGH);  
        
        if(millis() - cameraTime > 1000){
          cameraState = 2;
          partPos = partPosTemp;
          cameraTime = millis();
        }
        break;
      case 4:
        //SLIDE PART
        rotateDown(&hopperDC);
        flipperServo.write(slidingPos);
        cameraServo.write(viewingPos);  
        digitalWrite(flipper_mag_pin,LOW);
        
        if(millis() - cameraTime > 1000){
          cameraState = 2;
          partPos = partPosTemp;
          cameraTime = millis();
        }
        break;
      case 5:
        //VIEWING PART
        DCStop(&hopperDC);
        flipperServo.write(restingPos);
        cameraServo.write(viewingPos);
        digitalWrite(flipper_mag_pin,HIGH);  
        
        if(millis() - cameraTime > 2500){
          if(serialValue == '1' ){
            cameraState = 4;
            partPosTemp = 1;
            cameraTime = millis();
          }else if(serialValue == '2'){
            cameraState = 4;
            partPosTemp = 2;
            cameraTime = millis();
          }else if(serialValue == '3'){
            cameraState = 3;
            partPosTemp = 1;
            cameraTime = millis();
          }else if(serialValue == '4'){
            cameraState = 3;
            partPosTemp = 2;
            cameraTime = millis();
          }
                  
        }
        break;
    }      
    
  serialValue = 0; //only accept latest
}
