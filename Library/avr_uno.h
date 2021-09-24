#include <avr/io.h>
#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
#define HIGH 1
#define LOW 0

void off_led () ;

void on_led () ;

void set_bit (volatile uint8_t *port, uint8_t bit) ;

void clr_bit (volatile uint8_t *port, uint8_t bit) ;
