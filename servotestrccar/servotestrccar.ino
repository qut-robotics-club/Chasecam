#include <Servo.h>

int sensorValue0 = 1500;
int outputValue0 = 0;
int sensorValue1 = 1500;
int outputValue1 = 0;

Servo servo_9;
Servo servo_10;

void setup()
{
  int pot0 = A0;
  int pot1 = A1;
  
  servo_9.attach(9);
  servo_10.attach(10);

  Serial.begin(9600);
  Serial.println("Begin Transmission");
  
  pinMode(pot0, INPUT);
  pinMode(pot1, INPUT);

}

void loop()
{
  sensorValue0 = analogRead(A0);
  outputValue0 = map(sensorValue0, 0, 1023, 0, 180);
  delay(15);
  sensorValue1 = analogRead(A1);
  outputValue1 = map(sensorValue1, 0, 1023, 70, 110);
  delay(15);

  
  Serial.println(outputValue0);

  servo_9.write(outputValue0);
  delay(15); // Wait for 15 millisecond(s)
  servo_10.write(outputValue1);
  delay(15); // Wait for 15 millisecond(s)

  break;
}
