/* Uses Arduino digitalRead example to test code 
*  https://www.arduino.cc/en/Reference.digitalRead
*  button is read using INPUT_PULLUP, so it is ACTIVE LOW
*  LED will be lit when button is up and dark when button is pressed
*/
#include <avr/io.h>
#include "unolib.h"
#include "pinMode.h"
#include "digitalRead.h"
#include "digitalWrite.h"

int main (void)
{
    const uint8_t inPin = 3;   // pushbutton connected to digital pin

    pinMode(LED_BUILTIN, OUTPUT);           // sets the digital pin 13 as output
    pinMode(inPin, INPUT_PULLUP);      // sets the digital pin as input_pullup

    while(1) 
    {
        uint8_t val = digitalRead(inPin);   // read the input pin
        digitalWrite(LED_BUILTIN, val);    // sets the LED to the inverse of button's value
    }
    return 0;
}
