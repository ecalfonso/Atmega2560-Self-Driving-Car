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
#define BK_SENSOR 16

// Define Car Motor Maneuvers
#define GO_FORWARD    0x1111
#define GO_BACKWARD   0x2222
#define TURN_LEFT     0x2112
#define TURN_RIGHT    0x1221
#define FULL_STOP     0x3333
#define MOTOR_RELEASE 0x4444

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
  int sNext[8];   // Next State based on Inputs
};
typedef const struct State StateType;

/*
 * FSM Structure:
 */
#define FWD   0 // Forward
#define REV   1 // Reverse
#define RTL   2 // Rev then Left
#define RTR   3 // Rev then Right
#define TL    4 // Turn Left
#define TR    5 // Turn Right
#define PREL  6 // Pre-forward Left
#define PRER  7 // Pre-forward Right
#define STOP  8 // Stop

StateType fsm[9] {
  {GO_FORWARD,    10, {STOP, TR, TL,  FWD, REV, RTR, RTL,  FWD}},
  {GO_BACKWARD,  500, {STOP, TR, TL,   TR, REV, RTR, RTL,   TL}},
  {GO_BACKWARD,  500, {STOP, TR, TL,   TL, RTL, RTL, RTL,   TL}},
  {GO_BACKWARD,  500, {STOP, TR, TL,   TR, RTR, RTR, RTR,   TR}},
  {TURN_LEFT,   1000, {STOP, TR, TL, PREL, RTL, RTL, RTL, PREL}},
  {TURN_RIGHT,  1000, {STOP, TR, TL, PRER, RTR, RTR, RTR, PRER}},
  {GO_FORWARD,   500, {STOP, TR, TL,  FWD, RTL, RTL, RTL,  FWD}},
  {GO_FORWARD,   500, {STOP, TR, TL,  FWD, RTR, RTR, RTR,  FWD}},
  {FULL_STOP,   1000, {STOP, TR, TL,  FWD,  TR, RTR, RTL,  FWD}}
};

// Initialize current state to default (0)
int pState = -1;
int cState = 0;

void setup() {
  // Setup Sensor Pins as inputs
  pinMode(FL_SENSOR, INPUT);
  pinMode(FR_SENSOR, INPUT);
  pinMode(BK_SENSOR, INPUT);
}

void loop() {
  // Only change motor direction if states changed
  if (pState != cState) {
    // Stop motors before new state
    // But don't stop if moving from PRER/PREL -> FWD
   if ((pState == PREL || pState == PRER) && cState == FWD) { 
      moveCar(MOTOR_RELEASE);
      delay(50);
  }

    // Move car based on new state
    moveCar(fsm[cState].sOutput);
  }

  // Delay for the current state's said delay
  delay(fsm[cState].sDelay);

  // Save previous state
  pState = cState;

  // Change state based on input
  int B_input = (digitalRead(BK_SENSOR) << 2) & 0x4;
  int L_input = (digitalRead(FL_SENSOR) << 1) & 0x2;
  int R_input = digitalRead(FR_SENSOR) & 0x1;
  int input = B_input | L_input | R_input;
  cState = fsm[cState].sNext[input];
}
