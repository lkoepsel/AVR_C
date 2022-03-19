/**
 * Twisted Mersenne 32-bit integer example
 *
 * @brief Simple check program for tinymt32
 *
 * @author Mutsuo Saito (Hiroshima University)
 * @author Makoto Matsumoto (The University of Tokyo)
 *
 * Copyright (C) 2011 Mutsuo Saito, Makoto Matsumoto,
 * Hiroshima University and University of Tokyo.
 * All rights reserved.
 *
 * The 3-clause BSD License is applied to this software, see
 * LICENSE.txt
 *  http://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/TINYMT/index.html#tiny
 * 
 * TinyMT is a new small-sized variant of Mersenne Twister (MT) introduced by 
 * Mutsuo Saito and Makoto Matsumoto in 2011. This specific example outputs
 * 32-bit unsigned integers.
 * 
 * MT was firstly named "Primitive Twisted Generalized Feedback Shift Register 
 * Sequence" by a historical reason.
 * Makoto: Prof. Knuth said in his letter "the name is mouthful." 
 * Takuji:........ 
 * 
 * a few days later 
 * 
 * Makoto:Hi, Takkun, How about "Mersenne Twister?" 
 * Since it uses Mersenne primes, and it shows that it has its ancestor,
 * Twisted GFSR. 
 * Takuji:Well. 
 * Makoto:It sounds like a jet coaster, so it sounds quite fast, 
 * easy to remember and easy to pronounce. Moreover, although it is a secret, 
 * it hides in its name the initials of the inventors. 
 * Takuji:....... 
 * Makoto:Come on, let's go with MT! 
 * Takuji:....well, affirmative. 
 * Later, we got a letter from Prof. Knuth saying "it sounds a nice name." :-)
 * 
 * This example removes all float generation of random numbers
 */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "uart.h"
#include "tinymt32.h"

int main(int argc, char * argv[]) {
    init_serial();

    tinymt32_t tinymt;
    // this value is from example, change to have different results
    tinymt.mat1 = 0x8f7011ee; 
    uint32_t seed = 1;
    printf("tinymt32 0x%08" PRIx32, tinymt.mat1);
    printf(" seed = %lu\n", seed);
    tinymt32_init(&tinymt, seed);
    printf("32-bit unsigned integers r, where 0 <= r < 2^32\n");
    for (uint8_t i=0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%10" PRIu32 " ", tinymt32_generate_uint32(&tinymt));
        }
        printf("\n");
    }
}
