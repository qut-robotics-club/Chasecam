#include <Servo.h>

int steering = 0;
int drive = 0;

Servo servo_9;
Servo servo_10;

void setup()
{
  servo_9.attach(9);
  servo_10.attach(10);
}

void loop()
{
  steering = map(0, -100, 100, 0, 180);
  drive = map(0, -100, 100, 0, 180);
  servo_9.write(steering);
  servo_10.write(drive);
  delay(10000); // Wait for 15 millisecond(s)

  steering = map(0, -100, 100, 0, 180);
  drive = map(80, -100, 100, 0, 180);
  servo_9.write(steering);
  servo_10.write(drive);
  delay(2000); // Wait for 15 millisecond(s)

  steering = map(80, -100, 100, 0, 180);
  drive = map(80, -100, 100, 0, 180);
  servo_9.write(steering);
  servo_10.write(drive);
  delay(1000); // Wait for 15 millisecond(s)

  steering = map(0, -100, 100, 0, 180);
  drive = map(80, -100, 100, 0, 180);
  servo_9.write(steering);
  servo_10.write(drive);
  delay(2000); // Wait for 15 millisecond(s)

  steering = map(0, -100, 100, 0, 180);
  drive = map(0, -100, 100, 0, 180);
  servo_9.write(steering);
  servo_10.write(drive);
  delay(2000); // Wait for 15 millisecond(s)

  while(1);
}
