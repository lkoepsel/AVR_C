/*
* button - each button must attach to a pin, as be setup as INPUT_PULLUP
* Requires sysclock to have a SCALAR1 = SCALAR01_64, as this provides a 8 millis pulse
* buttons[i].pins are the ports attached to buttons, like digitalRead, function will translate pin to port
* buttons[i] are the pressed indications for the button, true is pressed
*/ 
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"
#include "pinMode.h"
#include "button.h"

extern button buttons[max_buttons];

int main (void)
{
    /* initialize buttons to ports, and instantiate using i     */
    /* buttons[i].uno are the Uno pin numbers                   */
    /* buttons[i].pressed indicate the button is pressed        */
    init_serial;
    puts("Testing Button Presses");

    uint8_t i = 0;
    buttons[i].uno = 8;
    pinMode(buttons[i].uno, INPUT_PULLUP);
    ++i;
    buttons[i].uno = 9;
    pinMode(buttons[i].uno, INPUT_PULLUP);

    init_sysclock ();

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         

        for (int i = 0; i < max_buttons; i++) {
            if (buttons[i].pressed) {
                printf("Button %u was pressed.\n", i);
            }
        }
    }
    /* return never executed */
    return (0);
}
