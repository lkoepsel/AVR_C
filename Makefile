##########------------------------------------------------------##########
##########  System-specific Details                             ##########
########## 	are contained in root-level file: env.make          ##########
########## 	edit to change local/board/project parameters       ##########
##########------------------------------------------------------##########
include $(DEPTH)env.make
##########------------------------------------------------------##########
##########                  Program Locations                   ##########
##########     Be sure to set TOOLCHAIN and OS in env.make      ##########
##########------------------------------------------------------##########

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

CC = $(BIN)avr-gcc
OBJCOPY = $(BIN)avr-objcopy
OBJDUMP = $(BIN)avr-objdump
AVRSIZE = $(BIN)avr-size
AVRDUDE = $(BIN)avrdude

##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             We want a .hex file                      ##########
##########        Compile source files into .elf                ##########
##########        Convert .elf file into .hex                   ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########

## The name of your project (without the .c)
TARGET = main
## Or name it automatically after the enclosing directory
# TARGET = $(lastword $(subst /, ,$(CURDIR)))

# Object files: will find all .c/.h files in current directory
#  and in LIBDIR.  If you have any other (sub-)directories with code,
#  you can add them in to SOURCES below in the wildcard statement.

ifeq ($(LIBRARY),no_lib)
	SOURCES=$(wildcard *.c )
	CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD)  \
	-DSOFT_RESET=$(SOFT_RESET) -DTC3_RESET=$(TC3_RESET)

