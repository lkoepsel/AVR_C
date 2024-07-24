// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction
// Change serial pins in soft_serial.h: SOFT_RX_PIN/SOFT_TX_PIN
// Set baud rate in soft_serial.h: SOFT_BAUD

#include <stdio.h>
#include "soft_serial.h"
#include "uart.h"

const char prompt[] PROGMEM = "Enter up to 9 chars: ";
const char chr_recd[] PROGMEM = " chars received\n";
#define N_in 10
#define N_out 10

int main(void) {
    // Initialize software serial and hardware serial (UART)
    init_serial();

    char soft_in[N_in] = {""};
    char soft_out[N_out] = {""};

    // Example: Send and receive data
    init_soft_serial();
    soft_pgmtext_write(prompt);
    soft_char_NL();
    puts("Soft serial has been initialized and title printed");

    while (1) {

        // Receive data
        uint8_t received = soft_readLine(soft_in, N_in - 1);
        soft_string_write(soft_out, (sizeof(soft_out)/sizeof(soft_out[0])));
        soft_char_write(received + ASCII_INTEGER);
        soft_pgmtext_write(chr_recd);
        soft_string_write(soft_in, received + 1);
        soft_char_NL();

        printf("On soft term %i ", received);
        printf("chars received: %s\n", soft_in);
    }

    return 0;
}
