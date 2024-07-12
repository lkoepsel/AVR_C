// Serial ASCII print - print's ASCII hex value for letter entered
// Quits on enter
// Requires serial monitor set to 250000, 8, 1, None with no line ending
// Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 
#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    char input;

    puts("ASCII Char Print");
    while((input = getchar())!= 0x0d) {
        printf("Char: %c ASCII (hex): %x\n", input, input);
    }
    puts("Exit");
}
