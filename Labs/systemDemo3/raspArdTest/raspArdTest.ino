const int orient0 = 13;
const int orient1 = 12;
const int orient2 = 11;
const int orient3 = 10;
const int orient4 = 9;


void setup()
{
  pinMode(orient0, OUTPUT);
  pinMode(orient1, OUTPUT);
  pinMode(orient2, OUTPUT);
  pinMode(orient3, OUTPUT);
  pinMode(orient4, OUTPUT);
  
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available()) {
    switch(Serial.read()){
      case '0':
        digitalWrite(orient0, HIGH);
        digitalWrite(orient1, LOW);
        digitalWrite(orient2, LOW);
        digitalWrite(orient3, LOW);
        digitalWrite(orient4, LOW);
        break;
      case '1':
        digitalWrite(orient0, LOW);
        digitalWrite(orient1, HIGH);
        digitalWrite(orient2, LOW);
        digitalWrite(orient3, LOW);
        digitalWrite(orient4, LOW);
        break;
      case '2':
        digitalWrite(orient0, LOW);
        digitalWrite(orient1, LOW);
        digitalWrite(orient2, HIGH);
        digitalWrite(orient3, LOW);
        digitalWrite(orient4, LOW);
        break;
      case '3':
        digitalWrite(orient0, LOW);
        digitalWrite(orient1, LOW);
        digitalWrite(orient2, LOW);
        digitalWrite(orient3, HIGH);
        digitalWrite(orient4, LOW);
        break;
      case '4':
        digitalWrite(orient0, LOW);
        digitalWrite(orient1, LOW);
        digitalWrite(orient2, LOW);
        digitalWrite(orient3, LOW);
        digitalWrite(orient4, HIGH);
        break; 
      default:
        digitalWrite(orient0, LOW);
        digitalWrite(orient1, LOW);
        digitalWrite(orient2, LOW);
        digitalWrite(orient3, LOW);
        digitalWrite(orient4, LOW);
        break;
    }
  }
}
