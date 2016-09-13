
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <Thermistor.h>
#include <Servo.h>
Thermistor temp(0);
#define I2C_ADDR    0x27 // <<- Add your address here.
#define Rs_pin  0
#define Rw_pin  1
#define En_pin  2
#define BACKLIGHT_PIN 3
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SERIESRESISTOR 10000    
#define THERMISTORPIN A0 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);// NewPing setup of pins and maximum distance.

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
//Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

//int pos = 0;    // variable to store the servo position
int numberOfTests = 0;

void setup()
{
  // myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  lcd.begin (12,2); // <<-- our LCD is a 20x4, change for your LCD if needed
 
  // LCD Backlight ON
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // go home on LCD

float reading;
 
}

void loop()
{
  
Serial.begin(9600);
 // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
  // myservo.write(pos);              // tell servo to go to position in variable 'pos'
 //  delay(5);                       // waits 15ms for the servo to reach the position
//  }
 // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  // delay(5);                       // waits 15ms for the servo to reach the position
 // }

  numberOfTests = numberOfTests + 1;
     String testNumberDisplay = "Test Number: ";
     String finalTestNumberDisplay = testNumberDisplay + numberOfTests;
     Serial.println(finalTestNumberDisplay);
     Serial.println(" ");
     
  int temperature = temp.getTemp();
  double uS = sonar.ping() * 1.0951047207; // Send ping, get ping time in microseconds (uS).
  unsigned int cm = ((1404.3 + 4.7*temperature - (0.04 * pow(temperature, 2))) * 0.00005114827 * uS) + 5;

  double expectedUS = sonar.ping();
  unsigned int expectedCM = sonar.convert_cm(expectedUS);

  String altitudeDisplay = "Altitude: ";
  String altitudeDisplayUnits = " cm";
  String finalAltitudeDisplay = altitudeDisplay + cm + altitudeDisplayUnits;
  String temperatureDisplay = "Temperature: ";
  String temperatureDisplayUnits = "C";
  String finalTemperatureDisplay = temperatureDisplay + temperature + temperatureDisplayUnits;
  String pingTimeDisplay = "Ping Time: ";
  String pingTimeDisplayUnits = " uS";
  String finalPingTimeDisplay = pingTimeDisplay + uS + pingTimeDisplayUnits;

  String expAltitudeDisplay = "Expected Altitude: ";
  String expTemperatureDisplay = "Expected Temperature: ";
  String expPingTimeDisplay = "Expected Ping Time: ";
  String expFinalAltitudeDisplay = expAltitudeDisplay + expectedCM + altitudeDisplayUnits;
  String expFinalTemperatureDisplay = finalTemperatureDisplay;
  String expFinalPingTimeDisplay = expPingTimeDisplay + expectedUS + pingTimeDisplayUnits;

//  double pingTimeFactor = expectedUS / uS;
//  String pingTimeFactorDisplay = "Ping Time Factor: ";
//  String finalPingTimeFactorDisplay = pingTimeFactorDisplay + pingTimeFactor;

    lcd.setCursor (0,0); // go to start of 2nd line
      lcd.print(finalAltitudeDisplay);
        delay(500);
    lcd.setCursor (0,1); // go to start of 2nd line
      lcd.print(finalTemperatureDisplay);
        delay(500);
        
    Serial.println(finalAltitudeDisplay);
    Serial.println(finalTemperatureDisplay);
    Serial.println(finalPingTimeDisplay);
    Serial.println(" ");
    Serial.println(expFinalAltitudeDisplay);
    Serial.println(expFinalTemperatureDisplay);
    Serial.println(expFinalPingTimeDisplay);
    Serial.println(" ");
//    Serial.println(finalPingTimeFactorDisplay);
//    Serial.println(" ");
    
      delay(10);

}
