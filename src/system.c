#include <stm32f411xe.h>
#include <system_stm32f4xx.h>

#include "system.h"
#include "utils.h"

//  100MHz
#define PLL_M 	12
#define PLL_N 	96
#define PLL_P 	0 // PLLP = 2


void SystemReset(void) {
    
    RCC->CR |= RCC_CR_HSION;
    RCC->CFGR &= 0xF8FF0000;
    RCC->CR &= 0xFEF6FFFF;
    RCC->CR &= 0xFFFBFFFF;
    RCC->CR &= 0xFF80FFFF;

    // disable all RCC interrupts
    RCC->CR &= 0x00000000;
}


// Configure system clock
void SysClockConfig(void) {
    
    // ENABLE HSE and wait for the HSE to become Ready
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)){};

    // Enable POWER CLOCK
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    
    // Set the VOLTAGE REGULATOR
	PWR->CR |= PWR_CR_VOS;
    
    // Configure the FLASH PREFETCH and the LATENCY Related Settings
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_3WS;
    // Wait for flash latency to be set
    while(!(FLASH->ACR & (FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_3WS))){};



    // Configure the MAIN PLL
	RCC->PLLCFGR = (PLL_M << RCC_PLLCFGR_PLLM_Pos) | 
                   (PLL_N << RCC_PLLCFGR_PLLN_Pos) | 
                   (PLL_P << RCC_PLLCFGR_PLLP_Pos) | 
                   (RCC_PLLCFGR_PLLSRC_HSE);
    

	// Enable PLL and PLLI2S, wait for them to become ready
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)){};

    // Wait for voltage regulator
    while (!(PWR->CSR & PWR_CSR_VOSRDY)){};

    // Configure the PRESCALARS HCLK, PCLK1, PCLK2
	// AHB PR 1
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2 | RCC_CFGR_PPRE2_DIV1;
	
    // Select the System Clock Source and wait for it to be set
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL){};
    
    // Update SystemCoreClock variable
    SystemCoreClockUpdate();

}





