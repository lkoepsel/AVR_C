// serial_buffer - uses ElliotWilliams circular_buffer example
// to create a ring buffer
/// ultimately to create an interrupt driven serial driver

#include <stdio.h>
#include "uart.h"
#include "readLine.h"

#define BUFFER_SIZE  8

enum BufferStatus {BUFFER_OK, BUFFER_EMPTY, BUFFER_FULL};

struct Buffer {
    uint8_t data[BUFFER_SIZE];
    uint8_t newest_index;
    uint8_t oldest_index;
};
struct Buffer buffer = {{}, 0, 0};

enum BufferStatus bufferWrite(uint8_t byte){
    uint8_t next_index = (buffer.newest_index+1) % BUFFER_SIZE;

    if (next_index == buffer.oldest_index){
        return BUFFER_FULL;
    }
    buffer.data[buffer.newest_index] = byte;
    buffer.newest_index = next_index;
    return BUFFER_OK;
}

enum BufferStatus bufferRead(uint8_t *byte){
    if (buffer.newest_index == buffer.oldest_index){
        return BUFFER_EMPTY;
    }
    *byte = buffer.data[buffer.oldest_index];
    buffer.oldest_index = (buffer.oldest_index+1) % BUFFER_SIZE;
    return BUFFER_OK;
}

int main(void) {    

    init_serial();
    
    char input1[16];
    uint8_t temp_char;
    // char input2[8];

    puts("Serial Buffer Test");
    printf("Enter up to %i characters\n", BUFFER_SIZE);
    while(1)
    {
        readLine(input1, BUFFER_SIZE);
        uint8_t in_char = 0;
        while(in_char < sizeof(input1) - 1)
        {
            enum BufferStatus flag = bufferWrite(input1[in_char]);
            printf("%i char is %c, Buffer status is: %i\n", in_char, input1[in_char], flag);
            ++in_char;
        }
        uint8_t out_char = 0;
        while(out_char < sizeof(input1) - 1)
        {
            enum BufferStatus flag = bufferRead(&temp_char);
            printf("%i char is %c, Buffer status is: %i\n", out_char, temp_char, flag);
            ++out_char;
        }
        printf("\n");
        // printf("You entered %s %s\n", input1, result);
    }        
    return 0;
}
