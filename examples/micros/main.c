/*
* micros - compare two microsecond counters using system clock
* Each tick of ticks() is 62.5 ns and 16 ticks are 1 microsecond
* ticks() = returns the number of ticks elapsed
* micros() = returns the number of ticks * 16 or microseconds elapsed
* To test, uses the system delay (blocking, doesn't use clock)
* Get ticks, delay 1 millisecond, get ticks, determine delta and store
* 
* The clock wraps around at 4.0959ms, so add 65535 for every n 4.0959 ms
* Calling ticks is more accurate than micros and won't provide bad values
* as shown below
*
* Requires: init_sysclock_1()
*/
#include <avr/io.h>
#include <stdio.h>
#include <delay.h>
#include "uart.h"
#include "sysclock.h"
#include "unolib.h"

int main (void)
{
    init_serial();
    puts("Testing System Ticks (1 tick = 62.5ns)");

    init_sysclock_1 ();
    const uint8_t DELAY = 1;
    const uint8_t MAX = 10;
    uint16_t elapased_ticks[2][MAX];

    printf("Delay of %u ms\n", DELAY);

    /* Two loops, one for ticks() and one for micros() */
    printf("ticks() in usec:\t");
    for (uint8_t i=MAX-1;i>0;i--)  {         
        elapased_ticks[0][i] = ticks();
        _delay_ms(DELAY);
        elapased_ticks[1][i] = ticks();

    }
    for (uint8_t i=MAX-1;i>0;i--)  {         
        printf("%i ",
         ((elapased_ticks[1][i]-elapased_ticks[0][i]) >> 4));
    }
    puts(" Complete");
    printf("micros() in usec:\t\t");
    for (uint8_t i=MAX-1;i>0;i--)  {         
        elapased_ticks[0][i] = micros();
        _delay_ms(DELAY);
        elapased_ticks[1][i] = micros();

    }
    for (uint8_t i=MAX-1;i>0;i--)  {         
        printf("%i ",
         (elapased_ticks[1][i]-elapased_ticks[0][i]));
    }
    puts(" Complete");
    // while(1) {
        
    // }
    /* return never executed */
    return 0;
}
