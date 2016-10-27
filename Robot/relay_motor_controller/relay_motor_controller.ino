/**
 * @author tedfoodlin
 * @author jiajerho
 * 
 * ROV relay motor controller v2.2
 */
 
// Motors
#define M1 9 //MOTOR 1
#define MM1 10 //MOTOR 1
#define M2 3 //MOTOR 2
#define MM2 11 //MOTOR 2
#define M3 5 //MOTOR 3
#define MM3 6 //MOTOR 3
#define M4 7 //MOTOR 4
#define MM4 8 //MOTOR 4

// Speed pins
int power0 = 170; 
int power3 = 170;
int power1 = 170; 
int power2 = 170; 
const int knob = 0; // Pin for Speed
const int knob3 = 3; // Pin for Speed
const int knob1 = 1; // Pin for Speed
const int knob2 = 2; // Pin for Speed

// Motion
enum lateralMotion {
  ALL_FORWARDS,
  ALL_REVERSE,
  TURN_LEFT,
  TURN_RIGHT,
  LATERAL_ZERO,
};
enum verticalMotion {
  PITCH_FWD,
  PITCH_BACK,
  GO_UP,
  GO_DOWN,
  VERTICAL_ZERO,
};

// Commands
enum lateralMotion lateralCommand;
enum verticalMotion verticalCommand;

void setup() {
  // set up serial
  Serial.begin(9600);

  // set up pins
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
 * all turning is with regards to the center of the robot
 * the joystick controls the robot based on the camera view
 * this is because the driver can't see the actual robot in water
 * they have to rely on the camera vision
 */
void loop()
{
  // Joystick power
  power0 = analogRead(knob)/2; //vertical y-axis
  power3 = analogRead(knob3)/2; //vertical x-axis
  power1 = analogRead(knob1)/2; //lateral y-axis
  power2 = analogRead(knob2)/2; //lateral x-axis

  verticalCommand = getVerticalDriverInput(power0, power3);
  lateralCommand = getLateralDriverInput(power1, power2);
  
  setVerticalMotion(verticalCommand);
  setLateralMotion(lateralCommand);

  Serial.println((String)verticalCommand);
  Serial.println((String)lateralCommand);
}

/**
 * Get vertical joystick driver input
 * @param speed0
 * @param speed3
 * @return verticalMotion
 */
verticalMotion getVerticalDriverInput(double power0, double power3) {
  if (power0 < 50) 
  {
    verticalCommand = GO_DOWN;
  }
  else if (power0 > 400) 
  {
    verticalCommand = GO_UP;
  }
  else 
  {
    if (power3 < 50){
      verticalCommand = PITCH_FWD;
    }
    else if (power3 > 400){
      verticalCommand = PITCH_BACK;
    }
    else {
      verticalCommand = VERTICAL_ZERO;
    }
  }
  return verticalCommand;
}

/**
 * Get lateral joystick driver input
 * @param speed1
 * @param speed2
 * @return lateralMotion
 */
lateralMotion getLateralDriverInput(double power1, double power2) {
  if (power1 < 50)
  {
    lateralCommand = ALL_FORWARDS;
  }
  else if (power1 > 400)
  {
    lateralCommand = ALL_REVERSE;
  } 
  else 
  {
    if (power2 < 50){
      lateralCommand = TURN_LEFT;
    } 
    else if (power2 > 400){
      lateralCommand = TURN_RIGHT;
    } 
    else {
      lateralCommand = LATERAL_ZERO;
    }
  }
  return lateralCommand;
}

/**
 * Set vertical motion based on commands from driver input
 * @param verticalMotion
 */
void setVerticalMotion(verticalMotion) {
  if (verticalCommand == GO_UP) {
    pinMode(MM3, HIGH); //MOTOR 3 CLOCKWISE
    pinMode(MM4, HIGH); //MOTOR 4 CLOCKWISE
  } else if (verticalCommand == GO_DOWN) {
    pinMode(M3, HIGH); //MOTOR 3 COUNTER CLOCKWISE
    pinMode(M4, HIGH); //MOTOR 4 COUNTER CLOCKWISE
  } else if (verticalCommand == PITCH_FWD) {
    pinMode(M3, HIGH); //MOTOR 3 CLOCKWISE
    pinMode(MM4, HIGH); //MOTOR 4 COUNTER CLOCKWISE
  } else if (verticalCommand == PITCH_BACK) {
    pinMode(MM3, HIGH); //MOTOR 3 COUNTER CLOCKWISE
    pinMode(M3, HIGH); //MOTOR 4 COUNTER CLOCKWISE
  } else if (verticalCommand == VERTICAL_ZERO) {
    pinMode(M3, LOW); //MOTOR 3 STOP
    pinMode(MM3, LOW); //MOTOR 3 STOP
    pinMode(M4, LOW); //MOTOR 4 STOP
    pinMode(MM4, LOW); //MOTOR 4 STOP
  }
}

/**
 * Set lateral motion based on commands from driver input
 * @param lateralMotion
 */
void setLateralMotion(lateralMotion) {
  if (lateralCommand == ALL_FORWARDS) {
    pinMode(M1, HIGH); //MOTOR 1 CLOCKWISE
    pinMode(M2, HIGH); //MOTOR 2 CLOCKWISE
  } else if (lateralCommand == ALL_REVERSE) {
    pinMode(MM1, HIGH); //MOTOR 1 COUNTER CLOCKWISE
    pinMode(MM2, HIGH); //MOTOR 2 COUNTER CLOCKWISE
  } else if (lateralCommand == TURN_LEFT) {
    pinMode(M1, HIGH); //MOTOR 1 CLOCKWISE
    pinMode(MM2, HIGH); //MOTOR 2 COUNTER CLOCKWISE
  } else if (lateralCommand = TURN_RIGHT) {
    pinMode(MM1, HIGH); //MOTOR 1 COUNTER CLOCKWISE
    pinMode(M2, HIGH); //MOTOR 2 CLOCKWISE
  } else if (lateralCommand = LATERAL_ZERO) {
    pinMode(M1, LOW); //MOTOR 1 STOP
    pinMode(MM1, LOW); // MOTOR 1 STOP
    pinMode(M2, LOW); //MOTOR 2 STOP
    pinMode(MM2, LOW); // MOTOR 2 STOP
    pinMode(M3, LOW); //MOTOR 3 STOP
    pinMode(MM3, LOW); // MOTOR 3 STOP
    pinMode(M4, LOW); //MOTOR 4 STOP
    pinMode(MM4, LOW); // MOTOR 4 STOP
  }
}

