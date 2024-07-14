#include "soft_serial.h"

char num_string[6] = {};

void init_soft_serial() 
{
    // Set TX pin as output, set RX pin as input, RX as input pullup
    DDRD |= _BV(SOFT_TX_PIN);
    DDRD &= ~_BV(SOFT_RX_PIN);
    PORTD |= _BV(SOFT_RX_PIN);
}

void soft_byte_write(uint8_t data) 
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

void soft_int_write(int16_t number)
{
    itoa(number, num_string, 10);
    soft_string_write(num_string, strlen(num_string));
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
        uint8_t count = 0;
        while ((*buffer != '\0') && (count <= len))
        {
            soft_byte_write(*buffer);
            buffer++;
            count++;
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

void soft_char_NL(void)
{
    uint8_t lf = 10;
    uint8_t cr = 13;
    soft_byte_write(cr);
    soft_byte_write(lf);
}

void soft_char_space(void)
{
    uint8_t space = 0x20;
    soft_byte_write(space);
}

void soft_pgmtext_write(const char* pgm_text)
    {
        for (uint8_t i=0; i < strlen_P(pgm_text); i++)
        {
            uint8_t c = pgm_read_byte(&(pgm_text[i]));
            soft_byte_write(c);
        }
    }
