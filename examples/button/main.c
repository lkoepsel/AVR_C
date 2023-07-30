/* button - Demonstrates how to add buttons and 
*  test software reset with a user-defined button.
* The button must attach to a pin, setup as INPUT_PULLUP and will be debounced
* Requires sysclock_2:
*       #include "sysclock.h"
*       init_sysclock_2()
*
*       buttons is a struct with elements
*           uno - uno pin for button
*           pressed - if true, button has been pressed
*       soft reset is setup by init_RESET()
*       button is assumed to be on PB7, INPUT_PULLUP and will be debounced
*       reset is performed by a WDT interrupt as described by AVR-GCC FAQ  
*/ 
#include <stdio.h>
#include "uart.h"
#include "sysclock.h"
#include "button.h"
#include "pinMode.h"

extern button buttons[MAX_BUTTONS];

int main (void)
{
    /* initialize buttons to ports, and instantiate using i     */
    /* buttons[i].uno are the Uno pin numbers                   */
    /* buttons[i].pressed indicate the button is pressed        */
    init_serial();
    puts("Testing Button Presses");
    uint8_t count[MAX_BUTTONS] = {0};

    buttons[0].uno = 2;
    pinMode(buttons[0].uno, INPUT_PULLUP);
    buttons[1].uno = 3;
    pinMode(buttons[1].uno, INPUT_PULLUP);

    init_sysclock_2 ();
   // Use init_RESET() if you want to setup a soft reset using a user defined
   // button as on the ATmega328PB Xplained Mini
   // init_RESET();

    /* loop forever, the interrupts are doing the rest */
    for (;;)  
    {
        for (uint8_t i=0; i < MAX_BUTTONS; i++) 
        {
            if (buttons[i].pressed) 
            {
                count[i] += 1;
                printf("Button %u was pressed, %u times.\n", i, count[i]);
            }
        }
    }
}

