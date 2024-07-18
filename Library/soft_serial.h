// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction
// Set serial pins below: SOFT_RX_PIN/SOFT_TX_PIN
// Set baud rate below: SOFT_BAUD
// Highest baud rate is 28800

// API:
// init_soft_serial(); initialize the ports, REQUIRED
// void soft_byte_write(uint8_t) - writes a binary byte, if ASCII needed, convert w itoa()
// void soft_string_write(char *, uint8) - writes a string via pointer, upto len
// uint8_t soft_char_read() - returns a binary byte
// uint8_t soft_readline(char *, uint8) - returns bytes read up to SIZE
// void soft_char_NL(void) - write a new line
// void soft_char_space(void) - write a space
// void soft_pgmtext_write(const char* pgm_text) - write PROGMEM string



#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "unolib.h"

#define SOFT_BAUD 9600
#define BIT_DURATION (1000000 / SOFT_BAUD) // Bit duration in microseconds
#define CR 13

#define SOFT_RX_PIN PIND2 // Define the RX pin
#define SOFT_TX_PIN PIND3 // Define the TX pin

void init_soft_serial() ;

void soft_byte_write(uint8_t data) ;
void soft_int16_write(int16_t number);
void soft_int8_write(int8_t number);



uint8_t soft_char_read() ;

uint8_t soft_string_write(char * buffer, uint8_t len) ;

uint8_t soft_readLine(char *buffer, uint8_t SIZE);

void soft_char_NL(void);
void soft_char_space(void);

void soft_pgmtext_write(const char* pgm_text);

#endif
