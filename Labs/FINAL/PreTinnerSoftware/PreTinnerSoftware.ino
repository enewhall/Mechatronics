#include <Servo.h>
#include <Encoder.h>
#include <CustomStepper.h>
#include "SupportFunctionsStructs.h"
#include "GlobalVariables.h"
#define ENCODER_OPTIMIZE_INTERRUPTS

void setup()
{
  placerSetup();
  revSetup();
  fluxSetup();
  cameraSetup(); 
  //code useful for modification or debug
  //revRelState = 4;
  partPlacerDone = false;
  fluxDispState = 0;
  //partPos = ;
  //partPlacerDone = ;
}

void loop()
{
  //cameraLoop();
  //LEDLoop();
  partPos = 1;
  placerLoop();
  //revLoop();
  fluxLoop();
}


