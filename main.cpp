#include <Arduino.h>
#include <SoftwareSerial.h>

/* Connect HC-05 TX to Arduino RX and HC-05 RX to Arduino TX */
SoftwareSerial Bluetooth(2, 3); /* RX, TX */

const int pin34 = 4;
bool newline_printed = false;

void setup() 
{  
  Serial.begin(9600);
  Serial.println("Arduino is ready");
 
  Bluetooth.begin(9600);  
  Serial.println("Bluetooth is ready");

  pinMode(pin34, OUTPUT);
  digitalWrite(pin34, HIGH);
  Bluetooth.println("AT+NAME=ARDUINO-BLUETOOTH");
  digitalWrite(pin34, LOW);
}

void loop()
{
  if(Bluetooth.available())
  {  
    char c = Bluetooth.read();
    if(c == '#')
    {
      if(!newline_printed)
      {
        Serial.println("");
        newline_printed = true;
      }
    }
    else
    {
      Serial.print(c);
      newline_printed = false;
    }
  }
 
  if(Serial.available())
  {
    char c = Serial.read();
    Serial.write(c);
    Bluetooth.write(c);  
  }
}
