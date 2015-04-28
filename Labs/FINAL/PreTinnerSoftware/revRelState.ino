//const char wirefeederPin = 12;
//Encoder wireEnc = Encoder(21, 20);
DCEncStruct wireEnc = DCENCINIT(12,0,21,20);
//Encoder myEnc = Encoder(2, 3);
//const char DCCutterPinCut = 46;
//const char DCCutterPinRelease = 48;
DCEncStruct cutEnc = DCENCINIT(46,48,2,3);



unsigned char revRelCount = 0;

void revSetup() {
  DCSetup(&wireEnc);
  DCSetup(&cutEnc);
  StepperSetup(&revStep);  
}

void revLoop() {
  
  switch(revRelState){
     case 0:
      rotateUp(&cutEnc);
      if(encoderGreater(&cutEnc, (1520 + 2*revRelCount) ))
      {   
         revRelState = 1;
      } 
      break;
      
    case 1:
      rotateDown(&cutEnc);
      if(encoderLess(&cutEnc, 29))
      {   
         revRelState = 2;
      } 
      break;
      
    case 2:
      rotateUp(&wireEnc);
      revRelState = 3;
      break;
      
    case 3:
      if(encoderGreater(&wireEnc, 40))
      {
        wireEnc.enc.write(0);
        revRelState = 4;
      }
      break;
      
      
    case 4: //rotate the revolver
      rotateDegrees(&revStep, 360/21*4, LOW);
      revRelState = 5;
      break;
      
    case 5:
      if(Done(&revStep)) //keep repeating until 20 wires are put in
      {
        revRelState = ;//Debug remember to undo
        revRelCount++;
        if(revRelCount == 21) //inserted in all the 20 pieces
        {
          revRelState = 100;
          fluxDispState = 0;
          //Give indication that the machine is ready
        }        
        //debug
        //delay(1000);
      }
      break;    
    }
    
    if(revRelState == 5)
    revStep.Step.run();
  
}
