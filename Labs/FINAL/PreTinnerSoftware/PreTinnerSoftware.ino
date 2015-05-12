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
  LEDSetup();
  cameraSetup(); 
  //code useful for modification or debug
  
  
  
  
  //revRelState = 0;
  //revRelCount = 0;
  //fluxDispState = 0;
  //partPlacerDone = true;
  //partState = 100;
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


