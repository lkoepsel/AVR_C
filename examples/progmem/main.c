// progmem - Demonstrates using progmem for storing error messages
#include <avr/pgmspace.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "sysclock.h"
#include "unolib.h"

const char ParameterA[] PROGMEM = "Parameter A";
const char ParameterB[] PROGMEM = "Parameter B";

PGM_P const array[2] PROGMEM = 
{
    ParameterA,
    ParameterB
};

// Function based on evaluation of pgm_read_byte documentation
// Demonstrates using a char-based approach
void Print_by_char(const char* ParameterName, uint16_t value)
    {
        // uint8_t max = 11;
        printf("The value of ");
        for (uint8_t i=0; i < strlen_P(ParameterName); i++)
        {
            uint8_t c = pgm_read_byte(&(ParameterName[i]));
            putchar(c);
        }
        printf(" is %u\n", value);
    }

// // Function based on: How do I put an array of strings completely in ROM?
// // https://avr-libc.nongnu.org/user-manual/FAQ.html#faq_rom_array
int Print_FAQ_Solution (uint8_t msg, uint16_t value)
{
    // RAM buffer used for print message
    char print_buffer[32];
    // Declare variable ptr, so that is a pointer to a string in program space.
    PGM_P ptr;
    
    // Set of 3 instructions, which fetch the string, place in RAM, then print
    // The memcpy_P() function is similar to memcpy(), 
    // except the src string resides in program space.
    memcpy_P(&ptr, &array[msg], sizeof(PGM_P));

    // The strcpy_P() function is similar to strcpy(),
    // except that src is a pointer to a string in program space.
    strcpy_P(print_buffer, ptr);
    printf("The value of %s is %u\n", print_buffer, value);

    return 0;
}


// Function based on: "AVR-GCC and the PROGMEM Attribute" White Paper 
// http://www.fourwalledcubicle.com/AVRArticles.php
// This approach uses a non-standard %S format for reading string from Flash memory
// Uncomment -Wno-format line 88 in the Makefile
void Print_S_Format(const char* ParameterName , uint8_t ParameterValue)
{
    printf("The value of %S is %d\n", ParameterName, ParameterValue); 
}

int main (void)
{

    init_serial();
    
    init_sysclock_1 ();    
    uint16_t now;
    uint16_t elapsed;
    uint16_t now_ro;
    uint16_t elapsed_ro;

    now = ticks();
    now_ro = ticks_ro();
    Print_S_Format(ParameterA , 10);
    elapsed = ticks();
    elapsed_ro = ticks_ro();
    Print_S_Format(ParameterB , 20);
    printf("Print_S_Format Execution time: %u%u\n",\
        elapsed_ro -now_ro, elapsed - now);

    now = ticks();
    Print_FAQ_Solution(0, 10);
    elapsed = ticks();
    Print_FAQ_Solution(1, 20);
    printf("Print_FAQ_Solution Execution time: %u%u\n",
    elapsed_ro -now_ro, elapsed - now);

    now = ticks();
    Print_by_char(ParameterA, 10);
    elapsed = ticks();
    Print_by_char(ParameterB, 20);
    printf("Print_by_char Execution time: %u%u\n",\
    elapsed_ro -now_ro, elapsed - now);

    return 0;
}
