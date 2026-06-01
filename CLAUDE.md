# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

AVR_C is a framework for programming the Arduino Uno (ATmega328P/PB) in standard C (C99), providing Arduino-like functions while using standard C instead of the Arduino framework. This allows students and developers to learn embedded C programming in a familiar context.

The framework mimics Arduino functions (pinMode, digitalWrite, analogRead, etc.) but implements them in standard C using avr-gcc and avr-libc.

## Build System

### Environment Configuration

The build system uses a single `Makefile` at the root level with environment-specific settings in `env.make`. Each example directory contains a symbolic link to the root Makefile.

**Initial Setup:**
```bash
# Create env.make from template
cp env.def env.make

# Edit env.make to set your serial port
nano env.make  # Update SERIAL = /dev/ttyACM0 (or /dev/ttyUSB0, COM3, etc.)
```

**Key env.make Variables:**
- `MCU` - Microcontroller type (atmega328p or atmega328pb)
- `SERIAL` - Serial port for programming (/dev/ttyACM0, /dev/ttyUSB0, COM3, etc.)
- `F_CPU` - Clock frequency (16000000UL for Uno)
- `USB_BAUD` - Serial baud rate (250000UL recommended)
- `LIBRARY` - Set to "YES" to use AVR_C library, leave blank for minimal code size
- `FLOAT` - Set to "YES" to include floating point printf support, leave blank otherwise
- `WRAP` - Set to "YES" to enable the `__wrap_printf` timestamp wrapper (adds `-Wl,--wrap=printf`). Required by any example that wraps `printf` (e.g. `serialio_wrapprint`); link error `undefined reference to '__wrap_printf'` means this is unset.
- `SOFT_BAUD` - Baud rate for the software serial port (soft_serial), max 28800UL
- `PROGRAMMER_TYPE` - arduino, atmelice_isp, snap_isp, xplainedmini, dragon, pkobn_updi, etc.
- `PROGRAMMER_ARGS` - Programmer-specific arguments
- `TOOLCHAIN` / `OS` - Set both to `arduino` / `mac|windows|raspberry` to use the Arduino-bundled avr toolchain; leave both blank for a native GCC install (avr-gcc on PATH)
- `TC3_RESET` - ATmega328PB only: use Timer/Counter 3 for the 1ms clock

After changing the board/MCU in `env.make`, the Library must be recompiled — use `make complete` (see below).

### Make Commands

Common commands (run from example directories):

```bash
make              # Build main.elf only (compile + link, equivalent to Arduino verify)
make compile      # Build main.hex
make flash        # Compile, show size, and upload to board (Arduino upload)
make verbose      # Flash with detailed (avrdude -v -v) programming output
make clean        # Delete this example's compiled files
make env          # Print all active env.make variables + source file list
make size         # Show program size (avr-objdump -Pmem-usage)
make help         # List the documented targets
make static       # Run cppcheck static analysis -> cppcheck.txt
make disassemble  # (alias: disasm) Emit main.lst, an annotated disassembly listing

# Library development — there is NO `make LIB_clean` target
make all_clean    # Delete all .o files in current dir AND Library/ (forces Library rebuild)
make complete     # = all_clean + verbose flash; the full rebuild after editing Library code
make clean_examples  # Run `make clean` in every examples/*/ directory (run from root or any example)
```

> Note: `make all_clean` is what clears stale `Library/*.o`. Use `make complete` (or `make all_clean && make flash`) after modifying any file under `Library/`, since the default build only rebuilds object files whose `.c`/`.h` changed.

### Project Structure

```
AVR_C/
├── Makefile           # Main makefile (symlinked in examples)
├── env.def            # Template environment configuration
├── env.make           # Local environment config (not tracked by git)
├── Library/           # AVR_C library functions (all *.c compiled when LIBRARY=YES)
│   ├── analogRead/Write, digitalRead/Write, pinMode, map  # Arduino-compatible I/O
│   ├── uart.c/h       # Hardware USART serial (init_serial, printf/puts/getchar backing)
│   ├── soft_serial.c/h + serial_asm.S/.h  # Bit-banged software serial (TX=PD3, RX=PD2);
│   │                                       #   timing-critical primitives are in AVR asm
│   ├── readLine.c/h   # Line-buffered serial input
│   ├── servo.c/h, tone.c/h        # Servo PWM and tone generation
│   ├── button.c/h     # Debounced buttons (needs sysclock_2)
│   ├── sysclock.c/h   # Timekeeping (millis, micros)
│   ├── tinymt32.c/h   # Mersenne Twister (TinyMT32) RNG
│   ├── xArm.c/h       # xArm robotics arm command interface (see docs/xArm.md)
│   └── unolib.h       # Common definitions and macros
└── examples/          # Example programs
    ├── blink/         # Each example has:
    │   ├── makefile   #   - Local makefile (sets DEPTH)
    │   └── main.c     #   - Main source code
    └── [others]/
```

### Local Makefiles in Examples

Each example has a local `makefile` that defines `DEPTH` (relative path to root):

```make
DEPTH = ../../
include $(DEPTH)Makefile
```

The `DEPTH` variable accounts for folder nesting. If adding examples at different levels, adjust accordingly:
- Examples at `examples/foo/` → `DEPTH = ../../`
- Examples at `examples/subdir/foo/` → `DEPTH = ../../../`

## AVR_C Library Functions

### Arduino-Compatible Functions

All functions require corresponding header includes:

```c
#include "unolib.h"      // General definitions (LED_BUILTIN, HIGH, LOW, TOG)
#include "pinMode.h"     // pinMode()
#include "digitalWrite.h" // digitalWrite()
#include "digitalRead.h" // digitalRead()
#include "analogRead.h"  // analogRead()
#include "analogWrite.h" // analogWrite() - PWM
#include "delay.h"       // delay()
#include "sysclock.h"    // millis(), micros()
```

