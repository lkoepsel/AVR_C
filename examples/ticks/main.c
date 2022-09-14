/*
 * ticks() test
 *
 * Requires serial monitor set to 9600, 8, 1, None with no line ending
 * Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 */
 
#include <stdio.h>
#include "uart.h"
#include "sysclock.h"


int main(void) {    

    init_serial();
    init_sysclock_1 ();
    int i = 0;
    int j = 1;
    int k;
    
    while(1)
    {
        uint16_t now = ticks();
        for (uint16_t i = 0; i < 500; i++) 
        {
            k = i + j;
        }
        uint16_t elapsed = ticks();
    
        printf("%u + %u = %u in %u %u %u\n", i, j, k, elapsed, now, elapsed-now);        
    } 
    return 0;
}
