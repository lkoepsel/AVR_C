// soft serial - adds a software defined serial port
// Slow serial port, use for non-intensive serial interaction

#include "soft_serial.h"

int main(void) {
    // Initialize software serial and hardware serial (UART)
    init_soft_serial();
    init_serial();

    char letters[12] = {"Soft Serial"};

    // Example: Send and receive data
    while (1) {
        soft_string_write(letters, (sizeof(letters)/init_soft_serial(letters[0])));
        // Receive data
        uint8_t received = soft_readLine(letters, 4);
        printf("n char: %i", received);
    }

    return 0;
}
