/* soft_reset - Performs a software reset a user-defined button
* The button must attach to a pin, as be setup as INPUT_PULLUP
* Requires sysclock_2, as in init_sysclock_2
*/ 
#include <stdio.h>
#include "uart.h"
#include "sysclock.h"
#include "button.h"
#include "pinMode.h"

extern button buttons[max_buttons];

int main (void)
{
    /* initialize buttons to ports, and instantiate using i     */
    /* buttons[i].uno are the Uno pin numbers                   */
    /* buttons[i].pressed indicate the button is pressed        */
    init_serial();
    puts("Testing Button Presses");
    uint8_t count[max_buttons] = {0};

    uint8_t i = 0;
    buttons[i].uno = 8;
    pinMode(buttons[i].uno, INPUT_PULLUP);
    ++i;
    buttons[i].uno = 9;
    pinMode(buttons[i].uno, INPUT_PULLUP);

    init_sysclock_2 ();

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         

        for (int i = 0; i < max_buttons; i++) {
            if (buttons[i].pressed) {
                count[i] += 1;
                printf("Button %u was pressed, %u times.\n", i, count[i]);
            }
        }
    }
    /* return never executed */
    return (0);
}

