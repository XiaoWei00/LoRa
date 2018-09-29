#ifndef _S_SPI_H_
#define _S_SPI_H_
#include "types.h"



void sspi_init(void);
void SPICmd8bit(unsigned char WrPara);
u8 SPIRead8bit(void);
u8 SPIRead(u8 adr);
void SPIWrite(word WrPara) ;
void SPIBurstRead(u8 adr, u8 *ptr, u8 length);
void BurstWrite(u8 adr, u8 *ptr, u8 length);

#endif