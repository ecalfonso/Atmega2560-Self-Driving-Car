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

/*
 * Set up quick functions for car maneuvering
 */
void moveCar(int mv) {
  for (int i = 0; i < 4; i++) {
    m.motor(i+1, ((mv >> (i*4)) & (0xF)), 255);
  }
}

/*
 * Create FSM struct
 */
struct State {
  int sOutput;    // Output for Motor Movement
  int sDelay;     // How long to stay in state
  int sNext[4];   // Next State based on Inputs
};
typedef const struct State StateType;

StateType fsm[6] {
  {0x1111, 100, {1, 3, 2, 0}},
  {0x2222, 500, {1, 3, 2, 0}},
  {0x2112, 100, {1, 2, 2, 0}},
  {0x1221, 100, {1, 3, 3, 0}}
};

// Initialize current state to default (0)
int cState = 0;

void setup() {
  // Setup Sensor Pins as inputs
  pinMode(FL_SENSOR, INPUT);
  pinMode(FR_SENSOR, INPUT);
}

void loop() {
  // Move car based on current state
  moveCar(fsm[cState].sOutput);

  // Delay for the current state's said delay
  delay(fsm[cState].sDelay);

  // Change state based on input
  int L_input = (digitalRead(FL_SENSOR) << 1) & 0x3;
  int R_input = digitalRead(FR_SENSOR) & 0x1;
  int input = L_input | R_input;
  cState = fsm[cState].sNext[input];
}
