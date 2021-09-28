# Programming the Arduino Uno in C
The intention of this repository is to provide a framework in C which mirrors that of the Arduino framework. This allows a student to program the ATmega328P using C in a relatively familar context. The value of programming the ATmega328P in C is that it is easier to understand some of the C concepts using an 8-bit processor as compared to programming in C on a PC. It also allows someone to learn how to program an embedded microcontroller in an easier environment than one like the Raspberry Pi Pico (32-bit microcontroller).

In order to use this framework, one must install the avr-gcc tool chain appropriate for their platform (Linux, macOS, or Windows). The directions to do so is [here](https://wellys.com/posts/avr_c_setup/).
## Arduino Framework  and standard C Replacement Routines
### Arduino Framework
* **analogWrite(pin, n)**: setup the Timer/Counters to provide a PWM signal.
	* pin = Arduino UNO Pin Number, must have a "\~" in its name (3, 5, 6, 9, 10, 11)
	* n = n/255 Duty Cycle, i.e; n=127, 127/255 = 49.8% duty cycle
	* Pin PWM Frequencies
		* UNO pin 3/PD3, 488.3Hz
		* UNO pin 5/PD5, 976.6Hz
		* UNO pin 6/PD6, 976.6Hz
		* UNO pin 9/PB1, 976.6Hz
		* UNO pin 10/PB2, 976.6Hz
		* UNO pin 11/PB3, 488.3Hz
* **delay(n)**: performs a blocking delay of n ms. n must be a constant and can be upto 65535.
* **digitalRead(pin)**: returns value (1 or 0) of Uno pin (pins 0-13 only). If using serial I/O (printf/puts/getchar) then Uno pins 0 and 1 are not usable.
* **digitalWrite(pin, level)**: set an UNO pin to HIGH or LOW (pins 0-13 only).  If using serial I/O (printf/puts/getchar) then Uno pins 0 and 1 are not usable.
* **pinMode(pin, mode)**: define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin (pins 0-13 only).
### Standard C functions adapted for the ATmega328P
Requires both #include "uart.h" and #include <stdio.h>
* **getChar(char)**: same as C getChar (non-interrupt at this time)
* **printf(string, variables)**: same as C printf, limited functionality to be documented
* **puts(string)**: same as C puts

### Existing C functions in avr-gcc, which mirror Arduino functionality
Requires #include <ctype.h>
* int 	isalnum (int \__c)
* int 	isalpha (int \__c)
* int 	isascii (int \__c)
* int 	isblank (int \__c) 
* int 	iscntrl (int \__c)
* int 	isdigit (int \__c)
* int 	isgraph (int \__c)
* int 	islower (int \__c)
* int 	isprint (int \__c)
* int 	ispunct (int \__c)
* int 	isspace (int \__c)
* int 	isupper (int \__c)
* int 	isxdigit (int \__c)

### Includes required for using routines
* #include "avr_UNO.h" - General definitions
* #include "analogWrite.h" 
* #include "pinMode.h"
* #include "digitalWrite.h"

Library still needs work to be setup correctly. At this time, any routine needs to be included to be used.

### Work in Progress
This is a work in progress, the initial version is proof of concept and uses a significant amount of storage. Over-time I'll optimize for size and add error-checking (as possible).

## Examples 
### analogWrite: 
Demo file for using analogWrite(), requires a scope (Labrador used) to see the output of the PWM signal

### blink: 
Essentially the same as the Arduino blink sketch. LED can be set to any Arduino pin (0-13).

### pinMode:
Demo file for using pinMode(), provides a short digital waveform on a pin to demonstrate pinMode is working.

### pinTest:
Demo file for using pinTest(), a multi-layer loop through pins (2-13) to allow for checking if INPUT and INPUT_PULL are working. Uses a button with one side to 5V (INPUT) or GND (INPUT_PULLUP), other side to pin to test.

### simple:
Demo file from avr-gcc on-line User Manual [Simple Project](https://www.nongnu.org/avr-libc/user-manual/group__demo__project.html), edited specific to ATmega328P. It is well-worth reviewing as it shows how to use an interrupt. The best way to understand it, is to use a scope (Labrador) to view the waveform change.

### tenthTimer:
Uses the simple framework from above to create a interrupt-based timer which provides a 100Hz signal (10ms period) with a 50% duty cycle. Could be used for multi-tasking, long counters etc. There are other settings which can be used to increase or decrease the frequency. See comments.

### usart:
Demo file for testing the serial interface (USB). Requires a serial program like minicom or Putty to test.

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
```
## Make Commands for Examples
```
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
* [Programming Arduino in "Pure C"](http://audiodiwhy.blogspot.com/2019/01/programming-arduino-in-pure-c-now-were.html)
* [Simple Serial Communications with AVR libc](https://appelsiini.net/2011/simple-usart-with-avr-libc/)
* [EMBEDDS: AVR Tutorials](https://embedds.com/avr-tutorials/)
* [CCRMA: AVR](https://ccrma.stanford.edu/wiki/AVR#AVR_Microcontrollers)
* [Efundies: AVR](https://efundies.com/category/avr/)
