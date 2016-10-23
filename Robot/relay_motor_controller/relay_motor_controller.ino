/**
 * @author tedfoodlin
 * 
 * ROV motor controller v2.2
 */
 
// Motors
#define M1 0 //MOTOR 1
#define MM1 1 //MOTOR 1
#define M2 2 //MOTOR 2
#define MM2 3 //MOTOR 2
#define M3 4 //MOTOR 3
#define MM3 5 //MOTOR 3
#define M4 6 //MOTOR 4
#define MM4 7 //MOTOR 4

// Speed pins
int speed0 = 170; 
int speed1 = 170; 
int speed2 = 170; 
const int knob = 0; // Pin for Speed
const int knob1 = 1; // Pin for Speed
const int knob2 = 2; // Pin for Speed

// Inversion
bool inverted = false;

void setup() {
  # set up serial
  Serial.begin(9600);

  pinMode(M1, OUTPUT); //MOTOR 1 OUTPUT
  pinMode(MM1, OUTPUT); // MOTOR 1 OUTPUT
  pinMode(M2, OUTPUT); //MOTOR 2 OUTPUT
  pinMode(MM2, OUTPUT); // MOTOR 2 OUTPUT
  pinMode(M3, OUTPUT); //MOTOR 3 OUTPUT
  pinMode(MM3, OUTPUT); // MOTOR 3 OUTPUT
  pinMode(M4, OUTPUT); //MOTOR 4 OUTPUT
  pinMode(MM4, OUTPUT); // MOTOR 4 OUTPUT
}

/**
 * note: all turning is with regards to the center of the robot
 * the joystick controls the robot based on the camera view
 * this is because the driver can't see the actual robot in water, they have to rely on the camera vision
 */
void loop()
{
  // Joystick power
  speed0 = analogRead(knob)/2; //vertical y-axis
  speed1 = analogRead(knob1)/2; //left and right y-axis
  speed2 = analogRead(knob2)/2; //left and right x-axis

  // check for inversion
  if (Serial.available() > 0){
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
   
  /**
   * right and left motors
   */
  // if y-axis power is negative
  if (speed1 < 50)
  {
    allReverse();
  }
  // if y-axis power is positive
  else if (speed1 > 400)
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
        Serial.println("Turning left");
      } else if (inverted == true) {
        turnRight();
        Serial.println("Turning left");
      }
    } 
    // if x-axis power is positive (right direction)
    else if (speed2 > 400){
      if (inverted == false){
        turnRight();
        Serial.println("Turning right");
      } else if (inverted == true) {
        turnLeft();
        Serial.println("Turning right");
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
  else if (speed0 > 400) 
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
  pinMode(M3, HIGH); //MOTOR 3 CLOCKWISE
  pinMode(M4, HIGH); // MOTOR 4 CLOCKWISE
}
void goDown(){
  pinMode(MM3, HIGH); //MOTOR 3 COUNTER CLOCKWISE
  pinMode(MM4, HIGH); // MOTOR 4 COUNTER CLOCKWISE
}
void verticalZero(){
  pinMode(M3, LOW); //MOTOR 3 STOP
  pinMode(MM3, LOW); // MOTOR 3 STOP
  pinMode(M4, LOW); //MOTOR 4 STOP
  pinMode(MM4, LOW); // MOTOR 4 STOP
}

// lateral motion functions
void allForwards(){
  digitalWrite(M1, HIGH); //MOTOR 1 CLOCKWISE
  digitalWrite(M2, HIGH); //MOTOR 2 CLOCKWISE
}
void allReverse(){
  digitalWrite(MM1, HIGH); //MOTOR 1 COUNTER CLOCKWISE
  digitalWrite(MM2, HIGH); //MOTOR 2 COUNTER CLOCKWISE
}
void allZero(){
  pinMode(M1, LOW); //MOTOR 1 STOP
  pinMode(MM1, LOW); // MOTOR 1 STOP
  pinMode(M2, LOW); //MOTOR 2 STOP
  pinMode(MM2, LOW); // MOTOR 2 STOP
  pinMode(M3, LOW); //MOTOR 3 STOP
  pinMode(MM3, LOW); // MOTOR 3 STOP
  pinMode(M4, LOW); //MOTOR 4 STOP
  pinMode(MM4, LOW); // MOTOR 4 STOP
}
void turnLeft(){
  digitalWrite(M1, HIGH); //MOTOR 1 CLOCKWISE
  digitalWrite(MM2, HIGH); //MOTOR 2 COUNTER CLOCKWISE
}
void turnRight(){
  digitalWrite(MM1, HIGH); //MOTOR 1 COUNTER CLOCKWISE
  digitalWrite(M2, HIGH); //MOTOR 2 CLOCKWISE
}

