/*
 * Main file for Arduino Mega 2560 powered Self Driving Car
 */

#include <MotorDriver.h>

// Define Wheels
#define BL_WHEEL 1
#define BR_WHEEL 2
#define FR_WHEEL 3
#define FL_WHEEL 4

// Define Sensors
#define FL_SENSOR 14
#define FR_SENSOR 15

/*
* Create MotorDriver
* D0 - D13 and A0- A7 are used by the Shield
*/
MotorDriver m;

void setup() {
  // Setup Sensor Pins as inputs
  pinMode(FL_SENSOR, INPUT);
  pinMode(FR_SENSOR, INPUT);
}

void loop() {
  m.motor(FL_WHEEL, FORWARD, 255);
}
