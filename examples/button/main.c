/*
* button - each button must attach to a pin, as be setup as INPUT_PULLUP
* Requires sysclock to have a SCALAR1 = SCALAR01_64, as this provides a 8 millis pulse
* pins[i] are the ports attached to buttons, like digitalRead, function will translate pin to port
* buttons[i] are the pressed indications for the button, true is pressed
*/ 
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"
#include "pinMode.h"

extern volatile uint8_t buttons[max_buttons];
extern volatile uint8_t pins[max_buttons];

int main (void)
{
    /* initialize buttons to ports, and instantiate using i     */
    /* pins[i] are the Uno port numbers                         */
    /* buttons[i] are the buttons which correspond to pins[i]   */
    uint8_t i = 0;
    pins[i] = 11;
    pinMode(pins[i], INPUT_PULLUP);
    ++i;
    pins[i] = 12;
    pinMode(pins[i], INPUT_PULLUP);

    init_serial;
    puts("Testing Button Presses");

    init_sysclock ();

    /* slight delay at beginning to reduce spurious button presses */
    delay(50);
    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         

        for (int i = 0; i < max_buttons; i++) {
            if (buttons[i]) {
                printf("Button %u was pressed.\n", i);
            }
        }
    }
    /* return never executed */
    return (0);
}
