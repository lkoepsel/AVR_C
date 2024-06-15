// soft serial - adds a software defined serial port
// transmit works, receive hangs

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "unolib.h"
#include "uart.h"

#define BAUD_RATE 9600
#define BIT_DURATION (1000000 / BAUD_RATE) // Bit duration in microseconds

#define SOFT_RX_PIN PIND2 // Define the RX pin
#define SOFT_TX_PIN PIND3 // Define the TX pin

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

uint8_t soft_string_write(char * buffer, uint8_t len)
{
        // Transmit data
        for (uint8_t i=0; i < len ; i++)
        {
            soft_serial_write(buffer[i]);
        }
    return 0;
}

int main(void) {
    // Initialize software serial and hardware serial (UART)
    soft_serial_init();
    init_serial();

    char letters[12] = {"Soft Serial"};

    // Example: Send and receive data
    while (1) {
        soft_string_write(letters, (sizeof(letters)/sizeof(letters[0])));
        // Receive data
        uint8_t received = soft_serial_read();
        putchar(received);
    }

    return 0;
}
