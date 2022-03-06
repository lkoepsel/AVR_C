/* micros - demonstrate fine-degree timing counter using system clock
* A system tick = .5 microseconds accessed via micros()
* To test, use the system delay() (blocking, doesn't use clock)
* To minimize overhead, system runs NTIMES filling an array
* then prints out NTIMES number of lines
* consisting of two times, post-delay and pre-delay. 
* The difference between the two are the number of ticks which occured duing delay
* In calculating anything over 32.77ms, add an N multiplier of 65535 for
* every rollover, i.e; 100 has N=3 rollovers (100,000 % 32.77 = 3)
* EX:
*   delay(4) = 8166 ticks = 8000 * .5us = 4ms with a 166 * .5 /4 or 20us overhead
*   delay(25) = 51010 ticks = 5000 * .5us = 25ms with a 1010 * .5 /25 or 20us overhead
*   delay(100) = 204019 ticks = 200000 * .5us = 100ms with a 4019 * .5 /100 or 20us overhead
* CALC: IF (PREV > NOW)
*   TRUE: (N * 65535) + (NOW + 65535) - PREV 
*   FALSE (N * 65535) + NOW - PREV 
*/
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "delay.h"
#include "sysclock.h"
#include "unolib.h"
#include "pinMode.h"
#include "tinymt32.h"

#define gen_x 20
#define gen_y 10
uint32_t tinymts[gen_x][gen_y];
uint32_t randos[gen_x][gen_y];

int main (void)
{
    init_sysclock_1();
    init_sysclock_2();
    init_serial();
    uint16_t tmt_init;
    uint16_t tmt_done;
    uint16_t rand_init;
    uint16_t rand_done;


    printf("Testing Random Number Generators\n");

    tinymt32_t tinymt;
    // this value is from example, change to have different results
    tinymt.mat1 = 0x8f7011ee; 
    uint32_t seed = 1;
    // printf("tinymt32 0x%08" PRIx32, tinymt.mat1);
    // printf(" seed = %lu\n", seed);
    tinymt32_init(&tinymt, seed);

    printf("Generate %d x %d arrays of 32-bit integers \n", gen_x, gen_y);
    printf("using TinyMT32 and random()\n");
    tmt_init = micros();
    for (int i = 0; i < gen_x; i++) {
        for (int j = 0; j < gen_y; j++) {
            tinymts[i][j] = tinymt32_generate_uint32(&tinymt);
            // printf("%10" PRIu32 " ", tinymt32_generate_uint32(&tinymt));
        }
        // printf("\n");
    }
    tmt_done = micros();

    // printf("%d x %d 32-bit integers r using random(), where 0 <= r < 2^32\n",
    //     gen_x, gen_y);
    rand_init = micros();
    for (int i = 0; i < gen_x; i++) {
        for (int j = 0; j < gen_y; j++) {
            randos[i][j] = random();
            // printf("%10" PRIi32 " ", random());
        }
        // printf("\n");
    }
    rand_done = micros();

    printf("                  TinyMT32  random() \n");
    // printf("Times of execution: %u %u %u %u\n", tmt_done, tmt_init, rand_done, rand_init);
    printf("Execution times: %8u %8u \n", tmt_done - tmt_init, rand_done - rand_init);

    /* return never executed */
    return (0);
}
