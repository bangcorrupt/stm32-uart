/* UART for stm32f411ce */

//#include <stdio.h>
//#include <string.h>
//#include <math.h>

#include <stm32f411xe.h>

#include "system.h"
#include "gpio.h"
#include "usart.h"
#include "utils.h" 
#include "command.h"


int main(void) {
    
    //SystemReset(); 
    SysClockConfig();
    
    GPIOConfig();
    USARTConfig();

   
    while(1){
        
        // Serial Console Commands
        if (CommandReceived) {
            HandleCommand();
        }
    }
    
    return 0;
}
