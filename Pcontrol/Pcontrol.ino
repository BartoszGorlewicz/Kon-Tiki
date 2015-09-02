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

#define MAX_RUDDER_ANGLE 80 // value from 0 to <90. Gives the move of rudder 2*MAX_RUDDER_ANGLE 
#define MAX_HEADINGERROR_ANGLE 20 // The angle of heading error which results with max rudder andgle
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

Servo myservo;  // create servo object to control a servo
int heading;    // the heading direction at the moment. In degrees.
int course = 330; // Desired heading. It is going to be passed from outer funtion
int headingError; // difference beatween heading and desired heading
void setup()
{

  // **************************************** MAGNET *****************************

  /* Initialise the sensor */
  if (!mag.begin()) 
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
  }
  displaySensorDetails();

  //****************************SERVO************************************
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop()
{
  heading = getHeading();                     // get heading at this time
  headingError = course - heading;            // get the heading difference
  if (headingError > 180) headingError -= 360; // if angle is over 180 then get the smaller angle from other side
  headingError = map(headingError, -MAX_HEADINGERROR_ANGLE, MAX_HEADINGERROR_ANGLE , 90-MAX_RUDDER_ANGLE, 90+MAX_RUDDER_ANGLE);    // translates the heading error to the angle of rudder
  myservo.write(headingError);                  // sets the servo position according to the scaled value
 // delay(100);                           // waits for the servo to get there
}

