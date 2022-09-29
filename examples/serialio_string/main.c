// Use scand to read a string from the serial console

#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    
    char input1[8];
    char input2[8];

    puts("Serial I/O Test: String");
    while(1) {
        scanf("%s %s", input1, input2);
        printf("You entered %s %s\n", input1, input2);        
    }        
    return 0;
}
