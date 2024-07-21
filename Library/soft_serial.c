#include <avr/io.h>
#include <avr/interrupt.h>
#include "soft_serial.h"

char num_string[6] = {};
const char debug1[] PROGMEM = "debug:1 ";
const char debug2[] PROGMEM = "debug:2 ";
const char debug3[] PROGMEM = "debug:3 ";
volatile uint8_t received_data = 0;
volatile uint8_t data_ready = 0;

void init_soft_serial()
{
    // // Set TX pin as output, set RX pin as input, RX as input pullup
    // DDRD |= _BV(SOFT_TX_PIN);
    // DDRD &= ~_BV(SOFT_RX_PIN);
    // PORTD |= _BV(SOFT_RX_PIN);

    // Set TX pin as output
    DDRD |= (1 << SOFT_TX_PIN);
    // Set RX pin as input
    DDRD &= ~(1 << SOFT_RX_PIN);
    // Enable pull-up resistor on RX pin
    PORTD |= (1 << SOFT_RX_PIN);

    // Configure Timer1 for bit timing
    TCCR1A = 0;                             // Normal mode
    TCCR1B = (1 << WGM12) | (1 << CS10);    // CTC mode, prescaler 1
    OCR1A = (F_CPU / SOFT_BAUD) - 1;        // Set compare match value
    TIMSK1 |= (1 << OCIE1A);                // Enable compare match interrupt
}

void soft_byte_write(uint8_t data)
{
    // // Start bit
    // PORTD &= ~(1 << SOFT_TX_PIN);
    // _delay_us(BIT_DURATION);

    // // Data bits
    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     if (data & (1 << i))
    //     {
    //         PORTD |= (1 << SOFT_TX_PIN);
    //     }
    //     else
    //     {
    //         PORTD &= ~(1 << SOFT_TX_PIN);
    //     }
    //     _delay_us(BIT_DURATION);
    // }

    // // Stop bit
    // PORTD |= (1 << SOFT_TX_PIN);
    // _delay_us(BIT_DURATION);


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
        soft_char_space();
    }
    soft_string_write(num_string, strlen(num_string));
}

void soft_int8_write(int8_t number)
{
    itoa(number, num_string, 10);
    soft_string_write(num_string, strlen(num_string));
}

uint8_t soft_char_read()
{
    // uint8_t data = 0;

    // // Wait for start bit
    // while (PIND & (1 << SOFT_RX_PIN))
    //     ;

    // // Wait for the middle of the start bit
    // _delay_us(BIT_DURATION / 2);
    // // Read each bit
    // for (uint8_t i = 0; i < 8; i++)
    // {
    //     _delay_us(BIT_DURATION);
    //     if (PIND & (1 << SOFT_RX_PIN))
    //     {
    //         data |= (1 << i);
    //     }
    // }

    // // Wait for stop bit
    // _delay_us(BIT_DURATION);

    // return data;

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

uint8_t soft_string_write(char *buffer, uint8_t len)
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
    } while (!EOL);
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

void soft_pgmtext_write(const char *pgm_text)
{
    for (uint8_t i = 0; i < strlen_P(pgm_text); i++)
    {
        uint8_t c = pgm_read_byte(&(pgm_text[i]));
        soft_byte_write(c);
    }
}
