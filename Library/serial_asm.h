// serial_asm.h
// C declarations for the assembly routines in serial.S
#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Initialise TX/RX pin directions and idle state.
// Must be called before char_write or char_read.
void init_soft_serial(void);

// Transmit one byte at 9600-8-N-1.
// The character is passed in r24 per the AVR-GCC ABI.
void soft_char_write(uint8_t c);

// Block until one byte is received; return it.
// The result is returned in r24 per the AVR-GCC ABI.
uint8_t soft_char_read(void);

#ifdef __cplusplus
}
#endif
