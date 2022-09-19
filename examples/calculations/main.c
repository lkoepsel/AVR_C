// math - Demonstrates the impact of data types on math calculations

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "uart.h"
#include "sysclock.h"


int main (void)
{
    init_serial();
    init_sysclock_1 ();

    uint16_t now;
    uint16_t elapsed;

    uint8_t  pow_8_u;
    uint16_t pow_16_u;
    uint32_t pow_32_u, pow_32_uf;
    float pow_flt;

    puts("Testing multiplication and variable types, (n ticks of execution) ");    uint8_t rand1 = (rand() % 20 + 16);
    uint8_t rand2 = (rand() % 17 + 16);

    now = ticks();
    pow_8_u = rand1 * rand2;
    elapsed = ticks();
    printf(" 8 bit test(%3u): %3u * %3u =  %4u\n",\
        elapsed - now, rand1, rand2, pow_8_u);

    now = ticks();
    pow_16_u = rand1 * rand2;
    elapsed = ticks();
    printf("16 bit test(%3u): %3u * %3u =  %4u\n",\
        elapsed - now, rand1, rand2, pow_16_u);

    now = ticks();
    pow_16_u = rand1 * rand1 * rand2 * rand2;
    elapsed = ticks();
    printf("16 bit test(%3u): %3u * %3u * %3u * %3u = %6u\n",\
        elapsed - now, rand1, rand1, rand2, rand2, pow_16_u);

    now = ticks();
    pow_32_u = rand1 * rand1 * rand2 * rand2;
    elapsed = ticks();
    printf("32 bit test(%3u): %3u * %3u * %3u * %3u = %8lu\n",\
        elapsed - now, rand1, rand1, rand2, rand2, pow_32_u);

    now = ticks();
    pow_32_uf = (uint32_t)rand1 * (rand1 * rand2 * rand2);
    elapsed = ticks();
    printf("32 bit test(%3u): (u)%3u * (%3u * %3u * %3u) = %8lu\n",\
        elapsed - now, rand1, rand1, rand2, rand2, pow_32_uf);

    now = ticks();
    pow_flt = (float)rand1 * rand1 * rand2 * rand2;
    elapsed = ticks();
    printf(" float test(%3u): (f) %3u * %3u * %3u * %3u = %8.2f\n",\
        elapsed - now, rand1, rand1, rand2, rand2, pow_flt);

    return 0;
}
