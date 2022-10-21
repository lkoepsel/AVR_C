/*
 * ticks() test
 *
 * Requires serial monitor set to 9600, 8, 1, None with no line ending
 * Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 */
 
#include <stdio.h>
#include "uart.h"
#include "sysclock.h"
#include "delay.h"


int main(void) {    

    init_serial();
    init_sysclock_1 ();
    uint16_t wait = 4096;

    while(1)
    {
        uint16_t now = ticks();
        delay(wait);
        uint16_t elapsed = ticks();
    
        printf("for wait = %u: elapsed: %u now: %u delta: %u\n",\
         wait, elapsed, now, elapsed-now);        
    } 
    return 0;
}
