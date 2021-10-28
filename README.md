# Programming the Arduino Uno in C
This repository provides a framework in  Standard C which mirrors that of the Arduino framework. This allows a student to program the ATmega328P using C in a relatively familar (Arduino) context. The value of programming the ATmega328P in C is that it is easier to understand some of the C concepts using an 8-bit processor as compared to programming in C on a PC. It also allows someone to learn how to program an embedded microcontroller in an easier environment than one like the Raspberry Pi Pico (32-bit microcontroller).

In order to use this framework, one must install the avr-gcc tool chain appropriate for their platform (Linux, macOS, or Windows). The directions to do so is [here](https://wellys.com/posts/avr_c_setup/).
## Arduino Framework  and standard C Replacement Routines
Much of the C Standard Library is provided by [AVR Libc](https://www.nongnu.org/avr-libc/). I recommend having a link to the online manual open while developing code. The code in this repository is the code required to program the Uno using similar routines as in the Arduino Framework.

### Arduino Framework

#### Requires an #include for any function
* #include "unolib.h" - General definitions
Library still needs work to be setup correctly. At present, any function called requires an #include "functionname.h" to be used. For example, to use analogRead(), #include "analogRead.h".

* **analogRead(pin)**: read one of the 6 Analog pins (A0-A5). Returns a 10-bit value in reference to AREF see [analogReference()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/). In this case, it only DEFAULT value of 5V.
* **analogWrite(pin, n)**: setup the Timer/Counters to provide a PWM signal.
	* pin = Arduino UNO Pin Number, must have a "\~" in its name (3, 5, 6, 9, 10, 11)
	* n = n/255 Duty Cycle, i.e; n=127, 127/255 \~= 50% duty cycle
	* Pin PWM Frequencies
		* UNO pin 3/PD3, 488.3Hz
		* UNO pin 5/PD5, 976.6Hz
		* UNO pin 6/PD6, 976.6Hz
		* UNO pin 9/PB1, 976.6Hz
		* UNO pin 10/PB2, 976.6Hz
		* UNO pin 11/PB3, 488.3Hz
* **digitalRead(pin)**: returns value (1 or 0) of Uno pin (pins 0-13 only). If using serial I/O (printf/puts/getchar) then Uno pins 0 and 1 are not usable. Is not configured to use A0-A5.
* **digitalWrite(pin, level)**: set an UNO pin to HIGH, LOW or TOG (pins 0-13 only).  If using serial I/O (printf/puts/getchar) then Uno pins 0 and 1 are not usable. This version also adds TOG, which toggles the level. Much easier than checking the level and setting it to be the opposite level and requires less code. Is not configured to use A0-A5.
* **pinMode(pin, mode)**: define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin (pins 0-13 only). Is not configured to use A0-A5.
* **delay(ms)**: Blocking delay uses built-in \_delay_ms, however allows for a variable as an argument. 
### Standard C functions adapted for the ATmega328P
Requires the following in the file which needs to use the serial I/O functions puts(), printf() and getchar(). scanf() has yet to be debugged. See example *serialio* to see implementation.

```C
# in the include section at the top of the file
#include "uart.h"
#include <stdio.h>

# at the top of the main function, prior to using I/O functions
    uart_init();
    stdout = &uart_output;
    stdin  = &uart_input;
```
* **getChar(char)**: same as C getChar (non-interrupt at this time)
* **printf(string, variables)**: same as C printf(), limited functionality to be documented. There are two ways to add printf and those are documented in the Makefile in the examples. It is also helpful to review the [avr-libc printf](https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html) documentation.
* **puts(string)**: same as C puts()

### Work in Progress
This is a work in progress, the initial version is proof of concept and uses a significant amount of storage. Over-time I'll optimize for size and add error-checking (as possible).

## Examples 
### analogWrite: 
Demo file for using analogWrite(), requires a scope (Labrador used) to see the output of the PWM signal

### blink: 
Essentially the same as the Arduino blink sketch. LED can be set to any Arduino pin (0-13).

### delayTest: 
Demonstrates how to use the delay function.

### durationTest:
An inline test of playing a melody using tone(). This version is easier to test and debug than melody.

### melody: 
Fundamentally, the same as the melody sketch on the Arduino website. The changes made are those required for standard C vs. the Arduino framework.

### pinMode:
Demo file for using pinMode(), provides a short digital waveform on a pin to demonstrate pinMode is working.

### pinTest:
Demo file for using pinTest(), a multi-layer loop through pins (2-13) to allow for checking if INPUT and INPUT_PULL are working. Uses a button with one side to 5V (INPUT) or GND (INPUT_PULLUP), other side to pin to test.

### serialio:
Simple character I/O test using the UART. The USB cable is the only cable required. See note in main.c, as program won't work with specific combinations of a board and serial monitor. Adafruit Metro 328 and minicom for example.

### simple:
Demo file from avr-gcc on-line User Manual [Simple Project](https://www.nongnu.org/avr-libc/user-manual/group__demo__project.html), edited specific to ATmega328P. It is well-worth reviewing as it shows how to use an interrupt. The best way to understand it, is to use a scope (Labrador) to view the waveform change.

### tenthTimer:
Uses the simple framework from above to create a interrupt-based timer which provides a 100Hz signal (10ms period) with a 50% duty cycle. Could be used for multi-tasking, long counters etc. There are other settings which can be used to increase or decrease the frequency. See comments.

### twoTimers:
* Interrupt driven timers which toggle pins (8) 100Hz and (7) 500Hz using timer 0 and timer 1.
* All at 50% duty cycle
* Example Settings:
* T0: 500Hz Pin 7: COM0A1 WGM01 WGM00 CS01 CS00
* T1: 100Hz Pin 8: COM1A1 WGM13 WGM11 WGM10 CS11 CS10 OCR1A=624

## Makefile
The examples make use of a great Makefile courtesy of Elliot William's in his book [Make: AVR Programming](https://www.oreilly.com/library/view/make-avr-programming/9781449356484/). I highly recommend the book and used it extensively to understand how to program the ATmega328P (Arduino UNO) from scratch.

[Makefile](https://github.com/hexagon5un/AVR-Programming/blob/ad2512ee6799e75e25e70043e8dcc8122cb4f5ab/setupProject/Makefile)

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
### Make Commands for Examples
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

## Serial Solutions
#### In use
* [Simple Serial Communications with AVR libc](https://appelsiini.net/2011/simple-usart-with-avr-libc/) Works well, integrated into avr-gcc to enable using printf, puts, and getchar. Uses polling which is slow and blocking.
#### Reviewing to determine how to use due to its interrupts
* [Peter Fleury AVR Software](http://www.peterfleury.epizy.com/avr-software.html) Works, not integrated into avr-gcc library, so not native. It uses interrupts and buffering so it is fast and non-blocking.

## Sources
I also write about C, MicroPython and Forth programming on microcontrollers at [Wellys](https://wellys.com).

Other sources of information which were helpful:
* [AVR Libc](https://www.nongnu.org/avr-libc/)
* [Arduino in C | Freedom Embedded](https://balau82.wordpress.com/arduino-in-c/)
* [Programming Arduino in "Pure C"](http://audiodiwhy.blogspot.com/2019/01/programming-arduino-in-pure-c-now-were.html)
* [EMBEDDS: AVR Tutorials](https://embedds.com/avr-tutorials/)
* [CCRMA: AVR](https://ccrma.stanford.edu/wiki/AVR#AVR_Microcontrollers)
* [Efundies: AVR](https://efundies.com/category/avr/)
