// serialio - demonstrate how to successfully read a line of text

#include <stdio.h>
#include "uart.h"
#include "readLine.h"

#define MAX_BUFFER 15

int main(void) {    

    init_serial();
    char input[MAX_BUFFER + 1] = {};

    puts("Serial I/O Test: readLine");
    while(1)
    {
        printf("Enter text up to %i characters, and end w/ CR\n", MAX_BUFFER);
        uint8_t num_char = readLine(input, MAX_BUFFER);

        printf("You entered %i characters\n", num_char);
        for (uint8_t out_char=0; out_char<MAX_BUFFER; out_char++)
        {
            printf("%c", input[out_char]);

            // erases buffer for next use, might not be desired
            input[out_char] = 0;
        }
        printf("\n");
    }
}
