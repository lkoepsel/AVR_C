#include "analogWrite.h"

void clear_all_TC(void) {
    // reset both timer/counter registers
    TCCR0A = 0;
    TCCR0B = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR2A = 0;
    TCCR2B = 0;
}

uint8_t analogWrite(uint8_t apin, uint8_t cycle) {

    // for a better understanding, consult page 102-168 in ATmega328P datasheet
    if (apin == 3) {
        // set UNO pin 3/PD3 to output
        // 16x10^6 / 0xFF / 128 => 488.28Hz
        DDRD |=  _BV(DDD3);
        
        // TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 00100011
        // COM2B1 => PD3
        // WGM21 WGM20 => Fast PWM, 0xFF as counter contents (divide by 256)
        TCCR2A |= (_BV(COM2B1) | _BV(WGM21) | _BV(WGM20));

        // TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
        // CS22 CS20 => scalar of 128
        TCCR2B |=  (_BV(CS22) | _BV(CS20));

        OCR2B = cycle;
        return(0);
    }
    else if (apin == 5) {
        // set UNO pin 5/PD5 to output, 976.6Hz
        DDRD |=  _BV(DDD5);
        
        // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM21 WGM20 ] = 00100011
        TCCR0A |= (_BV(COM0B1) | _BV(WGM21) | _BV(WGM20));

        // TCCR0B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
        TCCR0B |=  (_BV(CS21) | _BV(CS20));

        OCR0B = cycle;
        return(0);
    }
    else if (apin == 6) {
        // set UNO pin 6/PD6 to output, 976.6Hz
        DDRD |=  _BV(DDD6);
        
        // TCCR0A [ COM0A1 COM0A0 COM0B1 COM0B0 0 0 WGM21 WGM20 ] = 11000010
        TCCR0A |= (_BV(COM0A1) | _BV(WGM21) | _BV(WGM20));

        // TCCR0B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
        TCCR0B |=  (_BV(CS21) | _BV(CS20));

        OCR0A = cycle;
        return(0);
    }
    else if (apin == 9) {
        // set UNO pin 9/PB1, 976.6Hz
        DDRB |=  _BV(DDB1);
        
        // TCCR1A [ COM1A1 COM1A0 COM1B1 COM1B0 0 0 WGM11 WGM10 ] = 10000001
        TCCR1A |= (_BV(COM1A1) | _BV(WGM10));

        // TCCR1B [ 1CNC1 1CES1 0 WGM13 WGM12 CS12 CS11 CS10 ]
        TCCR1B |= (_BV(WGM12) | _BV(CS11) | _BV(CS10));

        OCR1A = cycle;
        return(0);
    }
    else if (apin == 10) {
        // set UNO pin 10/PB2 to output, 976.6Hz
        DDRB |=  _BV(DDB2);
        
        // TCCR1A [ COM1A1 COM1A0 COM1B1 COM1B0 0 0 WGM11 WGM10  ] = 00100001
        TCCR1A |= (_BV(COM1B1) | _BV(WGM10));

        // TCCR1B [ 1CNC1 1CES1 0 WGM13 WGM12 CS12 CS11 CS10 ]
        TCCR1B |= (_BV(WGM12) | _BV(CS11) | _BV(CS10));

        OCR1B = cycle;
        return(0);
    }
    else if (apin == 11) {
        // set UNO pin 11/PB3 to output, 488.28Hz
        DDRB |=  _BV(DDB3);
        
        // TCCR2A [ COM2A1 COM2A0 COM2B1 COM2B0 0 0 WGM21 WGM20 ] = 10000011
        TCCR2A |= (_BV(COM2A1) | _BV(WGM21) | _BV(WGM20));

        // TCCR2B [ FOC2A FOC2B 0 0 WGM22 CS22 CS21 CS20 ]
        TCCR2B |= (_BV(CS22) | _BV(CS20));

        OCR2A = cycle;
        return(0);
    }
    else {
        return(1);
    }
}
