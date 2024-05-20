/*
 * Simple Integer and Floating Point test
 *
 * Demonstrates float will report correct results, with a 3x performance hit
 * Use tio, Arduino Serial Monitor, minicom, or your favorite serial monitor
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

    puts("Integer and Floating Point Test");
    for (uint32_t i = 266; i < 330; i += 53)
    {
        for (uint32_t j = 313; j < 520; j += 78)
        {
            now = ticks();
            uint32_t k = i * j;
            elapsed = ticks();


            printf("Int: %lu * %lu = %lu in %u ticks\n",\
                i, j, k, elapsed-now);        

        }
    }

    for (uint16_t i = 266; i < 330; i += 53)
    {
        for (uint16_t j = 313; j < 520; j += 78)
        {
            now = ticks();
            float z = (float)i * (float)j;
            elapsed = ticks();

            printf("Float: %f * %f = %f in %u ticks\n",\
                (float)i, (float)j, z, elapsed-now);        

        }
    }
        
    return 0;
}
