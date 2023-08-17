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
    uint16_t exec_time;

    uint8_t  pow_8_u;
    uint16_t pow_16_u;
    uint32_t pow_32_u, pow_32_uf;
    float pow_flt;

    puts("Testing multiplication and variable types, (execution time in usec) ");
    srand(ticks());
    uint8_t rand1_8 = (rand() % 20 + 16);
    uint8_t rand2_8 = (rand() % 17 + 16);

    srand(ticks());
    uint16_t rand1_16 = (rand() % 20 + 16);
    uint16_t rand2_16 = (rand() % 17 + 16);

    srandom(ticks());
    uint32_t rand1_32 = (random() % 20 + 16);
    uint32_t rand2_32 = (random() % 17 + 16);

    now = ticks();
    pow_8_u = rand1_8 * rand2_8;
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf(" 8 bit test(%4uus): %3u * %3u =  %4u\n",\
        exec_time, rand1_8, rand2_8, pow_8_u);

    now = ticks();
    pow_16_u = rand1_16 * rand2_16;
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf("16 bit test(%4uus): %3u * %3u =  %4u\n",\
        exec_time, rand1_16, rand2_16, pow_16_u);

    now = ticks();
    pow_16_u = rand1_16 * rand1_16 * rand2_16 * rand2_16;
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf("16 bit test(%4uus): %3u * %3u * %3u * %3u = %6u\n",\
        exec_time, rand1_16, rand1_16, rand2_16, rand2_16, pow_16_u);

    now = ticks();
    pow_32_uf = (uint32_t)rand1_32 * (rand1_32 * rand2_32 * rand2_32);
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf("32 bit test(%4uus): (u)%3lu * (%3lu * %3lu * %3lu) = %8lu\n",\
        exec_time, rand1_32, rand1_32, rand2_32, rand2_32, pow_32_uf);

    now = ticks();
    pow_32_u = rand1_32 * rand1_32 * rand2_32 * rand2_32;
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf("32 bit test(%4uus): %3lu * %3lu * %3lu * %3lu = %8lu\n",\
        exec_time, rand1_32, rand1_32, rand2_32, rand2_32, pow_32_u);

    now = ticks();
    pow_32_uf = (uint32_t)rand1_32 * rand1_32 * rand2_32 * rand2_32;
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf("32 bit test(%4uus): (u)%3lu * %3lu * %3lu * %3lu = %8lu\n",\
        exec_time, rand1_32, rand1_32, rand2_32, rand2_32, pow_32_uf);

    now = ticks();
    pow_flt = (float)rand1_32 * rand1_32 * rand2_32 * rand2_32;
    elapsed = ticks();
    exec_time = ((elapsed - now) >> 4);
    printf(" float test(%4uus): (f) %3lu * %3lu * %3lu * %3lu = %8.2f\n",\
        exec_time, rand1_32, rand1_32, rand2_32, rand2_32, pow_flt);
}
