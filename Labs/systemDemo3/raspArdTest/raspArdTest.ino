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
      default:
        digitalWrite(ledPin, HIGH);
    }
  }
}
