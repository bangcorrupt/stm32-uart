#include <stm32f411xe.h>
#include "gpio.h"
#include "utils.h"

#define AF_05 5
#define AF_06 6
#define AF_07 7


// Configure Pin functions
void GPIOConfig(void) {
    
    // Configure GPIOC_13 for LED
    
    // Enable GPIOC Clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
   
    // GPIOC_13 Output
    GPIOC->MODER |= GPIO_MODER_MODER13_0;
    GPIOC->MODER &= ~(GPIO_MODER_MODER13_1);
   
    // GPIOC_13 High speed
    GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED13; 
    
    // Clear GPIO_13
    GPIOC->BSRR = GPIO_BSRR_BS13;
    
    //-------------------------------------------
        
    // Configure pins for USART1
    
    // --
    // Configure GPIOB_6 for USART1 TX
    
    // Enable GPIOB clock (for USART1)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    while(!(RCC->AHB1ENR & RCC_AHB1ENR_GPIOBEN));
    

    // Enable USART1 clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    
    // GPIOB_6 Alternate Function
    GPIOB->MODER &= ~(GPIO_MODER_MODER6_0);
    GPIOB->MODER |= GPIO_MODER_MODER6_1;

    // GPIOB_6 AF_07 (USART1 TX)
    GPIOB->AFR[0] |= (AF_07 << GPIO_AFRL_AFSEL6_Pos);

    // --
    // Configure GPIOB_7 for USART1 RX
    
    // GPIOB_7 Alternate Function
    GPIOB->MODER &= ~(GPIO_MODER_MODER7_0);
    GPIOB->MODER |= GPIO_MODER_MODER7_1;

    // GPIOB_7 AF_07 (USART1 RX)
    GPIOB->AFR[0] |= (AF_07 << GPIO_AFRL_AFSEL7_Pos);

}

