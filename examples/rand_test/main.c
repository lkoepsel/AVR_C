/* rand_test - demonstrate execution times of avr-libc rand() vs. TinyMT()
*/
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "sysclock.h"
#include "unolib.h"
#include "tinymt32.h"

#define gen_x 20
#define gen_y 8
#define print_values 1 // change to 1 to have values printed
uint32_t tinymts[gen_x][gen_y];
uint32_t randos[gen_x][gen_y];

int main (void)
{
    init_sysclock_1();
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
    tmt_init = ticks();
    for (int i = 0; i < gen_x; i++) {
        for (int j = 0; j < gen_y; j++) {
            tinymts[i][j] = tinymt32_generate_uint32(&tinymt);
        }
    }
    tmt_done = ticks();


    rand_init = ticks();
    for (int i = 0; i < gen_x; i++) {
        for (int j = 0; j < gen_y; j++) {
            randos[i][j] = random();
        }
    }
    rand_done = ticks();


    printf("                  TinyMT32  random() \n");
    printf("Execution times: %8u %8u \n", (tmt_done - tmt_init),
     (rand_done - rand_init));

#if print_values
    printf("TinyMT Values\n");
    for (int i = 0; i < gen_x; i++) {
        for (int j = 0; j < gen_y; j++) {
            printf("%12lu", tinymts[i][j]);
        }
        printf("\n");
    }

    printf("rand() Values\n");
    for (int i = 0; i < gen_x; i++) {
        for (int j = 0; j < gen_y; j++) {
            printf("%12lu", randos[i][j]);
        }
        printf("\n");
    }
#endif

    printf("Complete\n");
    /* return never executed */
    return (0);
}
