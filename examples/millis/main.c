// millis - demonstrate time counter using a system clock
// Sets up a system tick of 1 millisec (1kHz)
// To test, uses the system delay (blocking, doesn't use clock)
// to determine delta between a delay
// There can be a lag of 1-2 milliseconds at times
// Requires init_sysclock_2() or
// If using a ATmega328PB, use init_sysclock_3 and millis_TC3
// and set TC3_RESET = 1
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"

int main (void)
{
    // init_sysclock_2 is required to initialize the counter for millis()
    init_sysclock_2 ();
    init_serial();
    uint16_t delay_time = 1000;

    printf("Testing millis()\n");

    for (;;)  {         
        uint32_t prior_ticks = millis();
        delay(delay_time);
        uint32_t delta_ticks = millis() - prior_ticks;
        printf("Delay time was %u ms and delta in millis() was %lu ms\n",\
            delay_time, delta_ticks);
    }
}
