/* micros - demonstrate fine-degree timing counter using system clock
* A system tick = .5 microseconds accessed via micros()
* A system tock = 32.77 milliseconds accessed via sys_cntr_1
* To test, use the system delay (blocking, doesn't use clock)
* In calculating anything over one tock (32.77ms), add an N multiplier of 65535 for
* every rollover, i.e; 100 has N=3 rollovers
* EX:
*   delay(4) = 8133 ticks = 8000 * .5us = 4ms with a 133/2/4 or 16us overhead
*   delay(25) = 50802 ticks = 5000 * .5us = 25ms with a 802/2/25 or 16us overhead
*   delay(100) = 203202 ticks = 200000 * .5us = 100ms with a 3202/2/100 or 16us overhead
*/
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"
#include "pinMode.h"

#define NTIMES 100
int main (void)
{
    // extern uint16_t sys_ctr_1;
    init_sysclock_1();
    init_sysclock_2();
    init_serial();
    uint16_t DELAY = 100;
    uint16_t previous[NTIMES] = {0};
    uint16_t now[NTIMES] = {0};


    /* print the value of T/C 1 Control Register B to see scalar value  */
    /* lowest 3 bits are scalar, see datasheet page ~143 for values     */
    printf("Testing System Ticks: TCCR1B = %u\n",  TCCR1B);

    /* loop forever, the interrupts are doing the rest */
    while(1) {
        for (uint8_t i=0; i<NTIMES;i++)  {
            previous[i] = micros();
            delay(DELAY);
            now[i] = micros();
        }
        // average = ( total >> 7);
        for (uint8_t i=0; i<NTIMES;i++)  {
            printf("%u %u\n", now[i], previous[i]);
        }
    }    /* return never executed */
    return (0);
}
