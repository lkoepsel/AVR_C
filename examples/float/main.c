/*
 * Floating Point test
 *
 * Requires serial monitor set to 9600, 8, 1, None with no line ending
 * Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 */
 
#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    
    puts("Floating Point Test");
    float x = 5000.00;
    float y = 2500.00;
    float z = x * y;

    printf("%f * %f = %f\n", x, y, z);        
        
    return 0;
}
