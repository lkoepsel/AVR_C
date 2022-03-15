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

// Frequencies are defined by 16x10^6/ (2 * scalar * TOP), scalar = 1 and TOP,
// for which the definitions are below
// #define FREQ_2K 2000
// #define FREQ_4K 1000
// #define FREQ_8K 500
// #define FREQ_16K 249
// #define FREQ_20K 200
// #define FREQ_28K 143
// #define FREQ_32K 125
// #define FREQ_40K 101
// #define FREQ_48K 83


// state contains the current state of the FSM
extern int state;

extern int LED_bit0;
extern int LED_bit1;
extern int LED_bit2;

extern int buttonState0;
extern int BUTTON0;
extern int priorState0;

extern int buttonState1;
extern int BUTTON1;
extern int priorState1;

extern button buttons[max_buttons];

/* Main */ 
int main();
#endif