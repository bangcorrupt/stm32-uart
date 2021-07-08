#ifndef I2C_H
#define I2C_H

void I2SConfig(void);
void I2STx(uint16_t *  data);
uint16_t I2SRx();

#endif // I2C_H
