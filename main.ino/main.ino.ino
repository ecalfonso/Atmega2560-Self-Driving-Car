/*
 * Main file for Arduino Mega 2560 powered Self Driving Car
 */

#include <MotorDriver.h>

// Define Wheels
#define BACK_L 1
#define BACK_R 2
#define FRONT_R 3
#define FRONT_L 4


/*
* Create MotorDriver
* D0 - D13 and A0- A7 are used by the Shield
*/
MotorDriver m;

void setup() {

}

void loop() {
  m.motor(FRONT_L, FORWARD, 255);
}
