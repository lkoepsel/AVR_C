# Programming the Arduino Uno in Pure C
## Arduino Framework Replacement Routines
* pinMode(pin, mode): define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin
* digitalWrite(pin, level): set an UNO pin to HIGH or LOW
* analogWrite(pin, n): setup the Timer/Counters to provide a PWM signal
	* pin = Arduino UNO Pin Number, must have a "\~" in its name (3, 5, 6, 9, 10, 11)
	* n = n/255 Duty Cycle, i.e; n=127, 127/255 = 49.8% duty cycle
	* Pin PWM Frequencies
		* UNO pin 3/PD3, 488.3Hz
		* UNO pin 5/PD5, 976.6Hz
		* UNO pin 6/PD6, 976.6Hz
		* UNO pin 9/PB1, 976.6Hz
		* UNO pin 10/PB2, 976.6Hz
		* UNO pin 11/PB3, 488.3Hz

## Includes required for commands
### #include "avr_UNO.h" - General definitions
### #include "analogWrite.h" 
### #include "pinMode.h"
### #include "digitalWrite.h"