else
    SOURCES=$(wildcard *.c $(LIBDIR)/*.c)
    CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I.  -I$(LIBDIR) \
	-DSOFT_RESET=$(SOFT_RESET) -DTC3_RESET=$(TC3_RESET)
endif

# See Note re: CPPFLAGS if using/not using LIBDIR, pick only one LIB or NO_LIB
# LIB - Uncomment if the AVR_C Library is required (default), also 
# uncomment LIB below in CPPFLAGS (and comment NO_LIB)
# SOURCES=$(wildcard *.c $(LIBDIR)/*.c)

# NO_LIB - Uncomment if you wish the smallest code size and DON'T
# require AVR_C Library (and comment LIB)
# SOURCES=$(wildcard *.c )

OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(SOURCES:.c=.h)

## Compilation options, type man avr-gcc if you're curious. 

# use below to setup gdb and debugging
CFLAGS = -Og -ggdb -std=gnu99 -Wall -Wundef -Werror
# Use below to optimize size
# CFLAGS = -Os -g -std=gnu99 -Wall
## Use short (8-bit) data types 
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
## Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections
# if attempting to use %S format specification (strings in progmem), uncomment next line
CFLAGS += -Wno-format
LDFLAGS = -Wl,-Map,$(TARGET).map 
## Optional, but often ends up with smaller code
LDFLAGS += -Wl,--gc-sections 
# Uncomment line below to add timestamp wrapper to printf() OR
# Comment line below, if  undefined reference to `__wrap_printf'
# LDFLAGS += -Wl,--wrap=printf
## Relax shrinks code even more, but makes disassembly messy
## LDFLAGS += -Wl,--relax
## LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm  ## for floating-point printf
## LDFLAGS += -Wl,-u,vfprintf -lprintf_min      ## for smaller printf
TARGET_ARCH = -mmcu=$(MCU)

## Explicit pattern rules:
##  To make .o files from .c files 
%.o: %.c $(HEADERS) Makefile
	 $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ 

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

## These targets don't have files named after them
.PHONY: all disassemble disasm eeprom size clean squeaky_clean flash fuses


complete: all_clean verbose

compile: $(TARGET).hex 

static: 
	cppcheck --std=c99 --platform=avr8 --enable=all --suppressions-list=$(DEPTH)suppressions.txt . 2> cppcheck.txt

env:
	@echo "MCU:"  $(MCU)
	@echo "SERIAL:"  $(SERIAL)
	@echo "F_CPU:" $(F_CPU)
	@echo "BAUD:"  $(BAUD)
	@echo "SOFT_RESET:"  $(SOFT_RESET)
	@echo "LIB_DIR:"  $(LIBDIR)
	@echo "LIBRARY:"  $(LIBRARY)
	@echo "PROGRAMMER_TYPE:"  $(PROGRAMMER_TYPE)
	@echo "PROGRAMMER_ARGS:"  $(PROGRAMMER_ARGS)
	@echo "TOOLCHAIN:"  $(TOOLCHAIN)
	@echo "OS:"  $(OS)
	@echo "BIN:"  $(BIN)
	@echo "TC3_RESET:"  $(TC3_RESET)
	@echo
	@echo "Source files:"   $(SOURCES)
	@echo	

help:
	@echo "make compile - compile only (Arduino verify)"
	@echo "make flash - show program size and flash to board (Arduino upload)"
	@echo "make clean - delete all non-source files in folder"
	@echo "make complete - delete all .o files in folder & Library then verbose flash, for complete rebuild/upload"
	@echo "make verbose - make flash with more programming information for debugging upload"
	@echo "make env - print active env.make variables"
	@echo "make help - print this message"

# Optionally create listing file from .elf
# This creates approximate assembly-language equivalent of your code.
# Useful for debugging time-sensitive bits, 
# or making sure the compiler does what you want.
disassemble: $(TARGET).lst

disasm: disassemble

# Optionally show how big the resulting program is 
size:  $(TARGET).elf
# 	$(AVRSIZE) -G --mcu=$(MCU) $(TARGET).elf
	$(OBJDUMP) -Pmem-usage $(TARGET).elf
clean:
	rm -f $(TARGET).elf $(TARGET).hex $(TARGET).obj \
	$(TARGET).o $(TARGET).d $(TARGET).eep $(TARGET).lst \
	$(TARGET).lss $(TARGET).sym $(TARGET).map $(TARGET)~ \
	$(TARGET).eeprom cppcheck.txt

all_clean:
	rm -f *.elf *.hex *.obj *.o *.d *.eep *.lst *.lss *.sym *.map *~ *.eeprom core $(LIBDIR)/*.o

##########------------------------------------------------------##########
##########              Programmer-specific details             ##########
##########           Flashing code to AVR using avrdude         ##########
##########------------------------------------------------------##########

flash: $(TARGET).hex $(TARGET).lst size
	@echo "use make verbose to see complete programming information"
	$(AVRDUDE) -q -q $(AVRDUDECONF) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

verbose: $(TARGET).hex $(TARGET).lst size
	$(AVRDUDE) -v -v $(AVRDUDECONF) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

## An alias
program: flash

flash_eeprom: $(TARGET).eeprom 
	$(AVRDUDE) $(AVRDUDECONF) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U eeprom:w:$<

avrdude_terminal:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nt

##########------------------------------------------------------##########
##########       Fuse settings and suitable defaults            ##########
##########------------------------------------------------------##########

## Mega 48, 88, 168, 328 default values
LFUSE = 0x62
HFUSE = 0xdf
EFUSE = 0x00

## Generic 
FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 

fuses: 
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) \
	           $(PROGRAMMER_ARGS) $(FUSE_STRING)
show_fuses:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nv	

## Called with no extra definitions, sets to defaults
set_default_fuses:  FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m 
set_default_fuses:  fuses

## Set the fuse byte for full-speed mode
## Note: can also be set in firmware for modern chips
set_fast_fuse: LFUSE = 0xE2
set_fast_fuse: FUSE_STRING = -U lfuse:w:$(LFUSE):m 
set_fast_fuse: fuses

## Set the EESAVE fuse byte to preserve EEPROM across flashes
set_eeprom_save_fuse: HFUSE = 0xD7
set_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
set_eeprom_save_fuse: fuses

## Clear the EESAVE fuse byte
clear_eeprom_save_fuse: FUSE_STRING = -U hfuse:w:$(HFUSE):m
clear_eeprom_save_fuse: fuses
