// soft serial ISR - adds a software serial port using ISR for timing
// Change serial pins in soft_serial.h: SOFT_RX_PIN/SOFT_TX_PIN
// Set baud rate in soft_serial.h: SOFT_BAUD
#include <stdio.h>
#include "uart.h"

#define F_CPU 16000000UL // Define CPU frequency
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BAUD_RATE 115200
#define BIT_DURATION (1000000 / BAUD_RATE) // Bit duration in microseconds

#define SOFT_RX_PIN PD2 // Define the RX pin
#define SOFT_TX_PIN PD3 // Define the TX pin
#define BLUE (PIND |= (_BV(PORTD7)))
#define RED (PINB |= (_BV(PORTB5)))

volatile uint8_t received_data = 0;
volatile uint8_t data_ready = 0;

void soft_serial_init()
{
    // Set TX pin as output
    DDRD |= (1 << SOFT_TX_PIN);
    // Set RX pin as input
    DDRD &= ~(1 << SOFT_RX_PIN);
    // Enable pull-up resistor on RX pin
    PORTD |= (1 << SOFT_RX_PIN);

    // Configure Timer1 for bit timing
    TCCR1A = 0;                          // Normal mode
    TCCR1B = (1 << WGM12) | (1 << CS11); // CTC mode, prescaler 8
    OCR1A = (F_CPU / 8 / BAUD_RATE) - 1; // Set compare match value
    TIMSK1 |= (1 << OCIE1A);             // Enable compare match interrupt
}

void soft_serial_write(uint8_t data)
{
    // Start bit
    PORTD &= ~(1 << SOFT_TX_PIN);
    _delay_us(BIT_DURATION);

    // Data bits
    for (uint8_t i = 0; i < 8; i++)
    {
        if (data & (1 << i))
        {
            PORTD |= (1 << SOFT_TX_PIN);
        }
        else
        {
            PORTD &= ~(1 << SOFT_TX_PIN);
        }
        _delay_us(BIT_DURATION);
    }

    // Stop bit
    PORTD |= (1 << SOFT_TX_PIN);
    _delay_us(BIT_DURATION);
}

uint8_t soft_serial_read()
{
    uint8_t data = 0;

    // Wait for start bit
    while (PIND & (1 << SOFT_RX_PIN))
        ;

    // Wait for the middle of the start bit
    _delay_us(BIT_DURATION / 2);

    // Read each bit
    for (uint8_t i = 0; i < 8; i++)
    {
        _delay_us(BIT_DURATION);
        if (PIND & (1 << SOFT_RX_PIN))
        {
            data |= (1 << i);
        }
    }

    // Wait for stop bit
    _delay_us(BIT_DURATION);

    return data;
}

// ISR for Timer1 compare match
ISR(TIMER1_COMPA_vect)
{
    static uint8_t bit_count = 0;
    static uint8_t received_byte = 0;
    static uint8_t receiving = 0;

    if (!receiving)
    {
        // BLUE;
        if (!(PIND & (1 << SOFT_RX_PIN)))
        {
            // RED;
            receiving = 1;
            bit_count = 0;
            received_byte = 0;
        }
    }
    else
    {
        if (bit_count < 8)
        {
            if (PIND & (1 << SOFT_RX_PIN))
            {
                received_byte |= (1 << bit_count);
            }
            bit_count++;
        }
        else
        {
            received_data = received_byte;
            data_ready = 1;
            receiving = 0;
        }
    }
}

int main(void)
{
    DDRB |= (_BV(PORTB5));
    DDRD |= (_BV(PORTD7));

    // Initialize hardware serial (if needed)
    init_serial();
    // Initialize software serial
    soft_serial_init();
    sei(); // Enable global interrupts
    puts("ISR Test");
    // Example: Send and receive data
    while (1)
    {
        // Transmit data
        // soft_serial_write('A');
        PINB |= (_BV(PORTB5));

        // _delay_ms(1000);

        // Check if data is ready
        if (data_ready)
        {
            puts("looping");
            data_ready = 0;
            // Process received data (e.g., send it over hardware serial)
            printf("Got: %c\n", received_data);
        }
    }

    return 0;
}
