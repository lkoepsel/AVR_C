#include "unolib.h"

// https://www.nongnu.org/avr-libc/user-manual/FAQ.html#faq_softreset 
// Function Implementation
void wdt_init(void)
{
MCUSR = 0;
wdt_disable();
return;
}
