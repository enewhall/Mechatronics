#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#include <CustomStepper.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

byte cameraServoPin = 11;
Servo cameraServo;
byte servoPosition = 0;

void setup() {
 
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  pinMode(cameraServoPin,OUTPUT);
 
  cameraServo.attach(cameraServoPin);
  cameraServo.write(0);  
     
}

void loop() {
 cameraServo.write(servoPosition);
 delay(1000);
 servoPosition = (servoPosition + 20) % 180;
 
  
}


