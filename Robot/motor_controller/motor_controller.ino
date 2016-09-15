/**
 * @author tedfoodlin
 * 
 * ROV motor controller v2.2
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

// Speed setpoints
int speed0 = 170; 
int speed1 = 170; 
int speed2 = 170; 

// Inversion (set to default at beginning)
char inversion = '1';
bool inverted = false;

void setup() {  // Setup runs once per reset
// initialize serial communication @ 9600 baud:
  Serial.begin(9600);
// ask for inversion
  Serial.println("Enter 1 or 2 to invert right and left turning.");

// Define L298N Dual H-Bridge Motor Controller Pins

  pinMode(dir1PinA,OUTPUT);
  pinMode(dir2PinA,OUTPUT);
  pinMode(dir1PinB,OUTPUT);
  pinMode(dir2PinB,OUTPUT);
  pinMode(dir1PinC,OUTPUT);
  pinMode(dir2PinC,OUTPUT);
  pinMode(speedPinA,OUTPUT);
  
// Output pin configuration 3
  pinMode (brochePWM, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);;
  
// Inhibits the motor
  analogWrite (brochePWM, 0);
  digitalWrite (in1, LOW);
  digitalWrite (in2, LOW);
  
  Serial.println(" ");
  Serial.println("Motors enabled");
  Serial.println(" ");
}

void loop()
{
  // Joystick power
  speed0 = analogRead(knob)/2; //vertical y-axis
  speed1 = analogRead(knob1)/2; //left and right y-axis
  speed2 = analogRead(knob2)/2; //left and right x-axis

  // check for inversion
  if (Serial.available()){
    inversion = Serial.read();
    if (inversion == '2'){
      Serial.println("INVERSION MODE 2");
      inverted = true;
    } else {
      Serial.println("INVERSION MODE 1");
      inverted = false;
    }
  } else {
    Serial.println("INVERSION MODE 1");
    inverted = false;
  }
  
  // note: all turning is with regards to the center of the robot
  // everything is inverted (but we don't know which way)
  // the joystick controls the robot based on the camera view 
  // this is because the driver can't see the actual robot in water, they have to rely on the camera vision
  
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
        if (inverted == false){
          turnLeft();
        } else if (inverted == true) {
          turnRight();
        }
      } 
      // if x-axis power is positive (right direction)
      else if (speed2 > 300){
        if (inverted == false){
          turnRight();
        } else if (inverted == true) {
          turnLeft();
        }
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

// vertical motor functions and motion 
void goUp(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinA, HIGH);
  digitalWrite(dir2PinA, LOW);  
  Serial.println("Going up");
}
void goDown(){
  analogWrite(speedPinA, 255);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, HIGH); 
  Serial.println("Going down"); 
}
void verticalZero(){
  analogWrite(speedPinA, 0);
  digitalWrite(dir1PinA, LOW);
  digitalWrite(dir2PinA, LOW);
  Serial.println("No vertical movement");
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

// lateral motion functions
void allForwards(){
  rightForwards();
  leftForwards();
  Serial.println("Forwards");
}
void allReverse(){
  rightReverse();
  leftReverse();
  Serial.println("Reverse");
}
void allZero(){
  rightZero();
  leftZero();
  Serial.println("No lateral movement");
}
void turnLeft(){
  rightForwards();
  leftReverse();
  Serial.println("Turning left");
}
void turnRight(){
  leftForwards();
  rightReverse();
  Serial.println("Turning right");
}
