// serialio - demonstrate how to successfully read a line of text and
// use STRTOK() to split the line into tokens (or words)

#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "readLine.h"

#define MAX_BUFFER 16
#define MAX_TOKENS (MAX_BUFFER/2)
#define MAX_DELIMS 3

int main(void) {    

    init_serial();
    char input[MAX_BUFFER + 1] = {};
    char delims[MAX_DELIMS + 1] = {" ,\t"};

    puts("Serial I/O Test: readLine with tokens");
    printf("Enter text up to %i characters, and end w/ CR\n", MAX_BUFFER);
    printf("Line will be parsed into tokens\n");
    uint8_t num_char = readLine(input, MAX_BUFFER);

    printf("You entered %i characters\n", num_char);

    for (uint8_t out_char=0; out_char<MAX_BUFFER; out_char++)
    {
        printf("%c", input[out_char]);
    }
    printf("\n");

    // break input line into tokens
    char *tokens[MAX_TOKENS];
    uint8_t token = 0;
    tokens[token] = strtok(input, delims);
    while ((token < MAX_TOKENS - 1) || (tokens[token] != NULL) ) {
        token++;
        tokens[token] = strtok(NULL, delims);
    }
    uint8_t tokens_found = token;

    printf("Found %i tokens, delimitors were (w/ ASCII code): ", tokens_found);
    for (uint8_t delim=0; delim < MAX_DELIMS; delim++)
    {
        printf("'%c' 0x%x ", delims[delim], delims[delim]);
    }
    printf("\n");
    for (token=0; token<tokens_found; token++)
    {
        printf("%i %s\n", token, tokens[token]);

    }
}
