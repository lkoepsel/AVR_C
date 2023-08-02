// print_fuses Print fuse values of the 328P
// https://www.avrfreaks.net/s/topic/a5C3l000000UcB5EAK/t160547

#include <avr/boot.h>
#include <stdio.h>
#include "uart.h"

int main(void) {    

    init_serial();
    
    puts("ATmega328P Fuse Values");
    printf("lockb = 0x%x ", boot_lock_fuse_bits_get(1));        
    printf("ext fuse = 0x%x ", boot_lock_fuse_bits_get(2));        
    printf("high fuse = 0x%x ", boot_lock_fuse_bits_get(3));        
    printf("low fuse = 0x%x ", boot_lock_fuse_bits_get(0));        
    printf( "Signature: 0x");
    for (uint8_t i = 0; i < 5; i += 2) {
        printf("%x", boot_signature_byte_get(i));
    }
    printf("\n");
}
