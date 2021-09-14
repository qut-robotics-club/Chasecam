/* Input-side (button) Arduino code */
#include "SoftwareSerial.h"
// RX: Arduino pin 2, XBee pin DOUT.  TX:  Arduino pin 3, XBee pin DIN
SoftwareSerial XBee(2, 3);
int BUTTON = 8;

void setup()
{
  // Baud rate MUST match XBee settings (as set in XCTU)
  pinMode(BUTTON, INPUT_PULLUP);
  XBee.begin(9600);
}

void loop()
{
  if (digitalRead(BUTTON) == HIGH)
  {
    XBee.write('H');
    delay(50);
  }
}
