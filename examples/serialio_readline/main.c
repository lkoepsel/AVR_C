// serialio - demonstrate how to successfully read a line of text

#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    
    char temp;
    // uses CR as end of line, might need to be changed to LF
    const char CR = 13;
    #define MAX_BUFFER 15
    char input[MAX_BUFFER + 1] = {};

    puts("Serial I/O Test: readLine");
    while(1)
    {
        printf("Enter text up to %i characters, and end w/ CR\n", MAX_BUFFER);
        uint8_t in_char = 0;
        uint8_t EOL = 0;
        do
        {
            temp = getchar();
            if (temp == CR)
            {
                EOL = 1;
            }
            else
            {
                input[in_char] = temp;
                in_char++;
                if (in_char >= MAX_BUFFER)
                {
                    EOL = 1;
                }
            }
        }
        while (!EOL);

        printf("\n");
        for (uint8_t out_char=0;out_char<MAX_BUFFER;out_char++)
        {
            printf("%c", input[out_char]);
            // erases buffer for next use, might not be desired
            input[out_char] = 0;
        }
        printf("\n");
    }
}
