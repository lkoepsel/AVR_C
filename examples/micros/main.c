/* micros - demonstrate fine-degree timing counter using system clock
* A system tick = .5 microseconds accessed via micros()
* To test, use the system delay() (blocking, doesn't use clock)
* To minimize overhead, system runs NTIMES filling an array
* then prints out NTIMES number of lines
* consisting of two times, post-delay and pre-delay. 
* The difference between the two are the number of ticks which occured duing delay
* In calculating anything over 32.77ms, add an N multiplier of 65535 for
* every rollover, i.e; 100 has N=3 rollovers (100,000 % 32.77 = 3)
* EX:
*   delay(4) = 8166 ticks = 8000 * .5us = 4ms with a 166 * .5 /4 or 20us overhead
*   delay(25) = 51010 ticks = 5000 * .5us = 25ms with a 1010 * .5 /25 or 20us overhead
*   delay(100) = 204019 ticks = 200000 * .5us = 100ms with a 4019 * .5 /100 or 20us overhead
* CALC: IF (PREV > NOW)
*   TRUE: (N * 65535) + (NOW + 65535) - PREV 
*   FALSE (N * 65535) + NOW - PREV 
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
    init_sysclock_1();
    init_sysclock_2();
    init_serial();
    uint16_t DELAY = 25;
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

        for (uint8_t i=0; i<NTIMES;i++)  {
            printf("%u %u\n", now[i], previous[i]);
        }
    }    /* return never executed */
    return (0);
}
