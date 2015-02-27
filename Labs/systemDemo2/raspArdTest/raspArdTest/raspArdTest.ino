const int ledPin = 13;


void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available()) {
    switch(Serial.read()){
      case '0':
        digitalWrite(ledPin, LOW);
        break;
      case '1':
        digitalWrite(ledPin, HIGH);
    }
  }
  Serial.println("Hello World");
  delay(2000);
}
