; =============================================================
; serial  –  serial program and library
; Target : ATmega328P
; Toolchain: avr-as / avr-ld  (GNU Binutils for AVR)
; =============================================================

; Dependencies — included here so this module assembles standalone
; (C examples build serial.S on its own). Both are include-guarded /
; idempotent, so it's safe when an asm main.S already included them.
#include <avr/io.h>
#include "registers.S"

; ====================================================================
;  TEXT SECTION  (executable code lives here)
; ====================================================================
.section .text

; ---------- Registers and Values ----------------
; r18                           ; temp register - temp_r18
; r20                           ; temp register - bit_ctr
; r24                           ; char register - char_reg

; Bit timing is derived at assemble time from the clock and baud rate the
; Makefile passes as -DSOFT_F_CPU / -DSOFT_BAUD_HZ (UL stripped so the
; assembler can do the arithmetic). Change SOFT_BAUD in env.make and these
; constants recompute automatically; the defaults let the file assemble
; standalone. delay_ticks N == 3N cycles and each bit adds ~8 cycles of loop
; overhead, hence the -8.
#ifndef SOFT_F_CPU
#define SOFT_F_CPU   16000000
#endif
#ifndef SOFT_BAUD_HZ
#define SOFT_BAUD_HZ 38400
#endif
#define BIT_CYCLES   (SOFT_F_CPU / SOFT_BAUD_HZ)
#define period       ((BIT_CYCLES - 8) / 3)
#define half_period  (period / 2)

; delay_ticks loads `period` with ldi (8-bit immediate), so 1 <= period <= 255.
; That bounds the usable baud range (~20.8 kbaud min @ 16 MHz). Fail loudly.
.if (period > 255)
    .error "soft_serial: SOFT_BAUD too low - period exceeds 255 delay ticks"
.endif
.if (period < 1)
    .error "soft_serial: SOFT_BAUD too high - period under 1 delay tick"
.endif

; ====================================================================
;  Subroutines SECTION
; ====================================================================

;initialize serial port, must be called before using char_read and char_write
.global init_soft_serial
init_soft_serial:

;   Set TX pin as output, set RX pin as input pullup
    sbi     IO_DDR, SOFT_TX_PIN
    cbi     IO_DDR, SOFT_RX_PIN
    sbi     IO_PORT, SOFT_RX_PIN

    ; set TX high to start, start_bit is low
    sbi     IO_PORT, SOFT_TX_PIN
    ret
; --------------------------------------------------------------------

; write a char (passed in r24, per AVR-GCC ABI) to the serial port
.global soft_char_write
soft_char_write:

    ; Start bit
    cbi     IO_PORT, SOFT_TX_PIN
    delay_ticks period

    ;  8 data bits and preserve char
    ldi     bit_ctr, 8
    mov     temp_r18, char_reg

write_bit:
    ror     temp_r18
    brcs    write_one
    cbi     IO_PORT, SOFT_TX_PIN
    rjmp     next_write

write_one:
    sbi     IO_PORT, SOFT_TX_PIN

next_write:
    delay_ticks period

    dec     bit_ctr
    brne    write_bit

    ;  Stop bit
    sbi     IO_PORT, SOFT_TX_PIN
    delay_ticks period
    ret
; --------------------------------------------------------------------


; char_read - receive one char into r24 (8N1, LSB first), per AVR-GCC ABI
.global soft_char_read
soft_char_read:
;   Wait for start bit: idle is HIGH, start bit is LOW
;   while (IO_PIN & (1 << SOFT_RX_PIN)) {} ;
wait_start:
    in      bit_ctr, IO_PIN
    sbrc    bit_ctr, SOFT_RX_PIN    ; skip rjmp when RX is LOW = start bit
    rjmp    wait_start

;   Wait a .5 bit period so bit0 is sampled mid-bit
    delay_ticks half_period

    in      bit_ctr, IO_PIN
    sbrc    bit_ctr, SOFT_RX_PIN    ; confirm start bit remains low
    rjmp    wait_start

;   Wait a 1 bit period for a total of 1.5 bit periods
    delay_ticks period

;   Read 8 data bits, LSB first, into r24
    ldi     bit_ctr, 8              ; bit counter

read_bit:
    in      temp_r18, IO_PIN           ; scratch read - do not clobber r24
    clc                         ; assume bit is 0
    sbrc    temp_r18, SOFT_RX_PIN         ; skip sec when RX is LOW
    sec                         ; RX HIGH -> bit is 1
    ror     char_reg                 ; shift carry into MSB (LSB-first)

    delay_ticks period

    dec     bit_ctr
    brne    read_bit

    ret
; --------------------------------------------------------------------


; void flash_write(uint8_t addr)
;   Set the Z  r31/r30 address to PROGMEM text on entry
;   Calling convention: AVR-GCC ABI (r31/r30 FLASH address, r24 out, r18 scratch).

.global flash_write
flash_write:
        lpm     char_reg, Z+     ; load byte at Z into r24, the char_write register
        tst     char_reg          ; exit if null byte
        breq    print_done
        rcall   soft_char_write  ; write char to console
        rjmp    flash_write

print_done:
    ret

; --------------------------------------------------------------------

; ====================================================================
;  DATA SECTION  (initialized variables in SRAM)
;  Declare with:  my_var: .byte 0
; ====================================================================
.section .data

; ====================================================================
;  BSS SECTION  (zero-initialized / uninitialized variables in SRAM)
;  Declare with:  my_buf: .skip 16
; ====================================================================
.section .bss
