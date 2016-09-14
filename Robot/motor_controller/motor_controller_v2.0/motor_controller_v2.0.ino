/**
 * @author tedfoodlin
 * 
 * ROV motor controller v2.0
 */

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motors
int dir1PinA = 2; // vertical motors
int dir2PinA = 3; // vertical motors
int dir1PinB = 4; // right motor
int dir2PinB = 5; // right motor
int dir1PinC = 6; // left motor
int dir2PinC = 7; // left motor

// Speed pins
int speedPinA = 9; // Needs to be a PWM pin to be able to control motor speed

const int brochePWM = 3; // Pwn pin
const int in1 =  4; // Pin to activate bridge
const int in2 =  5;
const int knob = 0; // Pin for Speed
const int knob1 = 1; // Pin for Speed
const int knob2 = 2; // Pin for Speed
int speed0 = 170; // Speed setpoint
int speed1 = 170; // Speed setpoint
int speed2 = 170; // Speed setpoint


void setup() {  // Setup runs once per reset
// initialize serial communication @ 9600 baud:
Serial.begin(9600);



pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(dir1PinC,OUTPUT);
pinMode(dir2PinC,OUTPUT);
pinMode(speedPinA,OUTPUT);


// Setup serial port
  Serial.begin (9600);
  
// Output pin configuration 3
  pinMode (brochePWM, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);;
  
// Inhibits the motor
  analogWrite (brochePWM, 0);
  digitalWrite (in1, LOW);
  digitalWrite (in2, LOW);

}

void loop()
{
  speed0 = analogRead(knob)/2; //vertical y-axis
  speed1 = analogRead(knob1)/2; //left and right y-axis
  speed2 = analogRead(knob2)/2; //left and right x-axis
  
  // note: all turning is with regards to the center of the robot
  // everything is inverted, so the joystick controls the robot based on the camera view
  
  /**
   * right and left motors
   */
    // if y-axis power is negative
    if (speed1 < 50)
    {
      allReverse();
    }
    // if y-axis power is positive
    else if (speed1 > 300)
    {
      allForwards();
    } 
    // if y-axis power is at resting state (for the sake of brevity we're calling it zero from now on)
    else 
    {
      // if x-axis power is negative (left direction)
      if (speed2 < 50){
        turnLeft();
      } 
      // if x-axis power is positive (right direction)
      else if (speed2 > 300){
        turnRight();
      } 
      // if x-axis power is zero 
      else {
        allZero();
      }
    }

  /**
   * vertical motors
   */
    // if y-axis power is negative
    if (speed0 < 50) 
    {
      goDown();
    }
    // if y-axis power is positive
    else if (speed0 > 300) 
    {
      goUp();
    }
    // if y-axis power is zero
    else 
    {
      verticalZero();
    }
}

// lateral motor functions
void rightReverse(){
  analogWrite(speedPinA, 255); 
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, HIGH);
}
void rightForwards(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinB, HIGH);
  digitalWrite(dir2PinB, LOW);
}
void rightZero(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinB, LOW);
  digitalWrite(dir2PinB, LOW);
}
void leftReverse(){
  analogWrite(speedPinA, 255); 
  digitalWrite(dir1PinC, LOW);
  digitalWrite(dir2PinC, HIGH);  
}
void leftForwards(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinC, HIGH);
  digitalWrite(dir2PinC, LOW);  
}
void leftZero(){
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinC, LOW);
  digitalWrite(dir2PinC, LOW);  
}

// vertical motor functions and motion 
void goUp(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);  
}
void goDown(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH);  
}
void verticalZero(){
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
}

// lateral motion functions
void allForwards(){
  rightForwards();
  leftForwards();
}
void allReverse(){
  rightReverse();
  leftReverse();
}
void allZero(){
  rightZero();
  leftZero();
}
// these can be adjusted based on whether the camera is inverted or not
void turnLeft(){
  rightForwards();
  leftReverse();
}
void turnRight(){
  leftForwards();
  rightReverse();
}

