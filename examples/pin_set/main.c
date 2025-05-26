// Serial I/O test - Echo's the typed letter back to monitor
// Adapted from K&R The C Programming Language V3 page 17
// Requires serial monitor set to 250000, 8, 1, None with no line ending
// Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 
#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    char input;

    puts("Echo Serial Test");
    while((input = getchar())!= EOF) 
    {
        putchar(input);
        if (input == '\n' || input == '\r') 
        {
            puts("\nType another character or q to quit.");
        }
        else if (input == 'q' || input == 'Q') 
        {
            puts("\nExiting program.");
            break;
        }
        else 
        {
            printf("\nYou typed: %c", input);
        }
    }
}
