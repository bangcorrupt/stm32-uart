#include <string.h>
#include "command.h"
#include "usart.h"

volatile unsigned char Command[USART_BUF_LEN];
extern volatile unsigned char CommandReceived = 0;


// Copy command and clear USARTRx buffer
void CopyCommand(void) { 
    memcpy(Command, USARTRxBuf, USART_BUF_LEN);
    memset(USARTRxBuf, 0, USART_BUF_LEN);
}


// Handle received command string
void HandleCommand() {
    
    CopyCommand();
    
    if (!strlen(Command)) {
    
    } else if (!strcmp(Command, "command")) {
        USARTTxString("Executing command\n\r");
    
    } else {
        USARTTxString("Command not found\n\r");
    }
    
    CommandReceived = 0;
}
