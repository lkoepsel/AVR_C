#include "soft_serial.h"

char num_string[6] = {};
const char debug1[] PROGMEM = "debug:1 ";
const char debug2[] PROGMEM = "debug:2 ";
const char debug3[] PROGMEM = "debug:3 ";

void init_soft_serial()
{
    // // Set TX pin as output, set RX pin as input, RX as input pullup
    DDRD |= _BV(SOFT_TX_PIN);
    DDRD &= ~_BV(SOFT_RX_PIN);
    PORTD |= _BV(SOFT_RX_PIN);
}

void soft_char_write(char data)
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

int8_t soft_char_read()
{
    int8_t data = 0;

    // Wait for start bit
    while (PIND & (1 << SOFT_RX_PIN))
        ;

    // Wait for the middle of the start bit
    _delay_us(BIT_DURATION / 2);
    // Read each bit
    for (int8_t i = 0; i < 8; i++)
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

void soft_int16_write(int16_t number)
{
    itoa(number, num_string, 10);
    soft_string_write(num_string, strlen(num_string));
}

void soft_int16_writef(int16_t number, int8_t size)
{
    itoa(number, num_string, 10);
    int8_t int_size = strlen(num_string);
    for (int8_t i = 0; i < size - int_size; i++)
    {
        soft_char_BL();
    }
    soft_string_write(num_string, strlen(num_string));
}

void soft_int8_write(int8_t number)
{
    itoa(number, num_string, 10);
    soft_string_write(num_string, strlen(num_string));
}

int8_t soft_string_write(char *buffer, int8_t len)
{
    // Transmit data
    int8_t count = 0;
    while ((*buffer != '\0') && (count <= len))
    {
        soft_char_write(*buffer);
        buffer++;
        count++;
    }
    return count;
}

int8_t soft_readLine(char *buffer, int8_t SIZE)
{
    int8_t n_chars = 0;
    int8_t EOL = 0;
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
    } while (!EOL);
    return n_chars;
}

void soft_char_NL(void)
{
    soft_char_write(CR);
    soft_char_write(LF);
}

void soft_char_BL(void)
{
    soft_char_write(BL);
}

void soft_pgmtext_write(const char *pgm_text)
{
    for (uint8_t i = 0; i < strlen_P(pgm_text); i++)
    {
        uint8_t c = pgm_read_byte(&(pgm_text[i]));
        soft_char_write(c);
    }
}
