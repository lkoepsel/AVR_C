/* Finite State Machine Lock - uses a FSM to act as a binary locking mechanism
Requires 3 LEDs/resistors to be connected to pins 3/5/6
Requires 2 push buttons to be connected to pins 10/11 INPUT_PULLUP Mode
Correct button presses will cycle through FSM
Final correct button press will blink all three LEDs
*/

#ifndef MAIN_H
#define MAIN_H

/* Put your #includes here */
#include <stdio.h>
#include <stdlib.h>

#include "sysclock.h"
#include "button.h"
#include "pinMode.h"
#include "digitalRead.h"
#include "digitalWrite.h"
#include "delay.h"
#include "state0.h"
#include "state1.h"
#include "state2.h"
#include "state3.h"

/* Put your global variables here */
#define UP 0
#define ENTER 1
#define DIM 16
#define MEDIUM 63
#define BRIGHT 127

// state contains the current state of the FSM
extern uint8_t state;

extern const uint8_t BIT_0;
extern const uint8_t BIT_1;
extern const uint8_t BLUE_LED;

extern button buttons[MAX_BUTTONS];

/* Main */ 
int main();
#endif
