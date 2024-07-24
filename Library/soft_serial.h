// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction
// Set serial pins below: SOFT_RX_PIN/SOFT_TX_PIN
// Set baud rate below: SOFT_BAUD
// Highest baud rate is 28800

// API:
// init_soft_serial(); initialize the ports, REQUIRED
// void soft_char_write(uint8_t) - writes a binary byte, if ASCII needed, convert w itoa()
// void soft_string_write(char *, int8) - writes a string via pointer, upto len
// uint8_t soft_char_read() - returns a binary byte
// uint8_t soft_readline(char *, uint8) - returns bytes read up to SIZE
// void soft_char_NL(void) - write a new line
// void soft_char_BL(void) - write a space
// void soft_pgmtext_write(const char* pgm_text) - write PROGMEM string
// soft_int16_write - write a int16 number
// soft_int16_writef - write a int16 number, size is width of field, fill with blanks
// soft_int8_write - write a int8 number
// debug(n) - write "debug n:" for debugging purposes, n = 1-3


#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "uart.h"
#include "unolib.h"

#define SOFT_RX_PIN PIND2 // Define the RX pin
#define SOFT_TX_PIN PIND3 // Define the TX pin
#define BIT_DURATION (1000000 / SOFT_BAUD) // Bit duration in microseconds

#define CR 13		// carriage return
#define LF 10		// line feed
#define BL 32		// blank or space (SP is taken for stack pointer)

#define ASCII_INTEGER 0x30 // constant added to an integer(0-9) to make ASCII

extern const char debug1[] PROGMEM ;
extern const char debug2[] PROGMEM ;
extern const char debug3[] PROGMEM ;
#define debug(n) soft_pgmtext_write(debug##n)

void init_soft_serial() ;
void soft_char_write(char data) ;
int8_t soft_char_read() ;

int8_t soft_string_write(char * buffer, int8_t len) ;
int8_t soft_readLine(char *buffer, int8_t SIZE) ;

void soft_int16_write(int16_t number) ;
void soft_int16_writef(int16_t number, int8_t size) ;
void soft_int8_write(int8_t number) ;

void soft_char_NL(void) ;
void soft_char_BL(void) ;
void soft_pgmtext_write(const char* pgm_text) ;

#endif
