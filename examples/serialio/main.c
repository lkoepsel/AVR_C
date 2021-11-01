/*
 * Serial I/O test
 *
 * Adapted from K&R The C Programming Language V3 page 17
 *
 *
 */
 
#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial;
    
    char input;

    
    puts("Serial I/O Test");
    while((input = getchar())!= EOF) {
        printf("You entered %c\n", input);        
    }
        
    return 0;
}
