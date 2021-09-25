#include "avr_uno.h"
#include "pinMode.h"
#include "digitalRead.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"

#define BLINK_DELAY_MS 50

int main (void)
{
    uint8_t UNO_pin = 10;
    uint8_t pin;
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    pinMode(UNO_pin, INPUT_PULLUP);
    puts("Testing digitalRead");
    printf("Using Pin %d\n", UNO_pin);
    while(1) {
        pin = digitalRead(UNO_pin);
        printf("Value is: %d\n", pin);
        _delay_ms(1000);
    }
    return(0);
}
