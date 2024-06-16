#include "soft_serial.h"

void init_soft_serial() 
{
    // Set TX pin as output, set RX pin as input, RX as input pullup
    DDRD |= _BV(SOFT_TX_PIN);
    DDRD &= ~_BV(SOFT_RX_PIN);
    PORTD |= _BV(SOFT_RX_PIN);
}

void soft_char_write(uint8_t data) 
{
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

uint8_t soft_char_read() 
{
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
            soft_char_write(buffer[i]);
        }
    return 0;
}

uint8_t soft_readLine(char *buffer, uint8_t SIZE)
{
    uint8_t n_chars = 0;
    uint8_t EOL = 0;
    do
    {
        char temp = soft_char_read();
        if (temp == CR)
        {
            EOL = 1;
        }
        else
        {
            buffer[n_chars] = temp;
            n_chars++;
            if (n_chars >= SIZE)
            {
                EOL = 1;
            }
        }
    }
    while (!EOL);
    return n_chars;
}

void soft_char_CRLF(void)
{
    uint8_t lf = 10;
    uint8_t cr = 13;
    soft_char_write(cr);
    soft_char_write(lf);
}