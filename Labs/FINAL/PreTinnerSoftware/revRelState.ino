//const char wirefeederPin = 12;
//Encoder wireEnc = Encoder(21, 20);
DCEncStruct wireEnc = DCENCINIT(12,0,21,20);
//Encoder myEnc = Encoder(2, 3);
//const char DCCutterPinCut = 46;
//const char DCCutterPinRelease = 48;
DCEncStruct cutEnc = DCENCINIT(46,48,2,3);
//const char dirPin3 = 22;
//const char enPin3 = 24;
//const char stepPin3 = 26;
//CustomStepper revStep(stepPin3, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 6400, 5, CW);
//revStep.setRPM(10);
StepperStruct revStep = STEPPERINIT(22,24,26,6400, 10);

int revRelState = 100;
unsigned char revRelCount = 0;
unsigned long revFluxTimer = 0; //used for both flux and revRel

void revSetup() {
  DCSetup(&wireEnc);
  DCSetup(&cutEnc);
  StepperSetup(&revStep);  
}

void revLoop() {
  
  
  
}
