//include variables that are shared in multiple files
byte partPos = 0;
bool partPlacerDone = false;
unsigned long revFluxTimer = 0; //used for both flux and revRel
char LEDValue = '5';

bool Large = true; //tells if the piece is large or not.
unsigned char revRelCount = 0;

//States
int cameraState = 1;
int partState = 0;
int revRelState = 100;
int fluxDispState = 100; //starts when revRelState finishes


//const char dirPin2 = 49;
//const char enPin2 = 51;
//const char stepPin2 = 53;
StepperStruct trayStep = STEPPERINIT(49,51,53,200,800);

//const char dirPin3 = 22;
//const char enPin3 = 24;
//const char stepPin3 = 26;
//CustomStepper revStep(stepPin3, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 6400, 5, CW);
//revStep.setRPM(10);
StepperStruct revStep = STEPPERINIT(22,24,26,6400, 10);
