/*
* millis - demonstrate time counter using a system clock
* Sets up a system tick of 1 millisec (1kHz)
* To test, uses the system delay (blocking, doesn't use clock)
* to determine delta between a delay
* There appears to be a lag of 18 milliseconds
* as the delta for a delay of 1000 = 1018
* 15ms of the delay is due to the button press checking in the ISR
* if button presses aren't required, comment out the code
*/
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"
#include "pinMode.h"

int main (void)
{
    init_sysclock_1 ();
    init_serial();
    uint16_t DELAY = 64;
    uint16_t prior_ticks = 0;        

    /* print the value of T/C 1 Control Register B to see scalar value  */
    /* lowest 3 bits are scalar, see datasheet page ~143 for values     */
    // printf("Testing System Ticks: TCCR1B = %u\n",  TCCR0B);

    /* loop forever, the interrupts are doing the rest */
    for (;;)  {
        prior_ticks = micros();
        delay(DELAY);
        printf("%u,%u\n", micros(), prior_ticks);
    }
    /* return never executed */
    return (0);
}
