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
const int holdingPos = 20;
const int viewingPos = 90;
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
  cameraTime = millis();  
  Serial.begin(9600);
  while(!Serial.available());
  Serial.read();
}


void cameraLoop() {
  if(Serial.available()) {
    serialValue = Serial.read();
    LEDValue = serialValue;
  }
  
  switch(cameraState){
    case 1:
      //Release magnet
      DCStop(&hopperDC);
      cameraTime = millis();
      cameraState = 2;
      break;
      
    case 2:
      //Time Elapsed for releasing magnet
      if(millis() - cameraTime > 100)
      {
        //reEnable magnet
        rotateUp(&hopperDC);
        cameraState = 3;
        cameraTime = millis();
      }
      break;
      
    case 3: //Wait until piece is settled
      if(millis() - cameraTime > 1500)
      {
        cameraState = 4;
        Serial.print('0');
      }
      break;
      
    case 4: //check if a piece is in.
      if(Serial.available())
      {
        serialValue = Serial.read();
        if(serialValue == '0')
          cameraState = 0;
        else
          cameraState = 5;
      }
      break;
      
    case 5: 
      flipperServo.write(restingPos);
      cameraServo.write(viewingPos);
      digitalWrite(flipper_mag_pin,HIGH);
      cameraState = 6;
      cameraTime = millis();
      break;
      
    case 6:
      if(millis() - cameraTime > 1000)
      {
        Serial.print('0');
        cameraState = 7;
      }
      break;
      
    case 7:
      if(Serial.available())
      {
        serialValue = Serial.read();
        LEDValue = serialValue;
        if(serialValue == '1' ){
          cameraState = 9;
          partPosTemp = 1;
          cameraTime = millis();
        }else if(serialValue == '2'){
          cameraState = 9;
          partPosTemp = 2;
          cameraTime = millis();
        }else if(serialValue == '3'){
          cameraState = 8;
          partPosTemp = 1;
          cameraTime = millis();
        }else if(serialValue == '4'){
          cameraState = 8;
          partPosTemp = 2;
          cameraTime = millis();
        }
        else
          Serial.print('0'); //refetch value
      }
      break;
      
    case 8: //flip part
      flipperServo.write(flipPos);
      cameraServo.write(holdingPos);
      if(millis() - cameraTime > 1000){
        cameraState = 10;
        partPos = partPosTemp;
        cameraTime = millis();
      }
      break;
      
    case 9:
      //SLIDE PART
      flipperServo.write(slidingPos);
      cameraServo.write(viewingPos);  
      digitalWrite(flipper_mag_pin,LOW);
      
      if(millis() - cameraTime > 1000){
        cameraState = 10;
        partPos = partPosTemp;
        cameraTime = millis();
      }
      break;
        
    case 10: //reset positions
      flipperServo.write(restingPos);
      cameraServo.write(holdingPos);
      digitalWrite(flipper_mag_pin, LOW);
      if(millis() - cameraTime > 1000){
        //restart the process
        cameraState = 0;
      }
      break;
}
