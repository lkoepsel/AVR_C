// Demonstrate the problems with scanf() and fgets() to read a string
// from the serial console
// scanf() will allow a buffer over-run, resulting in a crash
// fgets() only allows a set number of char, limiting flexibility and overwrites
// once it has read the alloted number of char

#include <stdio.h>
#include "uart.h"

int main(void) {

    init_serial();
    #define MAX_CHAR 8
    char input1[MAX_CHAR] = {};
    char input2[MAX_CHAR] = {};

    puts("Serial I/O Test: scanf() and fgets()");
    while(1)
    {
        printf("scanf(): Enter up to %i char\n", MAX_CHAR - 1);
        scanf("%s", input1);
        printf("You entered %s\n", input1);

        printf("fgets(): Enter %i char\n", MAX_CHAR - 1);
        fgets(input2, MAX_CHAR, stdin);
        printf("\nYou entered %s\n", input2);
    }
}
