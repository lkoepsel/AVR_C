// Software Serial as defined by Kagi Code AI

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "uart.h"

#define BAUD_RATE 9600
#define BIT_DURATION (1000000 / BAUD_RATE) // Bit duration in microseconds

#define SOFT_RX_PIN PD2 // Define the RX pin
#define SOFT_TX_PIN PD3 // Define the TX pin

void soft_serial_init() {
    // Set TX pin as output
    DDRD |= (1 << SOFT_TX_PIN);
    // Set RX pin as input
    DDRD &= ~(1 << SOFT_RX_PIN);
    // Enable pull-up resistor on RX pin
    PORTD |= (1 << SOFT_RX_PIN);
}

void soft_serial_write(uint8_t data) {
    // Start bit
    PORTD &= ~(1 << SOFT_TX_PIN);
    _delay_us(BIT_DURATION);

    // Data bits
    for (uint8_t i = 0; i < 8; i++) {
        if (data & (1 << i)) {
            PORTD |= (1 << SOFT_TX_PIN);
        } else {
            PORTD &= ~(1 << SOFT_TX_PIN);
        }
        _delay_us(BIT_DURATION);
    }

    // Stop bit
    PORTD |= (1 << SOFT_TX_PIN);
    _delay_us(BIT_DURATION);
}

uint8_t soft_serial_read() {
    uint8_t data = 0;

    // Wait for start bit
    while (PIND & (1 << SOFT_RX_PIN));

    // Wait for the middle of the start bit
    _delay_us(BIT_DURATION / 2);

    // Read each bit
    for (uint8_t i = 0; i < 8; i++) {
        _delay_us(BIT_DURATION);
        if (PIND & (1 << SOFT_RX_PIN)) {
            data |= (1 << i);
        }
    }

    // Wait for stop bit
    _delay_us(BIT_DURATION);

    return data;
}

int main(void) {
    // Initialize hardware serial (if needed)
    // Initialize software serial
    soft_serial_init();
    init_serial();

    char letters[12] = {"Soft Serial"};

    // Example: Send and receive data
    while (1) {
        // Transmit data
        for (uint8_t i=0; i < (sizeof(letters)/sizeof(letters[0])) ; i++)
        {
            soft_serial_write(letters[i]);
            // _delay_ms(100);
        }
        // Receive data
        uint8_t received = soft_serial_read();
        putchar(received);
    }

    return 0;
}
