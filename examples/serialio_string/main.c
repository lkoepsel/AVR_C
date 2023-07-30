// Use scand to read a string from the serial console

#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    
    char input1[16];
    uint8_t input2[16];

    puts("Serial I/O Test: String");
    while(1) {
        printf("Enter up to 8 char\n");
        fgets(input1, 8, stdin);
        printf("You entered %s\n", input1);

        printf("Enter any number of char\n");
        uint8_t i = 0;
        uint8_t end = 1;
        while (end)
        {
            input2[i] = getchar() - '0';

            if (ferror(stdin))
            {
                printf("Error in reading char");
                clearerr(stdin);
                end = 0;
            }
            else if (feof(stdin))
            {
                printf("End of file encountered");
                clearerr(stdin);
                end = 0;
            }
            else
                i++;
            if (i > 10)
            {
                end = 0;
            }
            for (uint8_t j=0;j<10;j++)
            {
                printf("%i", input2[j]);
            }
            printf("\n");
        }
    }        
}
