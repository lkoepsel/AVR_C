// progmem - Demonstrates using progmem for storing error messages
#include <avr/pgmspace.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"

const char ParameterA[] PROGMEM = "Parameter A";
const char ParameterB[] PROGMEM = "Parameter B";

PGM_P const array[2] PROGMEM = 
{
    ParameterA,
    ParameterB
};

// Function based on evaluation of pgm_read_byte documentation
// Demonstrates using a char-based approach
void printbychar(const char* ParameterName, uint16_t value)
    {
        // uint8_t max = 11;
        uint8_t c;
        printf("The value of ");
        for (uint8_t i=0; i < strlen_P(ParameterName); i++)
        {
            c = pgm_read_byte(&(ParameterName[i]));
            putchar(c);
        }
        printf(" is %d\n", value);
    }

// Function based on: How do I put an array of strings completely in ROM?
// https://avr-libc.nongnu.org/user-manual/FAQ.html#faq_rom_array
int printProgmem (uint8_t msg, uint16_t value)
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
    printf("The value of %s is %d\n", print_buffer, value);

    return 0;
}


// Function based on: "AVR-GCC and the PROGMEM Attribute" White Paper 
// http://www.fourwalledcubicle.com/AVRArticles.php
// This approach uses a non-standard %S format for reading string from Flash memory
// Add -Wno-format to the CPP line in the Makefile (see line 47) 
void PrintParameterValue(const char* ParameterName , uint8_t ParameterValue)
{
    printf("The value of %S is %d\n", ParameterName, ParameterValue); 
}

int main (void)
{

    init_serial();
    
    PrintParameterValue(ParameterA , 10);
    PrintParameterValue(ParameterB , 20);

    printProgmem(0, 10);
    printProgmem(1, 20);

    printbychar(ParameterA, 10);
    printbychar(ParameterB, 20);

    return 0;
}
