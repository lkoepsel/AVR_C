// ticks_servo - determine the number of rollovers for a servo clock of 250kHz
// Uses system ticks() of 4us (250kHz) (sys_clock_servo)
// Objective is to determine % of time, clock rolls over on a 2.3ms pulse
// Results appear to be 98.9% there is NOT a rollover
// Requires init_sysclock_1()

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"

int main (void)
{
    init_sysclock_servo ();
    init_serial();
    uint16_t delay_time = 3;
    
    printf("Testing ticks_servo()\n");
    for(;;)
    {
        uint16_t count_0 = 0;
        uint16_t count_1 = 0;
        for (uint16_t i = 0; i < 1000; i++)  
        {         
            uint16_t prior_ticks = ticks_ro();
            delay(delay_time);
            volatile uint16_t elapsed_ticks = ticks_ro() - prior_ticks;
            elapsed_ticks == 0 ? count_0++ : count_1++;
        }
        printf("With delay of %u, count_0: %u count_1: %u\n",\
            delay_time, count_0, count_1);
    }    
    /// return never executed ///
    return (0);
}
