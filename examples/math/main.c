// math - Demonstrates the impact of data types on math results

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "uart.h"


int main (void)
{
    init_serial();

    uint8_t int_8_u, pow_8_u;
    uint16_t int_16_u, pow_16_u;
    uint32_t int_32_u, pow_32_u;
    int8_t int_8_s, pow_8_s;
    int16_t int_16_s, pow_16_s;
    int32_t int_32_s, pow_32_s;
    float flt, pow_flt;
    uint8_t i, j;

    puts("Testing math and variable types (powers of 2 by  data type)");
    printf("i = \t 8 u \t 8 s \t 16 u \t   16 s \t 32 u \t    32 s \t float \t  pow(flt,i)\n");

    for (i=1; i < 33; i++) 
    {
        int_8_u = 2;
        int_16_u = 2;
        int_32_u = 2;
        int_8_s = 2;
        int_16_s = 2;
        int_32_s = 2;
        flt = 2;
        pow_8_u = 1;
        pow_16_u = 1;
        pow_32_u = 1;
        pow_8_s = 1;
        pow_16_s = 1;
        pow_32_s = 1;
        pow_flt = 1;

        for (j=1; j<=i; j++) 
        {
            pow_8_u = pow_8_u * int_8_u;
            pow_16_u = pow_16_u * int_16_u;
            pow_32_u = pow_32_u * int_32_u;
            pow_8_s = pow_8_s * int_8_s;
            pow_16_s = pow_16_s * int_16_s;
            pow_32_s = pow_32_s * int_32_s;
            pow_flt = pow_flt * flt;
            }
        flt = pow(flt, i);
        printf("%3u %6u  %6d  %8u  %8d  %12lu  %12ld %12.1f %12.1f\n",
        i, pow_8_u, pow_8_s, pow_16_u, pow_16_s, pow_32_u, pow_32_s, pow_flt, flt);
    }

    return 0;
}
