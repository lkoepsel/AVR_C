/*
* button - attach a button to a port then read button to get debounced value
* Requires sysclock to have a SCALAR1 = SCALAR01_64, as this provides a 8 millis pulse
* uint8_t attach_button(uint8_t port) - attaches a button to a port and instantiates it
* use return value of attach_button for read_button value
* uint8_t read_button(uint8_t instance) instance is the value returned from attach_button()
* the instance number allows one to have multiple buttons debounced
* the return value is true if button is pressed, otherwise 0 for false
*/
#ifndef button_h
#define button_h

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t attach_button(uint8_t port);

#endif