#include <stm32f411xe.h>
#include "i2s.h"
#include "usart.h"
#include "utils.h"

#define I2SDIV 12
#define I2SODD 1

 
//volatile uint16_t I2STxBuf[I2S_BUF_LEN];


void I2SConfig(void) {
    
    // Configure I2S2
    
    // Disable I2S2
    SPI2->I2SCFGR &= ~SPI_I2SCFGR_I2SE;
    while ((SPI2->I2SCFGR & SPI_I2SCFGR_I2SE));
    
    // Clear registers
    SPI2->I2SCFGR = 0;
    SPI2->I2SPR = 0;
   
    // Select I2SDIV and ODD in SPI_I2SPR to define Baud rate
    SPI2->I2SPR |= (I2SODD << SPI_I2SPR_ODD_Pos);
    SPI2->I2SPR |= (I2SDIV << SPI_I2SPR_I2SDIV_Pos);
    
    //SPI2->I2SPR |= SPI_I2SPR_MCKOE;
    
    // Select CPOL to define clock polarity
    // Clock polarity low <--- CHECK
    SPI2->I2SCFGR &= ~SPI_I2SCFGR_CKPOL;
    //SPI2->I2SCFGR |= SPI_I2SCFGR_CKPOL;
    
    // I2SSTD 0 I2S is reset value
    
    
    SPI2->I2SCFGR |= //SPI_I2SCFGR_CHLEN |    // 32 bit frame
                     //SPI_I2SCFGR_DATLEN_0 | // 24 bit sample
                     SPI_I2SCFGR_I2SCFG_1 | // Master Transmit
                     SPI_I2SCFGR_I2SMOD;    // I2S Mode
    
                     

    // Select interrupts and DMA using SPI_CR2 <-- Later
    
    // Enable I2S2
    SPI2->I2SCFGR |= SPI_I2SCFGR_I2SE;
    while (!(SPI2->I2SCFGR & SPI_I2SCFGR_I2SE));
    
    //--
 
    // Configure I2S3
    
    // Disable I2S3
    SPI3->I2SCFGR &= ~SPI_I2SCFGR_I2SE;
    while ((SPI3->I2SCFGR & SPI_I2SCFGR_I2SE));
    
    // Clear registers
    SPI3->I2SCFGR = 0;
    SPI3->I2SPR = 0;
   
    // Select I2SDIV and ODD in SPI_I2SPR to define Baud rate
    SPI3->I2SPR |= (I2SODD << SPI_I2SPR_ODD_Pos);
    SPI3->I2SPR |= (I2SDIV << SPI_I2SPR_I2SDIV_Pos);

    // Select CPOL to define clock polarity
    // Clock polarity low <--- CHECK
    SPI3->I2SCFGR &= ~SPI_I2SCFGR_CKPOL;
    //SPI3->I2SCFGR |= SPI_I2SCFGR_CKPOL;
    
    // I2SSTD 0 I2S is reset value
    

    SPI3->I2SCFGR |= //SPI_I2SCFGR_CHLEN |    // 32 bit frame
                     //SPI_I2SCFGR_DATLEN_0 | // 24 bit sample
                     SPI_I2SCFGR_I2SCFG_0 | // Slave Receive
                     SPI_I2SCFGR_I2SMOD;    // I2S Mode

    // Select interrupts and DMA using SPI_CR2 <-- Later
    
    // Enable I2S3
    SPI3->I2SCFGR |= SPI_I2SCFGR_I2SE;
    while (!(SPI3->I2SCFGR & SPI_I2SCFGR_I2SE));

    
}






void I2STx(uint16_t* data) {
    
    SPI2->DR = *data;
    while(!(SPI2->SR & SPI_SR_TXE)); 
}


uint16_t I2SRx() {
    
    while(SPI3->SR & SPI_SR_BSY);
    SPI3->DR = 1;
    
    while(!((SPI3->SR) & (SPI_SR_RXNE))){};
    return SPI3->DR;
}

