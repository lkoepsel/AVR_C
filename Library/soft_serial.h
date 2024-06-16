// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction

#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "unolib.h"
#include "uart.h"

#define SOFT_BAUD 9600
#define BIT_DURATION (1000000 / SOFT_BAUD) // Bit duration in microseconds
#define CR 13

#define SOFT_RX_PIN PIND2 // Define the RX pin
#define SOFT_TX_PIN PIND3 // Define the TX pin

void init_soft_serial() ;

void soft_char_write(uint8_t data) ;

uint8_t soft_char_read() ;

uint8_t soft_string_write(char * buffer, uint8_t len) ;

uint8_t soft_readLine(char *buffer, uint8_t SIZE);

#endif
