/*
 * Mapping tests
 *
 * Requires serial monitor set to 250000, 8, 1, None with no line ending
 * Use Arduino Serial Monitor, minicom, PUTTY or your favorite serial monitor
 */
 
#include <stdio.h>
#include "uart.h"
#include "sysclock.h"
#include "map.h"

int main(void) {    

    init_serial();
    init_sysclock_1 ();
    
    puts("\nMapping: Simple Shift Test");
    
    uint8_t x = 14;
    uint8_t half_x = x >> 1;
    uint8_t twice_x = x << 1;
    printf("x= %u half_x= %u twice_x= %u \n", x, half_x, twice_x);

    uint8_t by_4 = 2;
    uint8_t fourth_x = x >> by_4;
    uint8_t four_x = x << by_4;
    printf("x= %u fourth_x= %u four_x= %u \n", x, fourth_x, four_x);

    puts("\nMapping: Complex Example (map() function)");
    uint16_t now;
    uint16_t elapsed;

    int32_t ADC_value = 512;
    int32_t ADC_max = 1023;
    int32_t ADC_min = 0;
    
    int32_t PWM_value;
    int32_t PWM_max = 255;
    int32_t PWM_min = 0;

    now = ticks();
    PWM_value = map(ADC_value, ADC_min, ADC_max, PWM_min, PWM_max);
    elapsed = ticks();
    printf("%u ticks - given %ld in range of %ld - %ld,  mapped value is %ld in range of %ld - %ld \n",\
        elapsed - now, ADC_value, ADC_min, ADC_max, PWM_value, PWM_min, PWM_max);

    return 0;
}
