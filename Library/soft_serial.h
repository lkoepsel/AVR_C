// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction

#ifndef SOFT_SERIAL_H
#define SOFT_SERIAL_H

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "unolib.h"
#include "uart.h"

// BAUD defined in env.make
#define BIT_DURATION (1000000 / BAUD) // Bit duration in microseconds

#define SOFT_RX_PIN PIND2 // Define the RX pin
#define SOFT_TX_PIN PIND3 // Define the TX pin

void soft_serial_init() ;

void soft_char_write(uint8_t data) ;

uint8_t soft_char_read() ;

uint8_t soft_string_write(char * buffer, uint8_t len) ;

#endif