// math - Demonstrates the impact of data types on math results
// TO view float numbers be sure to uncomment the ~line 58
// LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "uart.h"


int main (void)
{
    init_serial();

    puts("Maximum Value by data type");
    puts("Demonstrates float precision issue");
    printf(" i uint8_t  int8_t  uint16_t   int16_t      uint32_t\
       int32_t          float     pow(flt,i)\n");

    for (uint8_t i=1; i < 33; i++) 
    {
        uint8_t int_8_u = 2;
        uint16_t int_16_u = 2;
        uint32_t int_32_u = 2;
        int8_t int_8_s = 2;
        int16_t int_16_s = 2;
        int32_t int_32_s = 2;
        float flt = 2;
        uint8_t pow_8_u = 1;
        uint16_t pow_16_u = 1;
        uint32_t pow_32_u = 1;
        int8_t pow_8_s = 1;
        int16_t pow_16_s = 1;
        int32_t pow_32_s = 1;
        float pow_flt = 1;

        for (uint8_t j=1; j<=i; j++) 
        {
            if (j < 8)
            {
                pow_8_u = pow_8_u * int_8_u;
            }
            else if (j ==  8)
            {
                pow_8_u = (pow_8_u * int_8_u) - 1 ;
            }
            else
            {
                pow_8_u = 0;
            }
            if (j < 16)
            {
                pow_16_u = pow_16_u * int_16_u;
            }
            else if (j == 16)
            {
                pow_16_u = (pow_16_u * int_16_u) - 1;
            }
            else
            {
                pow_16_u = 0;
            }
            if (j < 32)
            {
                pow_32_u = pow_32_u * int_32_u;
            }
            else if (j == 32)
            {
                pow_32_u = (pow_32_u * int_32_u) - 1;
            }
            else
            {
                pow_32_u = 0;
            }
            pow_8_s = pow_8_s * int_8_s;
            pow_16_s = pow_16_s * int_16_s;
            pow_32_s = pow_32_s * int_32_s;
            pow_flt = pow_flt * flt;
            }
        flt = pow(flt, i);
        printf("%3u %6u  %6d  %8u  %8d  %12lu  %12ld %14.1f %14.1f\n",
        i, pow_8_u, pow_8_s, pow_16_u, pow_16_s, pow_32_u, pow_32_s, pow_flt, flt);
    }

    return 0;
}
