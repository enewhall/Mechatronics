#include <Time.h>


unsigned int apple[] = {1, 2, 3, 4};
int len = sizeof(apple)/sizeof(int);
int n = 0;
void setup()
{
  Serial.begin(9600);
  while (!Serial) { //Copy
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}
void loop()
{
  
  Serial.println(apple[n]);
  Serial.println(now());
  n = (n+1)%len;
  delay(2000);
}
