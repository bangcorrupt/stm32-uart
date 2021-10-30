#include <stm32f411xe.h>
#include <string.h>

#include "usart.h"
#include "command.h"
#include "utils.h"

// USART1 Serial console keyboard input

#define USART_BUF_LEN 32

// Buffer for received USART data
volatile unsigned char USARTRxBuf[USART_BUF_LEN];
volatile unsigned short USARTRxCount = 0;


// Configure USART
void USARTConfig(void) {

    // Enable USART1 Interrupt
    NVIC_EnableIRQ(USART1_IRQn);
    
    // Enable USART_1
    USART1->CR1 |= USART_CR1_UE;
    
    // Enable Rx Interrupt
    USART1->CR1 |= USART_CR1_RXNEIE;

    // Baud rate 115200, 100MHz
    USART1->BRR = (4<<0) | (54<<4);
    
    // Enable Tx, send idle frame
    USART1->CR1 |= USART_CR1_TE;
    
    // Enable Rx
    USART1->CR1 |= USART_CR1_RE;
    
}


void USART1_IRQHandler(void) {

    // If Rx data available
    if ((USART1->SR & USART_SR_RXNE)) {
        
        // Append character to Rx buffer
        USARTRxBuf[USARTRxCount] = USARTRx();

        // If CR received
        if (USARTRxBuf[USARTRxCount]=='\r') {
            USARTRxBuf[USARTRxCount] = 0;
            USARTRxCount = 0;
            CommandReceived = 1;

        } else {
            USARTRxCount++;
            if (USARTRxCount >= USART_BUF_LEN) {
                USARTRxCount = 0;
            }
        }
    }
}


// Transmit byte over UART
void USARTTx(uint8_t dat) {

    // Load the Data
    USART1->DR = dat;
    while (!(USART1->SR & USART_SR_TC));  // Wait for transmission
    // Flash(0x800);
}



uint8_t USARTRx(void) {
    // Flash(0x800);
    while (!(USART1->SR & USART_SR_RXNE));  // Wait for data
    return USART1->DR;
}


void USARTTxString (char *string) {
	while (*string) USARTTx (*string++); // Tx char until null
}
