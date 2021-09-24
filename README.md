# Programming the Arduino Uno in Pure C
## Arduino Framework Replacement Routines
* **pinMode(pin, mode)**: define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin (pins 0-13 only)
* **digitalWrite(pin, level)**: set an UNO pin to HIGH or LOW (pins 0-13 only)
* **analogWrite(pin, n)**: setup the Timer/Counters to provide a PWM signal
	* pin = Arduino UNO Pin Number, must have a "\~" in its name (3, 5, 6, 9, 10, 11)
	* n = n/255 Duty Cycle, i.e; n=127, 127/255 = 49.8% duty cycle
	* Pin PWM Frequencies
		* UNO pin 3/PD3, 488.3Hz
		* UNO pin 5/PD5, 976.6Hz
		* UNO pin 6/PD6, 976.6Hz
		* UNO pin 9/PB1, 976.6Hz
		* UNO pin 10/PB2, 976.6Hz
		* UNO pin 11/PB3, 488.3Hz

### Includes required for using routines
* #include "avr_UNO.h" - General definitions
* #include "analogWrite.h" 
* #include "pinMode.h"
* #include "digitalWrite.h"

### Work in Progress
UPDATE: Refactored code in pinMode and digitalWrite to reduce size considerably. This [hint](http://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_port_pass) helped, as I was having issues determining how to pass an I/O port. 

This is a work in progress, the initial version is proof of concept and uses a significant amount of storage. Over-time I'll optimize for size and add error-checking (as possible).


## Examples 
Examples make use of a great Makefile courtesy of Elliot William's in his book [Make: AVR Programming](https://www.oreilly.com/library/view/make-avr-programming/9781449356484/). I highly recommend the book and used it extensively to understand how to program the ATmega328P (Arduino UNO) from scratch.

Specific lines to be aware of:
```bash
15 LIBDIR = ../../Library
# Assumes using the structure of the git folder, 
# meaning the examples are two layers down from the Library. Adjust accordingly.
25 PROGRAMMER_ARGS = -F -V -P /dev/ttyACM0 -b 115200	
# Assumes the Uno is plugged into a specific USB port, 
# the easiest way to determine the correct one is to use the Arduino IDE 
# and check the Port (Tools -> Port)
#### Commands
# simple command to check syntax, similar to Verify in the Arduino IDE
make
# command to compile/link/load, similar to Upload in the Arduino IDE
make flash
# command to show the size of the code
make size
# command to clear out all the cruft created in compiling/linking/loading
make all_clean
```


To [install the proper toolchain](https://wellys.com/posts/avr_c_setup/) required to compile the code.

## Sources
I also write about C, MicroPython and Forth programming on microcontrollers at [Wellys](https://wellys.com).

Other sources of information which were helpful:
* [Arduino in C | Freedom Embedded](https://balau82.wordpress.com/arduino-in-c/)
* https://www.xanthium.in/atmega328p-10bit-sar-adc-usart-serial-transmit-to-pc-data-acquisition-tutorial
* https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP
* https://avogadrosnumber.wordpress.com/2017/09/02/blink-and-led-in-c-on-the-arduino-uno/
* http://audiodiwhy.blogspot.com/2019/01/programming-arduino-in-pure-c-now-were.html
* https://www.tderflinger.com/en/arduino-blinking-led-pure-c
* https://github.com/sagarsp/arduino-blink-c
