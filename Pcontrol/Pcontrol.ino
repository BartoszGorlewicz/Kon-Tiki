/* TO DO

- zmienan wartość kursu
- moduł komunikacyjny
- przesłanie z innego arduino wartości wychylenia / żądanego kursu

- dokumentacja
- optymalizacja

*/
/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
//#include <floatToString.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

Servo myservo;  // create servo object to control a servo
int heading;
int course = 330;
int potpin = 0;  // analog pin used to connect the potentiometer
// variable to read the value from the analog pin
String va;

void setup()
{

  // **************************************** MAGNET *****************************

  /* Initialise the sensor */
  if (!mag.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while (1);
  }
  displaySensorDetails();

  //****************************SERVO************************************
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  Serial.begin(9600);
}

void loop()
{
  heading = getHeading();
  va = String(heading);// reads the value of the potentiometer (value between 0 and 1023)
  int diff = getDifference(course, heading);
  Serial.println( String(heading) + " " + String(diff));
  diff = map(diff, -20, 20 , 0, 180);    // scale it to use it with the servo (value between 0 and 180)
  myservo.write(diff);                  // sets the servo position according to the scaled value
  delay(100);                           // waits for the servo to get there
}

int getDifference(int course, int heading) {
  int difference = course - heading;
  if (difference > 180) difference -= 340;

  return difference;
}
