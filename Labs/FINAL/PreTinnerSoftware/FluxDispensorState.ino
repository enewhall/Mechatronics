//const char fluxDCPinUp = 30; 
//const char fluxDCPinDown = 28; 
DCStruct fluxDC = DCINIT(30, 28);


//const char enPin4 = 39;
//const char stepPin4 = 41;
//const char dirPin4 = 37;
//CustomStepper fluxStep(stepPin4, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);
//fluxStep.setRPM(800);
StepperStruct fluxStep = STEPPERINIT(37,39,41,400,800);

const int fluxStartingPos = 2270;

unsigned char fluxDispXCounter = 0;
unsigned char fluxDispYCounter = 0;

void fluxSetup() {
  DCSetup(&fluxDC);
  StepperSetup(&fluxStep);
}

void fluxLoop() {
  switch(fluxDispState)
  {
    case 0:
      //get an indication that the partPlacer finished
      if(partPlacerDone)
      {
        fluxDispState = 1;
      }
      break;
      
    case 1: //move flux to initial position
      rotateDegrees(&fluxStep, (fluxStartingPos)*4, LOW);
      fluxDispState = 2;
      break;
      
    case 2:
      if(Done(&fluxStep))
      {
        fluxDispState = 3;
        rotateDown(&fluxDC);
        //Serial.println("Should push down");
      }
      break;
      
    case 3: //pushing down time
      if(timerElapsed(&fluxDC, 100))
      {
        //Serial.println("finish pushing");
        fluxDispState = 4;
        revFluxTimer = millis();
      }
      break;
    
    case 4: //hold time
      if(millis() - revFluxTimer > 100)
      {
        fluxDispState = 5;
        rotateUp(&fluxDC);
      }
      break;
      
    case 5: //pushing up timem
      if(timerElapsed(&fluxDC, 100))
      {
        fluxDispState = 6;
        
      }
      break;
      
    case 6: //rotate the revolver
      rotateDegrees(&revStep, 360/21*4, LOW);
      fluxDispState = 7;
      break;
      
    case 7:
      if(Done(&revStep))
      {
        fluxDispState = 8;
        revFluxTimer = millis();
      }
      break;
    
    case 8: //No correction needed ideally. wait for tube
      if(millis() - revFluxTimer > 300)
      {
        fluxDispState = 9; //move in the X direction
        //increase counter and ensure we are done
        fluxDispXCounter++;
        if(fluxDispXCounter == 5) //we did all five of them
        {
          fluxDispYCounter++;
          fluxDispState = 10; //move in the Y direction
          if(fluxDispYCounter == 4) //all 20 pieces have been fluxed and wired
          {
            fluxDispState = 100;
          }          
          
        }
      }
      break;
      
    case 9: //do flux movement in X direction and refresh to state 2
      rotateDegrees(&fluxStep, (200)*4, HIGH);
      fluxDispState = 2; //restart the process
      break;
      
    case 10: //move the flux back to original position
      rotateDegrees(&fluxStep, (800)*4, LOW);
      fluxDispState = 11; 
      break;
      
    case 11:
      if(Done(&fluxStep))
      {
        //Move the tray a little bit down
        //move to tray
        rotateDegrees(&trayStep, (400)*4, LOW);
        fluxDispState = 12;
      }
      break;
      
    case 12:
      if(Done(&trayStep))
      {
        //start up state 3
        fluxDispState = 3;
        rotateDown(&fluxDC);                        
      }
      break;
  }
  
  if(fluxDispState == 2 || fluxDispState == 11)
    fluxStep.Step.run();
    
  if(fluxDispState == 7)
    revStep.Step.run();
  
  if(fluxDispState == 12)
    trayStep.Step.run();
  
  
}
