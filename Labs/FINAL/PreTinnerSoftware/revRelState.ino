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
      rotateUp(&wireEnc);
      revRelState = 1;
      break;
      
    case 1:
      if(encoderGreater(&wireEnc, 40))
      {
        wireEnc.enc.write(0);
        revRelState = 2;
      }
      break;
      
    case 2:
      rotateUp(&cutEnc);
      if(encoderGreater(&cutEnc, 1500))
      {   
         revRelState = 3;
      } 
      break;
      
    case 3:
      rotateDown(&cutEnc);
      if(encoderLess(&cutEnc, 29))
      {   
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
        revRelState = 0;
        revRelCount++;
        if(revRelCount == 20) //inserted in all the 20 pieces
        {
          revRelState = 100;
          fluxDispState = 0;
          //Give indication that the machine is ready
        }        
      }
      break;    
    }
    
    if(revRelState == 5)
    revStep.Step.run();
  
}