**Digital I/O:**
- `pinMode(pin, mode)` - Set pin mode: INPUT, OUTPUT, INPUT_PULLUP (pins 0-13)
- `digitalWrite(pin, level)` - Set pin: HIGH, LOW, or TOG (toggle)
- `digitalRead(pin)` - Read digital pin (returns 1 or 0)

**Analog I/O:**
- `analogRead(pin)` - Read analog pins A0-A5 (returns 10-bit value 0-1023)
- `analogWrite(pin, n)` - PWM output on pins 3, 5, 6, 9, 10, 11 (n = 0-255)

**Timing:**
- `delay(ms)` - Blocking delay in milliseconds
- `millis()` - Returns milliseconds since startup (requires sysclock_2)
- `micros()` - Returns microseconds (uses ticks, 16 ticks = 1μs, rolls over every 4ms)

**Serial I/O:**
```c
#include "uart.h"
#include <stdio.h>

// In main(), before using serial functions:
init_serial();

// Then use standard C I/O:
printf("text");        // Formatted output
puts("string");        // String output
getchar();            // Character input
```

**Buttons:**
```c
#include "button.h"
#include "sysclock.h"

// Provides debounced button handling
buttons[i].uno      // Uno pin number
buttons[i].pressed  // True if button pressed
```

### Special Features

**Code Size Optimization:**

Set in `env.make`:
- `LIBRARY = ` (blank) - Don't use AVR_C library (minimal size, ~188 bytes for blink)
- `LIBRARY = YES` - Use AVR_C library (~1356 bytes for blink)
- `FLOAT = ` (blank) - Exclude floating point printf
- `FLOAT = YES` - Include floating point printf (adds ~3KB)

**Timer/Counter Usage:**
- PWM (analogWrite) uses Timer/Counter 0 and 2
- millis() uses Timer/Counter 2 (sys_clock_2)
- micros() uses Timer/Counter 1
- Watch for conflicts when using multiple features

**User-Defined Reset Button:**
Available on ATmega328PB Xplained Mini (PB7). Set in `env.make`:
- `SOFT_RESET = 1` - Enable software reset button
- `TC3_RESET = 1` - Use Timer/Counter 3 for 1ms clock (ATmega328PB only)

## Development Workflow

### Creating New Examples

1. Create new directory in `examples/`
2. Copy `makefile` from another example
3. Verify/adjust `DEPTH` variable in local makefile
4. Create `main.c` with your code
5. Include necessary headers from Library
6. Run `make flash` to build and upload

### Modifying Library Functions

When editing Library code:

```bash
cd examples/your_example
make complete          # = all_clean + verbose flash
# or, to rebuild without flashing:
make all_clean && make
```

`make all_clean` removes `Library/*.o` so your changes are picked up; the default incremental build will not otherwise re-link stale Library objects reliably.

### Hardware Debugging

On Linux with ATmega328PB Xplained Mini or debugWIRE-compatible programmer:
- Use [Bloom](https://bloom.oscillate.io/) for hardware debugging
- Provides GUI register/memory view and gdb connection
- The RESET pin is used for debugWIRE, hence the software reset button feature

## Common Patterns

### Basic Program Structure

```c
#include "unolib.h"
#include "pinMode.h"
#include "digitalWrite.h"
#include "delay.h"

int main(void)
{
    pinMode(LED_BUILTIN, OUTPUT);

    while(1)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        delay(1000);
    }
    return 0;
}
```

### Using Serial I/O

```c
#include "uart.h"
#include <stdio.h>

int main(void)
{
    init_serial();

    printf("Hello World\n");
    puts("Another line");

    char c = getchar();

    while(1) { }
    return 0;
}
```

### Using Timekeeping

```c
#include "sysclock.h"

int main(void)
{
    init_sysclock_2();  // Initialize millis() timer

    unsigned long start = millis();

    while(1)
    {
        if ((millis() - start) > 1000)
        {
            // Do something every 1000ms
            start = millis();
        }
    }
    return 0;
}
```

## Important Notes

- The Makefile uses `avr-objdump -Pmem-usage` instead of deprecated `avr-size -C`
- Serial baud rate of 250000 is recommended as fastest reliable setting
- Use `TOG` (toggle) in digitalWrite() instead of reading then inverting state
- If using serial I/O, pins 0 and 1 are unavailable for other uses
- Digital functions (pinMode, digitalWrite, digitalRead) work on pins 0-13 only, not A0-A5
- The framework targets C99 standard, not C++ or Arduino-specific C++ extensions
- When LIBRARY=YES, all Library `.c` files are compiled; include only needed `.h` files
- The default `CFLAGS` build is a **debug** build (`-Og -ggdb`) with `-Wall -Wundef -Werror` — warnings fail the build. Size-optimized flags (`-Os`) are present but commented out in the Makefile.
- `SOURCES` is `$(wildcard *.c $(LIBDIR)/*.c)` — only `.c` files are auto-compiled. Assembly (`.S`, e.g. `Library/serial_asm.S`) is **not** picked up automatically; it must be added explicitly to the build to be linked.

## Editor / Code Intelligence (`.clangd`)

`.clangd` at the repo root configures clangd for the AVR examples. It pins avr-gcc as the compiler and hardcodes two macOS Homebrew paths that must be updated after `brew upgrade avr-gcc@9`:
- `Compiler: /opt/homebrew/bin/avr-gcc`
- the `-isystem /opt/homebrew/Cellar/avr-gcc@9/9.5.0/avr/include` AVR header path

It forces `-xc` (so standalone `.h` files aren't misparsed as Objective-C) and disables clangd's include-cleaner diagnostics (which misfire on headers included for side effects).
