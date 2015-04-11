#include <Stepper.h>
#include <Servo.h>
#include <Encoder.h>
#define ENCODER_OPTIMIZE_INTERRUPTS

const int hopper_pin_fow = 50;
const int hopper_pin_rev = 52;

const int flipper_mag_pin = 4;

//Servo control
const int servoPin = 10;
const int holdUp = 93;
//Steppper
const int enPin = 45;
const int stepPin = 47;
const int dirPin = 43;

const int enPin2 = 51;
const int stepPin2 = 53;
const int dirPin2 = 49;

const int enPin3 = 39;
const int stepPin3 = 41;
const int dirPin3 = 37;

const int enPin4 = 24;
const int stepPin4 = 26;
const int dirPin4 = 22;

const int spinner_pin = 6;

const int wirefeederPin = 12;

//Wire Cutter
const int encoderAPin = 2;
const int encoderBPin = 3;
Encoder myEnc = Encoder(2, 3);
Encoder fluxEnc = Encoder(21, 20);
const int DCMotorPinA = 46;
const int DCMotorPinB = 48;
const int fluxDCPinA = 30; //down
const int fluxDCPinB = 28; //up



//magnet
const int magnetPin = 11;

int s = 0;

Stepper partStep = Stepper(400, stepPin, 0);

Stepper trayStep = Stepper(200, stepPin2, 0);

Stepper revStep = Stepper(6400, stepPin3, 0);

Stepper fluxStep = Stepper(400, stepPin4, 0);

Servo partServo;
Servo servo_flipper;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  pinMode(hopper_pin_rev,OUTPUT);
  pinMode(hopper_pin_fow,OUTPUT);
  
  
  pinMode(flipper_mag_pin,OUTPUT);
  
  pinMode(spinner_pin,OUTPUT);
  
  pinMode(encoderAPin,INPUT);
  pinMode(encoderBPin,INPUT);
  
  pinMode(enPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enPin2, OUTPUT);
  pinMode(stepPin2, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(enPin3, OUTPUT);
  pinMode(stepPin3, OUTPUT);
  pinMode(dirPin3, OUTPUT);
  pinMode(enPin4, OUTPUT);
  pinMode(stepPin4, OUTPUT);
  pinMode(dirPin4, OUTPUT);
  pinMode(magnetPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(wirefeederPin, OUTPUT);
  pinMode(DCMotorPinA, OUTPUT);
  pinMode(DCMotorPinB, OUTPUT); 
  pinMode(fluxDCPinA, OUTPUT);
  pinMode(fluxDCPinB, OUTPUT);
  partStep.setSpeed(100);
  trayStep.setSpeed(200);
  revStep.setSpeed(5);
  fluxStep.setSpeed(100);
  partServo.attach(servoPin);
  servo_flipper.attach(10,900,2100);
  digitalWrite(enPin, HIGH);
  digitalWrite(enPin2, HIGH);
  digitalWrite(enPin3, HIGH);
  digitalWrite(enPin4, HIGH);
  partServo.write(150); //calibration
  delay(300);
  partServo.write(holdUp); //Hold speed
  //attachInterrupt(0, PinA, CHANGE);
  //attachInterrupt(1, PinB, CHANGE);
  
}

void loop() {
  // put your main code here, to run repeatedly:

    
      servo_flipper.write(0);
      delay(2000);
      servo_flipper.write(90);
      delay(2000);
      servo_flipper.write(180);
      delay(2000);
      
      
   
  
}


