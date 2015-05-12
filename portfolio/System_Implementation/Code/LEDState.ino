const char LED0 = 34; //34 
const char LED1 = 40;
const char LED2 = 38;
const char LED3 = 36; 
const char LED4 = 42;

void LEDSetup() {
  
  pinMode(LED0,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  
  
  digitalWrite(LED0,LOW);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);
  digitalWrite(LED4,LOW);  
}

void LEDLoop() {
  
  switch(LEDValue){ 
     case '0':
       digitalWrite(LED0,LOW);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;
     case '1':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,LOW);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
     case '2':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,LOW);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
     case '3':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,LOW);
       digitalWrite(LED4,HIGH);
       break;  
     case '4':
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,LOW);
       break;  
     case '5':
       digitalWrite(LED0,LOW);
       digitalWrite(LED1,LOW);
       digitalWrite(LED2,LOW);
       digitalWrite(LED3,LOW);
       digitalWrite(LED4,LOW);
       break;
     case '6': //Done
       digitalWrite(LED0,HIGH);
       digitalWrite(LED1,HIGH);
       digitalWrite(LED2,HIGH);
       digitalWrite(LED3,HIGH);
       digitalWrite(LED4,HIGH);
       break;  
         
  }
  
}
