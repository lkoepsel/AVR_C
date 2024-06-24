// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction
// Change serial pins in soft_serial.h: SOFT_RX_PIN/SOFT_TX_PIN
// Set baud rate in soft_serial.h: SOFT_BAUD

#include "soft_serial.h"
#include "delay.h"

int main(void) {
    // Initialize software serial and hardware serial (UART)
    init_serial();

    char soft_out[18] = {"Enter <11 chars: "};
    char soft_in[11] = {""};

    // Example: Send and receive data
    puts("Enter upto 10 characters on soft terminal");
    init_soft_serial();
    while (1) {
        soft_string_write(soft_out, (sizeof(soft_out)/sizeof(soft_out[0])));

        // Receive data
        uint8_t received = soft_readLine(soft_in, 10);
        printf("On soft term %i chars received\n", received);
        printf("Chars are: %s\n", soft_in);
    }

    return 0;
}
