/**
 * @author tedfoodlin
 * @author Jiajer Ho (jh10422)
 * 
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
int sensorPin = 1;
int buttonpin1 = 10; // button pin for alarm
 int press1 = 0;
int buzzer = A5; // pin for buzzer  alarm
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define MAX_DISTANCE 500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define SERIESRESISTOR 10000    
#define THERMISTORPIN A0 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);// NewPing setup of pins and maximum distance.

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
  pinMode (buttonpin1, INPUT);
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
  
  int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
  int temperature = temp.getTemp();
  double uS = sonar.ping() * 1.0951047207; // Send ping, get calibrated ping time in microseconds (uS).
  unsigned int cm = ((1404.3 + 4.7*temperature - (0.04 * pow(temperature, 2))) * 0.00005114827 * uS) + 5; //gg magic calculations

  String altitudeDisplay = "";
  String altitudeDisplayUnits = " cm";
  String finalAltitudeDisplay = altitudeDisplay + cm + altitudeDisplayUnits;
  String temperatureDisplay = "";
  String temperatureDisplayUnits = "C";
  String finalTemperatureDisplay = temperatureDisplay + temperature + temperatureDisplayUnits;

    lcd.setCursor (0,0); // go to start of 2nd line
      lcd.print(finalAltitudeDisplay);
        delay(1000);
    lcd.setCursor (5,0); // go to start of 2nd line
      lcd.print(finalTemperatureDisplay);
   
       float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                lcd.setCursor (0,1);                               //to degrees ((voltage - 500mV) times 100)
lcd.print(temperatureC);

  press1 = digitalRead(buttonpin1);
 if (press1 == HIGH)
 {
    lcd.begin (16,2);
    lcd.print("***ALARM TEST***");
    lcd.setCursor (0,1);
   
        lcd.print("");
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000); 
 }


//
        delay(1000);
        
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
  String expPingTimeDisplay = "Expected Ping Time: ";
  String altitudeDisplayUnits = " cm";
  String expFinalAltitudeDisplay = expAltitudeDisplay + expectedCM + altitudeDisplayUnits;
  String expFinalPingTimeDisplay = expPingTimeDisplay + expectedUS + pingTimeDisplayUnits;

  double pingTimeFactor = expectedUS / uS;
  String pingTimeFactorDisplay = "Ping Time Factor: ";
  String finalPingTimeFactorDisplay = pingTimeFactorDisplay + pingTimeFactor;

  Serial.println(finalPingTimeDisplay);
  Serial.println(" ");
  Serial.println(expFinalAltitudeDisplay);

  Serial.println(expFinalPingTimeDisplay);
  Serial.println(" ");
  Serial.println(finalPingTimeFactorDisplay);
  Serial.println(" ");
  
  delay(10);
}

