#include <stdint.h>

#ifndef USART_H
#define USART_H

#define USART_BUF_LEN 32

void USARTConfig(void);
void USARTTx(uint8_t dat);
uint8_t USARTRx(void);
void USARTTxString (char *string);

extern volatile unsigned char USARTRxBuf[USART_BUF_LEN];
extern volatile unsigned char CommandReceived;

#endif // USART_H
