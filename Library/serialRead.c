#include "serialRead.h"

uint16_t serialRead(void)
{
    int16_t value;
    uint8_t values = scanf("%4i", &value);

    if (values == 0)
    {
        puts("Conversion error, exiting.");
        exit(1);
    }
    else if (values == EOF) 
    {
        puts("EOF, exiting.");
        exit(1);
    }
    else 
    {
        value = min(value, 1023);
        value = max(value, 0);

    }    
    return value; 
}
