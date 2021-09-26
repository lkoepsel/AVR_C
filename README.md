# Programming the Arduino Uno in C
The intention of this repository is to provide a framework in C which mirrors that of the Arduino framework. This allows a student to program the ATmega328P using C in a relatively familar context. The value of programming the ATmega328P in C is that it is easier to understand some of the C concepts using an 8-bit processor as compared to programming in C on a PC. It also allows someone to learn how to program an embedded microcontroller in an easier environment than one like the Raspberry Pi Pico (32-bit microcontoller).

In order to use this framework, one must install the avr-gcc tool chain appropriate for their platform (Linux, macOS, or Windows). The directions to do so is [here](https://wellys.com/posts/avr_c_setup/).
## Arduino Framework  and standard C Replacement Routines
### Arduino Framework
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
* **digitalRead(pin)**: returns value (1 or 0) of Uno pin (pins 0-13 only)
* **digitalWrite(pin, level)**: set an UNO pin to HIGH or LOW (pins 0-13 only)
* **pinMode(pin, mode)**: define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin (pins 0-13 only)
### Standard C routines adapted for the ATmega328P
* **getChar(char)**: same as C getChar (non-interrupt at this time)
* **printf(string, variables)**: same as C printf, limited functionality to be documented
* **puts(string)**: same as C puts

### Includes required for using routines
* #include "avr_UNO.h" - General definitions
* #include "analogWrite.h" 
* #include "pinMode.h"
* #include "digitalWrite.h"

Library still needs work to be setup correctly. At this time, any routine needs to be included to be used.

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
* [AVR Libc](https://www.nongnu.org/avr-libc/)
* [Arduino in C | Freedom Embedded](https://balau82.wordpress.com/arduino-in-c/)
* [Programming Arduino in "Pure C"]http://audiodiwhy.blogspot.com/2019/01/programming-arduino-in-pure-c-now-were.html
* [Simple Serial Communications with AVR libc](https://appelsiini.net/2011/simple-usart-with-avr-libc/)
