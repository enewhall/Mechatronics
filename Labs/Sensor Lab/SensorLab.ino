
int IRPin = A0;    
int PotPin = A1;    
int FlexPin = A2;    

int IRValue = 0;  
int PotValue = 0;  
int FlexValue = 0;  

float IRVoltage = 0.0;
float PotVoltage = 0.0;
float FlexVoltage = 0.0;

float IRLPF[] = {0, 0, 0, 0, 0};
float PotLPF[] = {0, 0, 0, 0, 0};
float FlexLPF[] = {0, 0, 0, 0, 0};



void setup() {
   Serial.begin(9600);      
}

void loop() {
  
  
  IRValue = analogRead(IRPin);    
  IRVoltage= IRValue * (5.0 / 1023.0);
  IRLPF[4] = IRVoltage;
  
  PotValue = analogRead(PotPin);    
  PotVoltage= PotValue * (5.0 / 1023.0);
  PotLPF[4] = PotVoltage;
  
  FlexValue = analogRead(FlexPin);    
  FlexVoltage= FlexValue * (5.0 / 1023.0);
  FlexLPF[4] = FlexVoltage;
  
  for(int i=0; i < 4; i++){
    IRLPF[i] = IRLPF[i+1];
    PotLPF[i] = PotLPF[i+1];
    FlexLPF[i] = FlexLPF[i+1];
  }
  
  IRVoltage = (IRLPF[0]+IRLPF[1]+IRLPF[2]+IRLPF[3]+IRLPF[4])/5;
  Serial.print("IR voltage is: ");
  Serial.print(IRVoltage);
  
  PotVoltage = (PotLPF[0]+PotLPF[1]+PotLPF[2]+PotLPF[3]+PotLPF[4])/5;
  Serial.print(", Pot voltage is: ");
  Serial.print(PotVoltage);
  
  IRVoltage = (FlexLPF[0]+FlexLPF[1]+FlexLPF[2]+FlexLPF[3]+FlexLPF[4])/5;
  Serial.print(", Flex voltage is: ");
  Serial.println(FlexVoltage);
  
  
  delay(250);          
  Serial.flush();                  
}
