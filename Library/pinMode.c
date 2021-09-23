#include "pinMode.h"


uint8_t pinMode(uint8_t apin, uint8_t mode) {
    uint8_t errno = 0;
    switch (apin) {
        // UNO PINS 0-7 PORT D        
        case 0:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD0);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD0);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD0);
            PORTD |= _BV(DDD0);
        }
        else {
            errno = 1;
        }
        break;
        case 1:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD1);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD1);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD1);
            PORTD |= _BV(DDD1);
        }
        else {
            errno = 1;
        }
        break;
        case 2:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD2);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD2);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD2);
            PORTD |= _BV(DDD2);
        }
        else {
            errno = 1;
        }
        break;
        case 3:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD3);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD3);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD3);
            PORTD |= _BV(DDD3);
        }
        else {
            errno = 1;
        }
        break;
        case 4:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD4);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD4);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD4);
            PORTD |= _BV(DDD4);
        }
        else {
            errno = 1;
        }
        break;
        case 5:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD5);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD5);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD5);
            PORTD |= _BV(DDD5);
        }
        else {
            errno = 1;
        }
        break;
        case 6:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD6);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD6);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD6);
            PORTD |= _BV(DDD6);
        }
        else {
            errno = 1;
        }
        break;
        case 7:
        if (mode == INPUT) {
            DDRD &= ~_BV(DDD7);
        }
        else if (mode == OUTPUT) {
            DDRD |= _BV(DDD7);
        }
        else if (mode == INPUT_PULLUP) {
            DDRD &= ~_BV(DDD7);
            PORTD |= _BV(DDD7);
        }
        else {
            errno = 1;
        }
        break;

        // UNO PINS 8-13 PORT B 0-5        
        case 8:
        if (mode == INPUT) {
            DDRB &= ~_BV(DDB0);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(DDB0);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(DDB0);
            PORTB |= _BV(DDB0);
        }
        else {
            errno = 1;
        }
        break;
        case 9:
        if (mode == INPUT) {
            DDRB &= ~_BV(DDB1);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(DDB1);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(DDB1);
            PORTB |= _BV(DDB1);
        }
        else {
            errno = 1;
        }
        break;
        case 10:
        if (mode == INPUT) {
            DDRB &= ~_BV(DDB2);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(DDB2);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(DDB2);
            PORTB |= _BV(DDB2);
        }
        else {
            errno = 1;
        }
        break;
        case 11:
        if (mode == INPUT) {
            DDRB &= ~_BV(DDB3);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(DDB3);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(DDB3);
            PORTB |= _BV(DDB3);
        }
        else {
            errno = 1;
        }
        break;
        case 12:
        if (mode == INPUT) {
            DDRB &= ~_BV(DDB4);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(DDB4);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(DDB4);
            PORTB |= _BV(DDB4);
        }
        else {
            errno = 1;
        }
        break;
        case 13:
        if (mode == INPUT) {
            DDRB &= ~_BV(DDB5);
        }
        else if (mode == OUTPUT) {
            DDRB |= _BV(DDB5);
        }
        else if (mode == INPUT_PULLUP) {
            DDRB &= ~_BV(DDB5);
            PORTB |= _BV(DDB5);
        }
        else {
            errno = 1;
        }
        break;
        default:
            errno = 1;
        break;
    }
    return(errno);
}  

