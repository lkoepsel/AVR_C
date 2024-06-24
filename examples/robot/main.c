// serialio - demonstrate how to successfully read a line of text and
// use STRTOK() to split the line into tokens (or words)

#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "readLine.h"

#define MAX_BUFFER 24
#define MAX_TOKENS (MAX_BUFFER/2)
#define MAX_DELIMS 3

#define max_cmd_len 4 # this is the maximun number of characters for a command

int main(void) {    

    // init_serial() is always required to use serial port, as well as #include "uart.h"
    init_serial();

    // input is the buffer for the serial port
    // delims are the token delimitors
    char input[MAX_BUFFER + 1] = {};
    char delims[MAX_DELIMS + 1] = {" ,."};
    
    char cmd[max_cmd_len] = {}; # defines the variable which will hold the command

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
    strncpy(cmd, tokens[0], max_cmd_len); # assigns the first token found to be a command
    for (index=0; index<tokens_found; index++)
    {
        printf("%5i %s\n", index, tokens[index]);

    }
    printf("commmand was: %s", cmd);
}
