//const char fluxDCPinUp = 30; 
//const char fluxDCPinDown = 28; 
DCStruct fluxDC = DCINIT(30, 28);

unsigned int fluxCor = 50;
unsigned int trayCor = 200;
bool reloaded = false;


//const char enPin4 = 39;
//const char stepPin4 = 41;
//const char dirPin4 = 37;
//CustomStepper fluxStep(stepPin4, 0, 0, 0, (byte[]){8, B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001}, 400, 100, CW);
//fluxStep.setRPM(800);
StepperStruct fluxStep = STEPPERINIT(41,39,37,400,800);

const int fluxStartingPos = 410;

unsigned char fluxDispXCounter = 0;
unsigned char fluxDispYCounter = 2;

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
      rotateDegrees(&fluxStep, (fluxStartingPos)*4, HIGH);
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
      
    case 30:
      fluxDispState = 3;
      rotateDown(&fluxDC);
      
    case 3: //pushing down time
      if(timerElapsed(&fluxDC, 110))
      {
        //Serial.println("finish pushing");
        fluxDispState = 4;
        revFluxTimer = millis();
      }
      break;
    
    case 4: //hold time
      if(millis() - revFluxTimer > 55)
      {
        fluxDispState = 5;
        rotateUp(&fluxDC);
      }
      break;
      
    case 5: //pushing up timem
      if(timerElapsed(&fluxDC, 65))
      {
        fluxDispState = 6; //skip tray correction
      }
      break;
      
    case 6: // do tray correction
      rotateDegrees(&trayStep, trayCor*4, LOW);
      fluxDispState = 7;
      break;
      
    case 7:
      if(Done(&trayStep))
      {
        fluxDispState = 8;
      }
      break;
      
    case 8: // do flux correction
      rotateDegrees(&fluxStep, fluxCor*4, LOW);
      fluxDispState = 9;
      break;
      
    case 9:
      if(Done(&fluxStep))
      {
        fluxDispState = 10;
      }
      break;
      
    case 10: //rotate the revolver
      rotateDegrees(&revStep, 360/21*4, LOW);
      fluxDispState = 11;
      break;
      
    case 11:
      if(Done(&revStep))
      {
        revRelCount--;
        fluxDispState = 12;
        revFluxTimer = millis();        
      }
      break;                
    
    case 12: //wait for tube
      if(millis() - revFluxTimer > 800)
      {
        //
        fluxDispState = 40; //skip tray correction
        if( (Large == true) && (reloaded == false))
        {
          fluxDispState = 10;
          reloaded = true;
        }
        //this algorithm will not result in inserting one less wire by parity
      }
      break;
      
    case 40:
      fluxDispState = 13;
      rotateDegrees(&trayStep, (trayCor-10)*4, HIGH); //move back
      break;
    
    case 13: //undo tray correction
      if(Done(&trayStep))
      {
        fluxDispState = 14;
      }
      break;
      
    case 14: // undo flux correction
      rotateDegrees(&fluxStep, (fluxCor-5)*4, HIGH);
      fluxDispState = 15;
      break;
      
    case 15:
      if(Done(&fluxStep))
      {
        //fluxDispState = 100;
        //break;
        
        reloaded = false; //refresh reload
        
        fluxDispState = 16; //move in the X direction
        //increase counter and ensure we are done
        fluxDispXCounter++;
        if(fluxDispXCounter == 5) //we did all five of them
        {
          fluxDispXCounter = 0;
          fluxDispYCounter++;
          fluxDispState = 17; //move in the Y direction
          if(fluxDispYCounter == 4) //all 20 pieces have been fluxed and wired
          {
            fluxDispState = 100;
          }          
          
        }        
      }
      break;
      
    case 16: //do flux movement in X direction and refresh to state 2
      rotateDegrees(&fluxStep, (240)*4, HIGH);
      fluxDispState = 2; //restart the process
      break;
      
    case 17: //move the tray a little bit up.
      rotateDegrees(&trayStep, (400)*4, HIGH);
      fluxDispState = 18; 
      break;
      
    case 18:
      if(Done(&trayStep))
      {
        //Move the flux back to original position
        rotateDegrees(&fluxStep, (850 + fluxStartingPos)*4, LOW);
        fluxDispState = 19;
      }
      break;
      
    case 19:
      if(Done(&fluxStep))
      {
        //start up state 0
        fluxDispState = 0;

        //By parity, all wires should run out on this state
        if(revRelCount == 0) //we ran out
        {
          revRelState = 0; //Restart revRelState
          fluxDispState = 100; //disable the fluxDispState
          //The flux will continue when 20 new wires are loaded
        }        
      }
      break;
  }
  
  if(fluxDispState == 2 || fluxDispState == 9 || fluxDispState == 15 || fluxDispState == 19)
    fluxStep.Step.run();
    
  if(fluxDispState == 11)
    revStep.Step.run();
  
  if(fluxDispState == 7 || fluxDispState == 13 || fluxDispState == 18)
    trayStep.Step.run();
  
  
}
