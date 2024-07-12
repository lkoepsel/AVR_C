// CRC Test - test the viablilty of using a CRC function
// Uses Optimized CRC-CCITT calculation, seems to be less susceptible to dupes
// Creates an array of 300 integers using a ticks() seed for rand
// Calculates the CRC for this array
// Performs N times
// _crc16_update - seemed to be susceptible to dupes
// _crc_xmodem_update - seemed to be susceptible to dupes
// _crc_ccitt_update - slightly less susceptible

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "sysclock.h"
#include "unolib.h"
#include <util/crc16.h>

#define N_rands 300         // number of random numbers
#define N_tests 100         // number of tests to run
#define N_functions 3       // number of CRC functions to test
uint16_t randos[N_rands] = {0};   // random number array for data
uint16_t CRCs[N_tests] = {0};     // array for CRC test results
static uint16_t (*p_func)(uint16_t a, uint8_t b);

int
checkcrc (void)
{
    uint16_t crc = 0xffff, i;
 
    for (i = 0; i < N_rands; i++)
        crc = _crc16_update(crc, randos[i]);
 
    return crc; 
}

int main (void)
{
    init_sysclock_1();
    init_serial();
    char input;

    p_func = _crc_ccitt_update;

    // Prints title then waits for enter
    // The amount of time in ticks, provides the random seed
    printf("Testing CRC Check\n");
    puts("Press enter to start");
    while((input = getchar())!= 0x0d) {}

    for (int j = 0; j < N_tests; j++)
    {
        srand(ticks());
        for (int i = 0; i < N_rands; i++) 
        {
            randos[i] = rand();
        }
        CRCs[j]  = checkcrc();
    }    

    int loop = 0;
    int ctr = 0;
    while ((ctr != 0) || (loop <= 100))
    {
        for (int i = 0; i < N_tests; i++) 
        {
            for (int j = 0; j < N_tests; j++)
            {
                if ((CRCs[i] == CRCs[j]) && (i != j))
                {
                    ctr++;
                    // printf("%i %i %12u\n", i, j, CRCs[i]);
                }
            }
        }
        loop++;
        printf("%i", loop);
    }
    printf("Loops and Identical CRCs: %i %i\n", loop, ctr);
    printf("Complete\n");
    /* return never executed */
    return (0);
}
