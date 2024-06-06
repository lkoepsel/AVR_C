# env.make required for *make*

```bash
cd AVR_C
nano env.make
```

Copy and paste in to the root level of AVR_C

## env.make
```make
# Environmental variables for specific boards
# See https://wellys.com/posts/avr_c_make_part2/ for more information
# Uncomment entire block less top line of block
# After switching boards, Library MUST BE RE-COMPILED
# Use "make LIB_clean && make all_clean && make flash" for a complete re-compile

# Baud rates to 250000 have been tested and work on Uno R3
# Baud rates above 230000 might not work on some ports or serial software
# TC3_RESET is only applicable to ATmega328PB, set to 0 for ATmega328P

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

# To reduce code size dramatically by not using AVR_C library, 
# set LIBRARY = no_lib, see examples/blink_avr
# All functions must be in avr-libc (standard library), main.c or files in folder
# otherwise, leave blank

# Arduino UNO et al using Optiboot (standard Arduino IDE approach)
MCU = atmega328p
SERIAL = /dev/ttyACM0
F_CPU = 16000000UL
BAUD  = 250000UL
SOFT_RESET = 0
LIBDIR = $(DEPTH)Library
LIBRARY = 
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
# LIBRARY =
# PROGRAMMER_TYPE = atmelice_isp
# PROGRAMMER_ARGS = -F -V -P usb -b 115200
# TOOLCHAIN = 
# OS = mac
# TC3_RESET = 0

# Arduino UNO and compatible boards using Atmel Dragon
# MCU = atmega328p
# SERIAL = /dev/cu.usbserial-01D5BFFC
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 0
# LIBDIR = $(DEPTH)Library
# LIBRARY =
# PROGRAMMER_TYPE = dragon
# PROGRAMMER_ARGS =   -c dragon_isp -P usb
# TOOLCHAIN = 
# OS = mac
# TC3_RESET = 0

# Arduino UNO and compatible boards using Atmel SNAP in ISP mode
# MCU = atmega328p
# SERIAL = /dev/tty.usbmodem4101
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 0
# LIBDIR = $(DEPTH)Library
# LIBRARY =
# PROGRAMMER_TYPE = snap_isp
# PROGRAMMER_ARGS = -P usb
# TOOLCHAIN = 
# OS = mac
# TC3_RESET = 0

# Microchip 328PB Xplained Mini board
# MCU = atmega328pb
# SERIAL = /dev/tty.usbmodem4101
# F_CPU = 16000000UL
# BAUD  = 250000UL
# SOFT_RESET = 1
# LIBDIR = $(DEPTH)Library
# LIBRARY =
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
# LIBRARY =
# PROGRAMMER_TYPE = pkobn_updi
# PROGRAMMER_ARGS =
# TOOLCHAIN = 
# OS = mac
# TC3_RESET = 0
```
*CTRL-s (save) then CTRL-x (exit)*
