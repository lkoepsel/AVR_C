/*
* millis - demonstrate time counter using a system clock
* Sets up a system tick of 1 millisec (1kHz)
* To test, uses the system delay (blocking, doesn't use clock)
* to determine delta between a delay
* There appears to be a lag of 2-3 milliseconds
* as the delta for a delay of 1000 = 1002
*/
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"

int main (void)
{
    init_sysclock ();
    init_serial;
    puts("Testing System Ticks");

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         
        uint16_t prior_ticks = millis();

        delay(1000);

        uint16_t delta_ticks = prior_ticks - millis();
        printf("delta is %u\n", delta_ticks);

    }
    /* return never executed */
    return (0);
}
