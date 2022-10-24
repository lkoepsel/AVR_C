// ticks() clock test
// ticks() is a high speed clock which counts at 62.5ns per tick or 16ticks/1us
// At this rate, it is easy for a counter to rollover, as the counter is 16bits
// ticks_ro() counts the number of rollovers and it is also 16bits
// Between ticks() and ticks_ro(), one can count to approx 4.5minutes
// Use the wait time below to better understand the relationship between ticks()
// and ticks_ro()

// Example times:
// for wait = 1: ticks_ro delta: 0 + ticks delta: 16059
// for wait = 4: ticks_ro delta: 0 + ticks delta: 64122
// for wait = 10: ticks_ro delta: 2 + ticks delta: 29178
// for wait = 100: ticks_ro delta: 24 + ticks delta: 28962
// for wait = 1000: ticks_ro delta: 244 + ticks delta: 26760
 
#include <stdio.h>
#include "uart.h"
#include "sysclock.h"
#include "delay.h"


int main(void) {    

    init_serial();
    init_sysclock_1 ();
    uint16_t wait = 1000;
    int16_t value;

    puts("ticks() and ticks_ro() test loop");
    printf("Initial test is for %u seconds\n", wait);
    while(1)
    {
        uint16_t delta = 0;
        uint16_t delta_ro = 0;
        uint16_t now = ticks();
        uint16_t now_ro = ticks_ro();
        delay(wait);
        uint16_t elapsed = ticks();
        uint16_t elapsed_ro = ticks_ro();
        delta = now > elapsed ? 65535 - now + elapsed : elapsed - now;
        delta_ro = now > elapsed ? elapsed_ro - now_ro - 1 : elapsed_ro - now_ro;

        printf("for wait = %u: ticks_ro delta: %u + ticks delta: %u\n",\
            wait, delta_ro, delta);        

        puts("enter the number of milliseconds, you wish to test (<9999)");
        scanf("%4i", &value);
        wait = value;
    } 
    return 0;
}
