/*
 * Floating Point test
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
    
    uint16_t now;
    uint16_t elapsed;
    float x = 32767.00;
    float y = 32767.00;

    puts("Floating Point Test");
    for (uint16_t i = 0; i < 4; i++)
    {
        for (uint16_t j = 0; j < 4; j++)
        {
            now = ticks();
            uint32_t k = i * j;
            elapsed = ticks();


            printf("Int: %u * %u = %lu in %u %u, %u ticks\n",\
                i, j, k, elapsed, now, elapsed-now);        

        }
    }

    for (uint16_t i = 0; i < 4; i++)
    {
        for (uint16_t j = 0; j < 4; j++)
        {
            now = ticks();
            float z = x + i * y - j;
            elapsed = ticks();

            printf("Float: %f * %f = %e in %u %u, %u ticks\n",\
                x, y, z, elapsed, now, elapsed-now);        

        }
    }
        
    return 0;
}
