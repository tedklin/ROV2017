//zoomkat servo button test 7-30-2011
//Powering a servo from the arduino usually *DOES NOT WORK*.

#include <Servo.h>
int button1 = 4; //button pin, connect to ground to move servo
int press1 = 0;
Servo servo1;

void setup()
{
 pinMode(button1, INPUT);
 servo1.attach(7);
 digitalWrite(4, HIGH); //enable pullups to make pin high
}

void loop()
{
 press1 = digitalRead(button1);
 if (press1 == LOW)
 {
   servo1.write(180 f321`);
 }
 else {
   servo1.write(0);
 }
}

