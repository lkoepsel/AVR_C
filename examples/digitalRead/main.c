#include <stdio.h>
#include "uart.h"
#include <avr/io.h>
#include "delay.h"
#include "unolib.h"
#include "pinMode.h"
#include "digitalRead.h"

#define BLINK_DELAY_MS 50

int main (void)
{
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
    // DDRD = 0xff;
    // DDRB = 0xff;

    uint8_t pin;
    puts("Testing digitalRead");
    while(1) {
        for(int8_t i=2;i<=13;i++) {
            pinMode(i, INPUT_PULLUP);
            printf("Using Pin %d\n", i);
            for (uint8_t j=0;j<=9;j++) {
                pin = digitalRead(i);
                printf("Value is: %d\n", pin);
                delay(500);
            }
        }
    }
    return(0);
}
