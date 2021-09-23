#include "digitalWrite.h"

uint8_t digitalWrite(uint8_t apin, uint8_t level) {
    uint8_t errno = 0;
    switch (apin) {
        // UNO PINS 0-7 PORT D        
        case 0:
        if (level == LOW) {
            PORTD &= ~_BV(DDD0);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD0);
        }
        else {
            errno = 1;
        }
        break;
        case 1:
        if (level == LOW) {
            PORTD &= ~_BV(DDD1);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD1);
        }
        else {
            errno = 1;
        }
        break;
        case 2:
        if (level == LOW) {
            PORTD &= ~_BV(DDD2);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD2);
        }
        else {
            errno = 1;
        }
        break;
        case 3:
        if (level == LOW) {
            PORTD &= ~_BV(DDD3);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD3);
        }
        else {
            errno = 1;
        }
        break;
        case 4:
        if (level == LOW) {
            PORTD &= ~_BV(DDD4);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD4);
        }
        else {
            errno = 1;
        }
        break;
        case 5:
        if (level == LOW) {
            PORTD &= ~_BV(DDD5);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD5);
        }
        else {
            errno = 1;
        }
        break;
        case 6:
        if (level == LOW) {
            PORTD &= ~_BV(DDD6);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD6);
        }
        else {
            errno = 1;
        }
        break;
        case 7:
        if (level == LOW) {
            PORTD &= ~_BV(DDD7);
        }
        else if (level == HIGH) {
            PORTD |= _BV(DDD7);
        }
        else {
            errno = 1;
        }
        break;

        // UNO PINS 8-13 PORT B 0-5        
        case 8:
        if (level == LOW) {
            PORTB &= ~_BV(DDB0);
        }
        else if (level == HIGH) {
            PORTB |= _BV(DDB0);
        }
        else {
            errno = 1;
        }
        break;
        case 9:
        if (level == LOW) {
            PORTB &= ~_BV(DDB1);
        }
        else if (level == HIGH) {
            PORTB |= _BV(DDB1);
        }
        else {
            errno = 1;
        }
        break;
        case 10:
        if (level == LOW) {
            PORTB &= ~_BV(DDB2);
        }
        else if (level == HIGH) {
            PORTB |= _BV(DDB2);
        }
        else {
            errno = 1;
        }
        break;
        case 11:
        if (level == LOW) {
            PORTB &= ~_BV(DDB3);
        }
        else if (level == HIGH) {
            PORTB |= _BV(DDB3);
        }
        else {
            errno = 1;
        }
        break;
        case 12:
        if (level == LOW) {
            PORTB &= ~_BV(DDB4);
        }
        else if (level == HIGH) {
            PORTB |= _BV(DDB4);
        }
        else {
            errno = 1;
        }
        break;
        case 13:
        if (level == LOW) {
            PORTB &= ~_BV(DDB5);
        }
        else if (level == HIGH) {
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
