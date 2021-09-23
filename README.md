# Programming the Arduino Uno in Pure C
## Arduino Framework Replacement Routines
### pinMode(pin, mode): define INPUT, OUTPUT, INPUT_PULLUP for an UNO pin
### digitalWrite(pin, level): set an UNO pin to HIGH or LOW
### analogWrite(pin, n): setup the Timer/Counters to provide a PWM signal
Parameters:
* pin = Arduino UNO Pin Number, must have a "\~" in its name (3, 5, 6, 9, 10, 11)
* n = n/255 Duty Cycle, i.e; n=127, 127/255 = 49.8% duty cycle
### Pin PWM Frequencies
UNO pin 3/PD3, 488.3Hz
UNO pin 5/PD5, 976.6Hz
UNO pin 6/PD6, 976.6Hz
UNO pin 9/PB1, 976.6Hz
UNO pin 10/PB2, 976.6Hz
UNO pin 11/PB3, 488.3Hz

## Includes required for commands
### #include "avr_UNO.h" - General definitions
### #include "analogWrite.h" 
### #include "pinMode.h"
### #include "digitalWrite.h"

## Instructions for tool chain installation
### KDE Ubuntu
```
sudo pkcon install gcc-avr binutils-avr gdb-avr avr-libc avrdude
```
### Ubuntu
```
sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude
```
## Instructions for using Dragon as a Debugger
Commands:
```bash
# Connect Dragon to Uno and initiate connection to debugger
avarice -g -w -d -P atmega328p :3333
# begin gdb debugger
avr-gdb led.elf
# compile/link/load using Dragon
make flash-dragon
# Set DWEN bits using Dragon
avrdude -c dragon -p atmega328p -c dragon_isp -P usb -U hfuse:w:0x9A:m
# Clear DWEN bits using Dragon
avrdude -c dragon -p atmega328p -c dragon_isp -P usb -U hfuse:w:0xDA:m
```

## Program and debug Arduino Uno
(Using avrdude, Dragon and DebugWire)
## Process
### 1. Cut Reset Enable on Uno board
The Uno board contains a trace that can be cut to disable the auto-reset. The pads on either side of the trace can be soldered together to re-enable it. It's labeled "RESET-EN". You may also be able to disable the auto-reset by connecting a 110 ohm resistor from 5V to the reset line. It is immediately to the right of the 16MHz crystal, looking down on the board, digital pins on top.

## Commands to use DWEN
With DWEN set (hfuse:6 is 0) DebugWire is enable using Dragon. To use run Avarice and gdb and Reset Enable must be cut on Arduino Uno. 

Program board per instructions below to have a working UNO
```bash
# Per: http://www.martyncurrey.com/arduino-atmega-328p-fuse-settings/
# Reset must be cut to allow DWEN to work (get URL)
DWEN is bit 6 of the High Fuse (hfuse)
# this changes the High Fuse from DA (1 in bit 6) to 9A (0 in bit 6)
avrdude -c dragon -p atmega328p -c dragon_isp -P usb -U hfuse:w:0x9A:m 

avarice -g -w -d -P atmega328p :3333

avr-gdb led.elf

```

## Instructions for reflashing bootloader onto Atmega328P chip
```
# 0. Connect the Dragon to the Uno. ICSP cable, pin 1 to pin 1, USB to Dragon, USB to Uno
# 1. Test the connection
avrdude -p m328p -P usb  -c dragon_isp -t
part
quit
# 2. Set fuses and lock bits to enable re-loading of boot loader
avrdude -p atmega328p  -c dragon_isp -P usb -e -u -U lock:w:0x3f:m -U efuse:w:0x05:m -U hfuse:w:0xDE:m -U lfuse:w:0xFF:m
# 3. Copy hex file to desktop
cp /Applications/Arduino.app/Contents/Java/hardware/arduino/avr/bootloaders/optiboot/optiboot_atmega328.hex ~/Desktop/
# 4. Burn Arduino bootloader & set lock bits to lockbootloader section
avrdude -p atmega328p  -c dragon_isp -P usb -U flash:w:./optiboot_atmega328.hex -U lock:w:0x0f:m
```

## Instructions for simple compile/link/load on Arduino Uno
```
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o led.o led.c
avr-gcc -mmcu=atmega328p led.o -o led
avr-objcopy -O ihex -R .eeprom led led.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:led.hex
```

## Instructions for Using Makefile
Current version uses Makefile from Maker Media book Make: AVR Programming.
https://github.com/hexagon5un/AVR-Programming
Be sure to make/confirm changes to makefile regarding setup, programmer etc
```
make flash
```

## Sources
* [Arduino in C | Freedom Embedded](https://balau82.wordpress.com/arduino-in-c/)
* https://www.xanthium.in/atmega328p-10bit-sar-adc-usart-serial-transmit-to-pc-data-acquisition-tutorial
* https://www.arduino.cc/en/Tutorial/BuiltInExamples/ArduinoISP
* https://github.com/rsbohn/ArduinoISP
* https://stackoverflow.com/questions/1588788/wrapping-c-class-api-for-c-consumption
* https://github.com/balau/arduino_c
* https://johanneshoff.com/arduino-command-line.html
* https://avogadrosnumber.wordpress.com/2017/09/02/blink-and-led-in-c-on-the-arduino-uno/
* http://audiodiwhy.blogspot.com/2019/01/programming-arduino-in-pure-c-now-were.html
* https://www.tderflinger.com/en/arduino-blinking-led-pure-c
* https://github.com/sagarsp/arduino-blink-c
