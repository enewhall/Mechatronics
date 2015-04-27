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
  //partState = ;
  //partPos = ;
  //partPlacerDone = ;
}

void loop()
{
  cameraLoop();
  LEDLoop();
  placerLoop();
  revLoop();
  fluxLoop();
}


