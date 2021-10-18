/*
 * Demonstration on how to redirect stdio to UART. 
 *
 * http://appelsiini.net/2011/simple-usart-with-avr-libc
 *
 * To compile and upload run: make clean; make; make program;
 * Connect to serial with: screen /dev/tty.usbserial-*
 *
 * Copyright 2011 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 *      Added delays to determine if board is receiving data via TX/RX LEDs
 *      Some boards won't work with some serial programs:
 *          Adafruit Metro - won't minicom and moserial
 *          Adafruit Metro - will Arduino Serial Monitor
 * YMMV
 *
 */
 
#include <stdio.h>
#include "uart.h"
#include "delay.h"

int main(void) {    

    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
                
    char input;

    
    puts("AVR UART");
    delay(2000);
    puts("Char Test");
    while(1) {
        input = getchar();
        delay(2000);
        printf("You entered %c\n", input);        
    }
        
    return 0;
}
