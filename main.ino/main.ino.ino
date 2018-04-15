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
 *  Define Car Maneuvers
 *  M1 - BACK LEFT
 *  M2 - BACK RIGHT
 *  M3 - FRONT RIGHT
 *  M4 - FRONT LEFT
 *  
 *  FORWARD - 1
 *  BACKWARD - 2
 *  BREAKE - 3
 *  RELEASE - 4
 */
#define GO_BACKWARD   0x2222
#define GO_FORWARD    0x1111
#define ROTATE_LEFT   0x2112
#define ROTATE_RIGHT  0x1221
#define TURN_LEFT     0x3113
#define TURN_RIGHT    0x1331

/*
* Create MotorDriver
* D0 - D13 and A0- A7 are used by the Shield
*/
MotorDriver m;

/*
 * Set up quick functions for car maneuvering
 */
void moveCar(int mv) {
  for (int i = 0; i < 4; i++) {
    m.motor(i+1, ((mv >> (i*4)) & (0xF)), 255);
  }
}

void setup() {
  // Setup Sensor Pins as inputs
  pinMode(FL_SENSOR, INPUT);
  pinMode(FR_SENSOR, INPUT);
}

void loop() {
  
}
