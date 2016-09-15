/**
 * @author tedfoodlin
 * @author Jiajer Ho (jh10422)
 * Underwater Sonar Sensor v1.2
 */
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

void setup()
{
  // initialize serial communication
  Serial.begin(9600);
  
  lcd.begin (12,2);
 
  // LCD Backlight ON
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // go home on LCD

  delay(1500);
  Serial.println(" ");
  Serial.println("Sonar and temperature sensors enabled!");
  Serial.println(" ");
}

void loop()
{
  int temperature = temp.getTemp();
  double uS = sonar.ping() * 1.0951047207; // Send ping, get calibrated ping time in microseconds (uS).
  unsigned int cm = ((1404.3 + 4.7*temperature - (0.04 * pow(temperature, 2))) * 0.00005114827 * uS) + 5; //gg magic calculations

  String altitudeDisplay = "Altitude: ";
  String altitudeDisplayUnits = " cm";
  String finalAltitudeDisplay = altitudeDisplay + cm + altitudeDisplayUnits;
  String temperatureDisplay = "Temperature: ";
  String temperatureDisplayUnits = "C";
  String finalTemperatureDisplay = temperatureDisplay + temperature + temperatureDisplayUnits;

    lcd.setCursor (0,0); // go to start of 2nd line
      lcd.print(finalAltitudeDisplay);
        delay(500);
    lcd.setCursor (0,1); // go to start of 2nd line
      lcd.print(finalTemperatureDisplay);
        delay(500);
        
    Serial.println(finalAltitudeDisplay);
    Serial.println(finalTemperatureDisplay);
//  reportState();

}

// testing
int numberOfTests = 0;
void reportState()
{
  numberOfTests = numberOfTests + 1;
  String testNumberDisplay = "Test Number: ";
  String finalTestNumberDisplay = testNumberDisplay + numberOfTests;
  Serial.println(finalTestNumberDisplay);
  Serial.println(" ");

  double expectedUS = sonar.ping();
  unsigned int expectedCM = sonar.convert_cm(expectedUS);
  double uS = sonar.ping() * 1.0951047207; // Send ping, get calibrated ping time in microseconds (uS).

  String pingTimeDisplay = "Ping Time: ";
  String pingTimeDisplayUnits = " uS";
  String finalPingTimeDisplay = pingTimeDisplay + uS + pingTimeDisplayUnits;

  String expAltitudeDisplay = "Expected Altitude: ";
  String expTemperatureDisplay = "Expected Temperature: ";
  String expPingTimeDisplay = "Expected Ping Time: ";
  String expFinalAltitudeDisplay = expAltitudeDisplay + expectedCM + altitudeDisplayUnits;
  String expFinalTemperatureDisplay = finalTemperatureDisplay;
  String expFinalPingTimeDisplay = expPingTimeDisplay + expectedUS + pingTimeDisplayUnits;

  double pingTimeFactor = expectedUS / uS;
  String pingTimeFactorDisplay = "Ping Time Factor: ";
  String finalPingTimeFactorDisplay = pingTimeFactorDisplay + pingTimeFactor;

  Serial.println(finalPingTimeDisplay);
  Serial.println(" ");
  Serial.println(expFinalAltitudeDisplay);
  Serial.println(expFinalTemperatureDisplay);
  Serial.println(expFinalPingTimeDisplay);
  Serial.println(" ");
  Serial.println(finalPingTimeFactorDisplay);
  Serial.println(" ");
  
  delay(10);
}

