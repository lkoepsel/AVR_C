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
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    DDRD = 0xff;
    DDRB = 0xff;

    uint8_t pin, UNO_pin = 9;
    pinMode(UNO_pin, INPUT);
    puts("Testing digitalRead");
    printf("Using Pin %d\n", UNO_pin);
    while(1) {
        pin = digitalRead(UNO_pin);
        printf("Value is: %d\n", pin);
        _delay_ms(1000);
    }
    return(0);
}
