// readLine - reads a line of text until EOL = CR or SIZE reached
// printLine - will echo a line of text, read by readLine

#ifndef READLINE_H
#define READLINE_H

#include <stdio.h>
#include "uart.h"

// uses CR as end of line, might need to be changed to LF
#define CR 13

uint8_t readLine(char *buffer, uint8_t SIZE);
void printLine(char *buffer, uint8_t len);

#endif
