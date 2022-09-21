#include "serialRead.h"

uint16_t serialRead() 
{
    uint16_t value;
    uint8_t values = scanf("%4d", &value);

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
        if (value > 1023)
        {
            value = 1023;
        }
        if (value < 0)
        {
            value = 0;
        }
    }    return value; 
}
