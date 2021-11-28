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
#include "unolib.h"

int main (void)
{
    init_sysclock ();
    init_serial;
    uint16_t delay_time = 1000;
    puts("Testing System Ticks");

    /* print the value of T/C 1 Control Register B to see scalar value  */
    /* lowest 3 bits are scalar, see datasheet page ~143 for values     */
    printf(" TCCR1B %u\n",  TCCR1B);

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {         
        uint16_t prior_ticks = millis();

        delay(delay_time);

        uint16_t delta_ticks = prior_ticks - millis();
        printf("Delay time was %u and delta is %u\n", delay_time, delta_ticks);

    }
    /* return never executed */
    return (0);
}
