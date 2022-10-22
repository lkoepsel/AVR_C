// button - each button must attach to a pin
// buttons[i].uno are the Uno pins attached to buttons, 
// like digitalRead, function will translate Uno pin to port/pin
// buttons[i].pressed indicates if the button has been pressed (true or non-zero)

#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/sleep.h>

#define MAX_BUTTONS 2
#define BOUNCE_MASK 0b11000111

typedef struct button {
   uint8_t uno;                 // Uno pin numbers for button
   uint8_t pressed;             // true if button has been pressed
} button;

uint8_t read_button(uint8_t uno);
uint8_t is_button_pressed(uint8_t instance);

#endif