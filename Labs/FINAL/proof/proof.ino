byte power = LOW;
void setup()
{
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  Serial.begin(9600);
  
}

void loop() {
  
  if(Serial.available())
  {
    Serial.read();
    power = ~power & 1;
    digitalWrite(11, HIGH);
  }
  
}
