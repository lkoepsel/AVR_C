// serialRead - Can replace analogRead() by getting the 10bit integer data
// from the serial port.
#ifndef SERIALREAD_H
#define SERIALREAD_H

#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "unolib.h"

uint16_t serialRead(void) ;

#endif
