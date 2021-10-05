#include "analogRead.h"

// -------- Functions --------- //
static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS2);                   /* ADC clock prescaler /16 */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}

uint16_t analogRead(uint8_t apin) {

	initADC0();
	ADMUX |= (apin);

	// set AD Mux to 0 initially to ensure MUX switches each time
	ADMUX &= (0xF0);
	switch(apin) {
		case 0:
				break;
		case 1:
				ADMUX |= (_BV(MUX0));
				break;
		case 2:
				ADMUX |= (_BV(MUX1));;
				break;
		case 3:
				ADMUX |= (_BV(MUX1) | _BV(MUX0));;
				break;
		case 4:
				ADMUX |= (_BV(MUX2));;
				break;
		case 5:
				ADMUX |= (_BV(MUX2) | _BV(MUX0));;
				break;
	}

	ADCSRA |= (1 << ADSC);                     /* start ADC conversion */
	loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done */
	return(ADC);                            /* Return with value read */
}
