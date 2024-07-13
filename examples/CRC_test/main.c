// CRC Test - test the viablilty of using a CRC function
// Uses Optimized CRC-CCITT calculation, seems to be less susceptible to dupes
// Creates an array of 300 integers using a ticks() seed for rand
// Calculates the CRC for this array
// Performs N times
// _crc16_update - seemed to be susceptible to dupes
// _crc_xmodem_update - seemed to be susceptible to dupes
// _crc_ccitt_update - slightly less susceptible to duplicates

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "sysclock.h"
#include "unolib.h"
#include <util/crc16.h>

#define N_rands 150         // number of random numbers
#define N_tests 300         // number of tests to run
#define N_functions 3       // number of CRC functions to test
uint16_t randos[N_rands] = {0};   // random number array for data
uint16_t CRCs[N_tests] = {0};     // array for CRC test results

uint16_t checkCRC (uint16_t *ptr, int16_t size)
{
    uint16_t crc = 0xffff;
    while (size > 0)
    {
        crc = _crc16_update(crc, *ptr);
        ptr++;
        size--;
    }
    return crc; 
}

int main (void)
{
    init_sysclock_1();
    init_serial();
    char input;

    // Prints title then waits for enter
    // The amount of time in ticks, provides the random seed
    printf("Testing CRC Check\n");
    puts("Press enter to start");
    while((input = getchar())!= 0x0d) {}

    uint16_t ticks_rand = ticks();
    printf("ticks %u\n", ticks_rand);
    srand(ticks_rand);

    // Performs N_tests CRC calculations on an array of N_rands 
    for (int j = 0; j < N_tests; j++)
    {
        for (int i = 0; i < N_rands; i++) 
        {
            randos[i] = rand();
        }
        CRCs[j]  = checkCRC(randos, N_rands);
    }    

    uint16_t ctr = 0;
    uint8_t complete = 0;
    while ((ctr == 0) && (complete == 0) )
    {
        for (int i = 0; i < N_tests; i++) 
        {
            for (int j = 0; j < N_tests; j++)
            {
                if ((CRCs[i] == CRCs[j]) && (i != j))
                {
                    ctr++;
                }
            }
        }
        complete = 1;
    }
    if (ctr != 0)
    {
        printf("\n %u Identical CRCs\n", ctr);
    }
    printf("Complete\n");

    // return never executed
    return (0);
}
