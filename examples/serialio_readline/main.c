// serialio - demonstrate how to successfully read a line of text and
// use strtok() to split the line into tokens (or words)
// It is very important to understand that strtok() returns a pointer
// this means the tokens[] below is:
// an array of pointers which point to each specific token
// it is NOT an array of characters, which make up the token

#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "readLine.h"

#define MAX_BUFFER 24
#define MAX_TOKENS (MAX_BUFFER/2)
#define MAX_DELIMS 1

int main(void) {    

    // init_serial() is always required to use serial port, as well as #include "uart.h"
    init_serial();

    // input is the buffer for the serial port
    // delims are the token delimitors
    char input[MAX_BUFFER + 1] = {};
    char delims[MAX_DELIMS + 1] = {" "};

    puts("Serial I/O Test: readLine with tokens");
    printf("Enter text up to %i characters, or end w/ CR\n", MAX_BUFFER);
    printf("Line will be parsed into tokens\n");
    printf("Possible delimitors are (w/ ASCII code): ");
    for (uint8_t delim=0; delim < MAX_DELIMS; delim++)
    {
        printf("'%c' 0x%x ", delims[delim], delims[delim]);
    }
    printf("\n");
    uint8_t num_char = readLine(input, MAX_BUFFER);

    printf("\nYou entered %i characters\n", num_char);

    printLine(input, num_char);
    printf("\n");

    // break input line into tokens
    // when this section has executed, the characters in input
    // which are separated by a delim
    // will now be in an array called tokens
    // with each location in token, a multiple character token
    char *tokens[MAX_TOKENS];
    uint8_t index = 0;
    tokens[index] = strtok(input, delims);
    while ( (tokens[index] != NULL) && (index < MAX_TOKENS - 1) ) {
        index++;
        tokens[index] = strtok(NULL, delims);
    }
    uint8_t tokens_found = index;

    printf("The %i tokens parsed are:\n", tokens_found);
    printf("index token\n");
    for (index=0; index<tokens_found; index++)
    {
        printf("%5i %s\n", index, tokens[index]);

    }
}
