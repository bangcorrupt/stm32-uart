#include <stm32f411xe.h>
#include "utils.h"

// Flash LED
void Flash(uint32_t d) {
    
        // Set GPIO_13
        GPIOC->BSRR = GPIO_BSRR_BR13; 
        Delay(d);             
        // Clear GPIO_13
        GPIOC->BSRR = GPIO_BSRR_BS13;
        Delay(d); 
}


// Wait a while
void Delay(volatile uint32_t d) {
    while (d--);
}
