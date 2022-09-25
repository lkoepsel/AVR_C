// ticks_ro - demonstrate counting ticks() rollover
// Uses system ticks() of 62.5nsec (16MHz), and rolls over ever 65535 ticks
// To test, uses the system delay (blocking, doesn't use clock)
// to determine delta between a delay
//
// Requires init_sysclock_1()

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"

int main (void)
{
    init_sysclock_1 ();
    init_serial();
    uint16_t delay_time = 1000;

    printf("Testing ticks_ro()\n");
    float calc_ro = (float) delay_time / 4.096;
    printf("For a delay of %u, calculated rollover ticks are %4.2f\n",\
        delay_time, calc_ro);

    for (;;)  
    {         
        uint16_t prior_ticks = ticks_ro();
        delay(delay_time);
        uint16_t elapsed_ticks = ticks_ro() - prior_ticks;
        printf("With delay of %u, roll over ticks are %u\n",\
            delay_time, elapsed_ticks);
    }
    /// return never executed ///
    return (0);
}
