# Programming the Arduino Uno in Standard C

## Introduction
This repository provides a framework in  [*C* (ANSI C99)](http://avr-libc.nongnu.org) which mirrors that of the Arduino framework. This allows a student to program the ATmega328P or equivalents using a standardized **C** in a relatively familar (Arduino) context. This serves the following:
* The *C language* used in this framework follows the [*C99*](https://iso-9899.info/wiki/The_Standard) standard and doesn't introduce anything which would not be considered *standard C*. This is in contrast to the Arduino software framework, which introduces classes such as *serial* to process serial input.
* The value of programming the *ATmega328P* in *C* is that it is easier to understand the *C* concepts using an 8-bit processor as compared to programming in *C* on a personal computer.
* It also allows someone to learn how to program an embedded microcontroller in a less complex environment as compared to a 32-bit microcontroller such as the Raspberry Pi Pico.

In order to use this framework, you can either install the *GNU avr* tool chain appropriate for your computer (Linux, macOS, or Windows). Or you can use the tool chain installed by Arduino, the instructions are in the same location. The directions to do so are here: [Developing in C on the AVR ATmega328P](https://wellys.com/posts/courses_avr_c/).

For a robust debugging approach on Linux, you may add [Bloom](https://bloom.oscillate.io/) and *avr-gdb*. Bloom provides a GUI display of the microcontroller's registers and memory as well as the connection required from the chip to avr-gdb. [gdb](https://www.sourceware.org/gdb/) is a simple yet extremely powerful debugging tool. I find it easier to use than most IDE's such as Visual Studio, MPLAB IDE etc. More guidance at [Developing in C for the ATmega328: Setup Bloom and gdb for Hardware Debug](https://wellys.com/posts/avr_c_gdb_bloomsetup/).

## Steps to Use
1. Install toolchain. [Details here](https://www.wellys.com/posts/avr_c_setup/)
2. Obtain this repository, either via download using zip file or preferably, [use git and clone to your system](https://www.wellys.com/posts/avr_c_step5/).
3. Open the *AVR_C* folder and add an *env.make* file (*see below*) based on your board and system. **Be sure to set *toolchain* and *OS*, appropriate to the tool chain your are using and your operating system.**
4. Navigate to *examples/blink* in your CLI and run:
	* *make* to compile, link and create an executable file
	* *make flash* to upload executable file to your board.
5. Look at the other examples to better understand how to use the code and begin writing your own!
6. If you are running Linux and want to try hardware debugging, consider [using Bloom, avr-gdb and a debugger](https://www.wellys.com/posts/avr_c_gdb_bloomsetup/).


## Boards and Microcontrollers
This code has been tested extensively with the Arduino Uno and the [Microchip ATmega328PB Xplained Mini ](https://www.microchip.com/en-us/development-tool/ATMEGA328PB-XMINI). I prefer the latter board for development as it includes a hardware debugger on the same board, which works well with [Bloom](https://bloom.oscillate.io/) and it only costs $12! If looking to purchase a new board to work with this code, I recommend the Microchip board. 

If you have an existing Uno, it will work very well. If you wish to add hardware debugging, you will want to purchase a debugWIRE compatible device such as the [Microchip MPLAB Snap](https://www.microchip.com/en-us/development-tool/PG164100) or the [Atmel ICE](https://www.microchip.com/en-us/development-tool/ATATMEL-ICE).

Other Microchip AVR-compatible microcontrollers will more than likely work, I haven't the time to test them. If the processor is not a ATmega328P, it will be important to set the MCU and processor frequency (F_CPU) variables in the Makefile. For specific information as to how to setup your environment specific to your board and microcontroller, see the content for **Makefile** below.
## Arduino Framework  and standard C Replacement Routines
Much of the Standard C Library is provided by [AVR Libc](https://www.nongnu.org/avr-libc/). I recommend having a link to the online manual open while developing code. The code in this repository is the code required to program the Uno using similar routines as in the Arduino Framework.
### Arduino Framework Functions

**Each function used requires an #include in order to be used (example):**
```C
#include "functionname.h" /* format of include */

#include "analogRead.h" /* for example to use analogRead() */
#include "unolib.h" /* add this file for general definitions */
```
This keeps the code smaller than with a large file containing all of the functions available.

### Arduino Framework Functions
* **analogRead(pin)**: read one of the 6 Analog pins (A0-A5). Returns a 10-bit value in reference to AREF see [analogReference()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogreference/). In this case, it only DEFAULT value of VCC or 5V. To convert reading to voltage, multiply by 0.0048 (for a reference voltage of 5V).
* **analogWrite(pin, n)**: setup the Timer/Counters to provide a PWM signal. Keep in mind, PWM using the Timer/Counters, see this [AVR Datasheet Note: PWM](https://wellys.com/posts/avr_c_step2/) as to which pin, a Timer/Counters is assigned. The examples such as *button* (T/C 2) and *micros* (T/C 1) also use the same Timer/Counters, so the conflict might be an issue. 
	* pin = Arduino UNO Pin Number, must have a "\~" in its name (3, 5, 6, 9, 10, 11)
	* n = n/255 Duty Cycle, i.e; n=127, 127/255 \~= 50% duty cycle
	* Pin PWM Frequencies
		* UNO pin 3/PD3, 488.3Hz
		* UNO pin 5/PD5, 976.6Hz
		* UNO pin 6/PD6, 976.6Hz
		* UNO pin 9/PB1, 976.6Hz
		* UNO pin 10/PB2, 976.6Hz
		* UNO pin 11/PB3, 488.3Hz
* **digitalRead(pin)**: returns value (1 or 0) of Uno pin (pins 0-13 only). If using serial I/O (printf/puts/getchar) then Uno pins 0 and 1 are not usable. digitalRead() is not configured to use A0-A5.
* **digitalWrite(pin, level)**: set an UNO pin to HIGH, LOW or TOG (pins 0-13 only).  If using serial I/O (printf/puts/getchar) then Uno pins 0 and 1 are not usable. This version also adds TOG, which toggles the level. Much easier than checking the level and setting it to be the opposite level and requires less code. digitalWrite() is not configured to use A0-A5.
* **pinMode(pin, mode)**: define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin (pins 0-13 only). Is not configured to use A0-A5.
* **delay(ms)**: Blocking delay uses Standard C built-in \_delay_ms, however allows for a variable to be used as an argument. 
* **millis()**: Returns a long int containing the current millisecond tick count. Review the millis example to understand how to use it. millis() uses *sys_clock_2*, which is a system clock configured using Timer/Counter 2.  
### Standard C I/O functions adapted for the ATmega328P
Use these standard C I/O functions instead of the Arduino Serial class. See example *serialio* for an example implementation. Requires the following in the file:
```C
# in the include section at the top of the file
#include "uart.h"
#include <stdio.h>

# at the top of the main function, prior to using I/O functions
	init_serial();
```
* **getChar(char)**: same as C *getChar()* (non-interrupt at this time)
* **printf(string, variables)**: same as C *printf()*, limited functionality to be documented. There are two ways to add printf and those are documented in the Makefile in the examples. It is also helpful to review the [avr-libc printf](https://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html) documentation.
* **puts(string)**: same as C *puts()*

### Added functions beyond Arduino Framework
* **buttons[i]** - provides a debounced button response. Each button must attach to an Uno pin
	* Requires *sysclock_2()*, see *examples/button* as to how to implement
	* *buttons[i].uno* are the Uno pins attached to a button and like digitalRead, function will translate Uno pin to port/pin
	* *buttons[i].pressed* indicates if the button has been pressed (true or non-zero)
	* depending on the application, you might need to set *buttons[i].pressed* to zero, following a successful press, if you depend on a second press to change state. Otherwise, you'll have a race condition where one press is counted as two presses (its not a bounce, its a fast read in a state machine)

* **user-defined button RESET** - as debugWIRE uses the \~RESET pin for communication, it is valuable to define another pin to use as a RESET pin. It is performed using this [method](http://avr-libc.nongnu.org/user-manual/FAQ.html#faq_softreset). 
	 The ATmega328PB XPLAINED MINI board has an on-board user defined push button on PB7. The reset routine will debounce the button. To use the reset, the routine requires an include of *sysclock.h* and an *init_sysclock_2();*. Three examples already have *reset* enabled, **button**, **millis, and **analogRead**. Additional variables to set are in *unolib.h*:
	```C
	#define RESET_BUTTON PB7
	#define RESET_MASK  0b11000111
	```
	I recommend not changing the mask, unless you are experiencing significant debounce issues. The button pin needs to be expressed as pin on port B and with a pin number as shown.

* **Random number generation** - using Mersenne Twister, TinyMT32, 32-bit unsigned integers can be created.. There is are two test routines, *tinymt*, which demonstrates how to setup and use it as well as *rand_test*, which compares the execution time of *tinymt* to *random()*. It appears that rand() is 4 times faster than tinyMT, however, I haven't checked the "randomness" of the two routines.

### Multi-tasking
There are six examples of multi-tasking in the examples folder. Two are 3rd party code which I added for consideration as multitasking models. And the remaining four are a development, which I document in greater detail [here.](https://wellys.com/posts/avr_c_step6/)

In a nutshell:
* *multifunction* is the first iteration, simply a proof of concept that the *"single-line scheduler"* works.
* *multi_Ard* takes the previous code example, which is fast and simplifies it using Arduino-type calls (pinMode and digitialWrite) for easier integration
* *multi-array* moves away from a separate function framework to a common function using an array to multitask
* *multi_struct* uses a similar approach as the previous code, however uses a struct to provide fully overlapping multi-tasking

## Examples 
### analogRead: 
Demo file for using analogRead(), requires a pot to be setup with outerpins to GND and 5V. Then connect center pin to one of A0-A5, adjust pot to see value chance in a serial monitor.

### analogWrite: 
Demo file for using analogWrite(), requires a scope (Labrador used) to see the output of the PWM signal

### button: 
Demo file for using debounced buttons, requires a button attached to a Uno digital pin with INPUT_PULLUP. *buttons[i].pressed* provides a indication of the button pressed.

### blink: 
Minimal blink sketch. Intended as a minimal test program while working on code, it doesn't use the AVR_C Library.

### digitalRead: 
Uses loops to go through each digital pin (2-13) and print out level on pin. Uses INPUT_PULLUP, so pin needs to be grounded to show 0, otherwise it will be a 1. 

### durationTest:
An inline test of playing a melody using tone(). This version is easier to test and debug than melody. **See note on Interrupts below.**

### four states:
A four state finite state machine which uses 2 pushbuttons, 2 red LEDs and 1 blue LED to move through states and indicate state status. One push button is *UP*, which moves through the states on being pressed, and the other push button is *ENTER*, which enters the state and in this case, lights a blue LED with varying intensity. The LEDs indicate the state in a binary fashion.
### melody: 
Fundamentally, the same as the melody sketch on the Arduino website. The changes made are those required for standard C vs. the Arduino framework. **See note on Interrupts below.**
### micros:
Shows an example of using micros() to demonstrate how to measure time. Micros are a form of the system time-keeping mechanism *ticks*. A tick is 62.5us, which means 16 ticks = 1us. Calling micros will provide a number in microseconds, however, it will rollover every 4milliseconds, so it can't be used for measuring an event longer than 4 milliseconds without accounting for the rollover.
### millis:
Shows an example of using millis() to demonstrate the effectiveness of the delay command. Prints the time delta based on using a delay(1000).
### serialio:
Simple character I/O test using the UART. The USB cable is the only cable required. See note in main.c, as program won't work with specific combinations of a board and serial monitor. Adafruit Metro 328 and minicom for example.

## Serial Interface
[Simple Serial Communications with AVR libc](https://appelsiini.net/2011/simple-usart-with-avr-libc/) Works well, integrated into avr-gcc to enable using printf, puts, and getchar. Uses polling, which will blocking, works well to 250000 baud. 

The Makefile uses 250000 baud, it is fast and error-free. My recommended serial monitor is [CoolTerm](https://freeware.the-meiers.org/). Read [here](https://wellys.com/posts/serial_applications/) for more information.

The example `serialio_readline` provides a *readline* example to understand how to read a line from the serial console and break the line into tokens or words.

## Multitasking
There are four multitasking examples in the *examples* folder. Only one of them will be incorporated into the Library. The goal of each example is to explore the possible approaches for multitasking. 
* **multi_struct** Based on *oneline*, this version uses a struct to contain the details as to the tasks to be performed. This version will be ultimately integrated into the AVR_C Library. I will continue to evolve *multi_struct* as I have several specific projects which require a particular version of multitasking.
* **multi_Ard** Based on *oneline*, this version incorporates *digitalWrite()* from the AVR_C Library.
* **multi_array** Based on *multi_Ard*, this version incorporates *digitalWrite()* and uses an array of tasks to perform multitasking.
* **multifunction** Based on *oneline*, this is the original version to test the limits as to how well the concept worked.
* **oneline** [A Multitasking Kernal in One Line of code](https://www.embedded.com/a-multitasking-kernel-in-one-line-of-code-almost/) The simplest example of round robin multitasking. Only recommended as an simple illustration as to how to multitask using pointers to functions. Highest speed, smallest footprint 466 bytes, minimal scheduling.

### Edit the Library!
I encourage you to play around with the Library to better understand C and programming the Uno. **IF YOU DO CHANGE THE ROUTINES IN THE LIBRARY**, you will need to run *make LIB_clean* to clean the Library folder and force it to recompile all of the functions.

My approach to the compile/link/load cycle while working on the Library is the following chain of *make* executions:
```bash
make LIB_clean && make all_clean && make flash
```
This deletes all object files from both the Library and the current working folder then recompiles them with the last command. This approach is a bit overkill, however, it takes only a few additional seconds. The extra seconds are returned with knowing you aren't using out-dated code. Once you are finished with working on the Library code, *make flash* will be sufficient.

## Makefile and make
The examples make use of a great Makefile courtesy of Elliot William's in his book [Make: AVR Programming](https://www.oreilly.com/library/view/make-avr-programming/9781449356484/). I highly recommend the book and used it extensively to understand how to program the ATmega328P (Arduino UNO) from scratch.

[Makefile](https://github.com/hexagon5un/AVR-Programming/blob/ad2512ee6799e75e25e70043e8dcc8122cb4f5ab/setupProject/Makefile)

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
# command to clear out the Library object files *file.o*, sometimes required if changes to Library files aren't appearing to work, uses LIBDIR folder as the folder to clean
make LIB_clean
```

To [install the proper toolchain](https://wellys.com/posts/avr_c_setup/) required to compile the code.

### Makefile Notes
The *Makefile* uses two variables from the env.make file, `TOOLCHAIN = ` and `OS =`, which allows you to use either, a system-installed toolchain (default) or the toolchain installed by the legacy *Arduino (1.8.x) IDE*. 

In order to use the latter, perform the following steps in the env.make file:
1. Add *arduino* to the `TOOLCHAIN` variable as in `TOOLCHAIN = arduino`
2. Add either *mac* or *windows* to the `OS =` line to indicate the OS your PC is running

If either is missing, *make* will assume you are using the GNU tool chain.

```bash
ifeq ($(TOOLCHAIN),arduino)
    ifeq ($(OS),mac)
        BIN = /Applications/Arduino.app/Contents/Java/hardware/tools/avr/bin/
        AVRDUDECONF = -C /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/bootloaders/gemma/avrdude.conf
    endif
    ifeq ($(OS),windows)
        BIN = 'C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\'
        AVRDUDECONF = '-CC:\Program Files (x86)\Arduino\hardware\arduino\avr\bootloaders\gemma\avrdude.conf'
    endif
    ifeq ($(OS),raspberry)
        BIN = /usr/local/arduino/hardware/tools/avr/bin/
        AVRDUDECONF = -C /usr/local/arduino/hardware/arduino/avr/bootloaders/gemma/avrdude.conf
    endif

else
	BIN =
	AVRDUDECONF = 
endif
```
**The `BIN = ...` and `AVRDUDECONF = ...` lines must be indented with two `tab`s at the beginning of the line for make to accept the lines.**

There is only one Makefile and it sits at the root level of the folder, along side env.make. There are symbolic (soft) links inside of each example to this Makefile. This makes it easy to propagate changes to all examples simultaneously. It also means there is only one Makefile.

In order to account for multiple projects which use this library in different folder hierarchies, each local makefile has a variable `DEPTH` which is defined as the required relative nesting to reach the root folder.

For example, in *AVR_C*, the depth is two, therefore `DEPTH = ../../`, while in another project where there is one more level of folders, it is `DEPTH = ../../../`.

If you are getting make errors, stating it can't find the target, more than likely the `DEPTH` variable is incorrect.

### env.make
The method of changing parameters from local environmental variables such as *AVR_PORT* and *AVR_MCU* has changed. Instead of local enviromental variables, I have found it easier to maintain a top-level file called *env.make*, which contains all of the local customizable options. This file is added to the *make* process by an *include* at the top of file. It is **ignored** by git, so it must be created and updated, outside of the git process.

The file, *env.make* is **not tracked by git** and it looks like this: (*macOS SERIAL parameter)
```make
# Arduino UNO environmental variables
MCU = atmega328p
SERIAL = /dev/cu.usbmodem14101
F_CPU = 16000000UL
BAUD  = 250000UL
SOFT_RESET = 0
LIBDIR = $(DEPTH)Library
PROGRAMMER_TYPE = Arduino
PROGRAMMER_ARGS = -F -V -P $(SERIAL) -b 115200
TOOLCHAIN = arduino
OS = mac
```
As shown, this one is for the Arduino Uno board and on a Mac. For Make to work, you need to perform the following:
1. Copy the contents above and paste them into a file called *env.make*
2. The file needs to sit at the top level, the same level as this *README* and the programming folders *Library* and *examples*.
You will need to set the following:
* **SERIAL =** to the serial port you found using the Arduino IDE
* **TOOLCHAIN = arduino** delete the word 'arduino if you wish to use the locally installed GNU C tool chain'
* **OS = mac** replace 'mac' with 'windows' if on a Windows PC
```make
# Arduino UNO environmental variables
MCU = atmega328p
SERIAL = /dev/cu.usbmodem14101
F_CPU = 16000000UL
BAUD  = 250000UL
SOFT_RESET = 0
LIBDIR = $(DEPTH)Library
PROGRAMMER_TYPE = Arduino
PROGRAMMER_ARGS = -F -V -P $(SERIAL) -b 115200
TOOLCHAIN = arduino
OS = mac
```
I've found it best to include full sections per board, then comment/uncomment a section based on the board I'm using. A full version of the *env.make* file I'm using is below.

**Note: This repository has the new version of Makefiles which uses this file, so no other changes other than creating the proper *env.make* file are needed.**

The nice part about this change, is once the variables have been updated for your system, you no longer have to do special programmer types such as *make flash_snap* or *make flash_xplain*, as *make flash* will be automatically updated for your specific programmer. (**Provided you give it the right parameters.**)

Here is an env.make with multiple sections, one for each board to be used. Notice that only one section is active at a time, the non-used sections have been commented out.

**Full version of the env.make file I am using:**
```make
# Environmental variables for specific boards
# Uncomment entire block less top line of block
# After switching boards, Library must be re-compiled
# Use "make LIB_clean && make all_clean && make flash" for a complete re-compile
# Baud rates to 250000 have been tested and work

# Example Serial Ports on Mac
# /dev/cu.usbserial-01D5BFFC
# /dev/cu.usbmodem5101
# /dev/cu.usbmodem3301
# /dev/cu.usbserial-AB0JQEUX
# /dev/cu.usbmodem14101

# Example Serial Ports on Linux
# /dev/ttyACM0

# Example Serial Ports on Windows
# COM3
# COM4
# COM9

# Using Arduino tools vs. GCC native
# For Arduino tool chain
# TOOLCHAIN [ arduino ]
# OS: [mac | windows | raspberry ]
# For GCC native, both TOOLCHAIN and OS need to be blank

# Arduino UNO et al using Optiboot (standard Arduino IDE approach)
MCU = atmega328p
SERIAL = /dev/cu.usbserial-AR0JYGOB
F_CPU = 16000000UL
BAUD  = 250000UL
SOFT_RESET = 0
LIBDIR = $(DEPTH)Library
PROGRAMMER_TYPE = arduino
PROGRAMMER_ARGS = -F -V -P $(SERIAL) -b 115200
TOOLCHAIN =
OS =
TC3_RESET = 0


# Arduino UNO and compatible boards using Atmel-ICE Debugger in atmelice_isp mode
# MCU = atmega328p
# SERIAL = /dev/cu.usbserial-01D5BFFC
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 0
# LIBDIR = $(DEPTH)Library
# PROGRAMMER_TYPE = atmelice_isp
# PROGRAMMER_ARGS = -F -V -P usb -b 115200
# TOOLCHAIN = 
# OS = mac

# Arduino UNO and compatible boards using Atmel Dragon
# MCU = atmega328p
# SERIAL = /dev/cu.usbserial-01D5BFFC
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 0
# LIBDIR = $(DEPTH)Library
# PROGRAMMER_TYPE = dragon
# PROGRAMMER_ARGS =   -c dragon_isp -P usb
# TOOLCHAIN = 
# OS = mac

# Arduino UNO and compatible boards using Atmel SNAP in ISP mode
# MCU = atmega328p
# SERIAL = /dev/cu.usbserial-01D5BFFC
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 0
# LIBDIR = $(DEPTH)Library
# PROGRAMMER_TYPE = snap_isp
# PROGRAMMER_ARGS = -P usb
# TOOLCHAIN = 
# OS = mac

# Microchip 328PB Xplained Mini board
# MCU = atmega328pb
# SERIAL = /dev/cu.usbmodem3102
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 1
# LIBDIR = $(DEPTH)Library
# PROGRAMMER_TYPE = xplainedmini
# PROGRAMMER_ARGS =
# TOOLCHAIN = 
# OS = mac
# TC3_RESET = 0

# Microchip Curiousity Nano AVR64DD32
# avrdude -p avr64dd32 -c pkobn_updi -P usb -t
# MCU = avr64dd32
# SERIAL = /dev/cu.usbmodem3102
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 0
# LIBDIR = $(DEPTH)Library
# PROGRAMMER_TYPE = pkobn_updi
# PROGRAMMER_ARGS =
# TOOLCHAIN = 
# OS = mac
# TC3_RESET = 0
```

## Static Testing
I used [*cppcheck*](http://cppcheck.net) to perform a static analysis of the code. It was extremely helpful in pointing out a few buffer issues, I had. That said, there were a few false positives or some issues, which I knew existed and didn't wish to fix. Here is the suppressions-list I used:
```
// info issues which don't need to get resolved
missingIncludeSystem
missingInclude

// example purposely uses a false known condition to execute
knownConditionTrueFalse:examples/pointers/main.c

// example purposely uses an unbounded scanf() to demo problem
invalidscanf:examples/serialio_string/main.c

// functions which are included if a specific board is used
unusedFunction:Library/sysclock.c
unusedFunction:Library/unolib.c
unusedFunction:examples/serialio_wrapprint/main.c

// haven't determined if a problem, however not a concern
unusedFunction:Library/tinymt32.c
```

To perform static testing, run `make static` at the root level and the output from cppcheck will appear in cppcheck.txt. If you want to see all issues, none suppressed, then remove '--suppressions-list=$(DEPTH)suppressions.txt' from the `make static` line in the Makefile (line 89)
## Sources
I also write about C, MicroPython and Forth programming on microcontrollers at [Wellys](https://wellys.com).

Other sources of information which were helpful:
* [AVR Libc](https://www.nongnu.org/avr-libc/)
* [AVR Freaks Community](https://www.avrfreaks.net/)
* [Arduino in C | Freedom Embedded](https://balau82.wordpress.com/arduino-in-c/)
* [Programming Arduino in "Pure C"](http://audiodiwhy.blogspot.com/2019/01/programming-arduino-in-pure-c-now-were.html)
* [EMBEDDS: AVR Tutorials](https://embedds.com/avr-tutorials/)
* [CCRMA: AVR](https://ccrma.stanford.edu/wiki/AVR#AVR_Microcontrollers)
* [Efundies Electronics and Programming Guides: AVR](https://efundies.com/avr/)
