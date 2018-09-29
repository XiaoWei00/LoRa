#include "board_cfg.h"
#include "s_spi.h"


void sspi_init(void)
{
      SET_SCK_PIN();
      SET_MISO_PIN();
      SET_MOSI_PIN();
      SET_NCS_PIN();
}

/**********************************************************
**Name:     SPICmd8bit
**Function: SPI Write one byte
**Input:    WrPara
**Output:   none
**note:     use for burst mode
**********************************************************/
void SPICmd8bit(unsigned char WrPara)
{
  unsigned char  bitcnt;  
  S_NCS=0;
  S_SCK=0;
  
  for(bitcnt=8; bitcnt!=0; bitcnt--)
  {
    S_SCK=0;
    if(WrPara&0x80)
      S_MOSI=1;
    else
      S_MOSI=0;
	asm("nop");	
	asm("nop");	
     S_SCK=1;
	asm("nop");	
    WrPara <<= 1;
  }
  S_SCK=0;
  S_MOSI=1;

}


/**********************************************************
**Name:     SPIRead8bit
**Function: SPI Read one byte
**Input:    None
**Output:   result byte
**Note:     use for burst mode
**********************************************************/
u8 SPIRead8bit(void)
{
 unsigned char RdPara = 0;
 unsigned char bitcnt;
 
  S_NCS=0;
  S_MOSI=1;                                                 //Read one byte data from FIFO, MOSI hold to High
  for(bitcnt=8; bitcnt!=0; bitcnt--)
  {
    S_SCK=0;
	asm("nop");	
	asm("nop");	
    RdPara <<= 1;
    S_SCK=1;
    if(S_MISO)
      RdPara |= 0x01;
    else
      RdPara |= 0x00;
  }
  S_SCK=0;
  return(RdPara);



}

/**********************************************************
**Name:     SPIRead
**Function: SPI Read CMD
**Input:    adr -> address for read
**Output:   None
**********************************************************/
u8 SPIRead(u8 adr)
{
   unsigned char tmp;
   SPICmd8bit(adr);
   tmp=SPIRead8bit();
   
   S_NCS=1;
   
   return (tmp);
}


/**********************************************************
**Name:     SPIWrite
**Function: SPI Write CMD
**Input:    WrPara -> address & data
**Output:   None
**********************************************************/
void SPIWrite(word WrPara)               
{                                                       
  unsigned char bitcnt;    
  
  S_SCK=0;
  S_NCS=0;
  
  WrPara |= 0x8000;                                        //MSB must be "1" for write 
  
  for(bitcnt=16; bitcnt!=0; bitcnt--)
  {
    S_SCK=0;
	asm("nop");	
	asm("nop");	
    if(WrPara&0x8000)
      S_MOSI=1;
    else
      S_MOSI=0;
    S_SCK=1;
    WrPara <<= 1;
  }
  S_SCK=0;
  S_MOSI=1;
  S_NCS=1;
}


/**********************************************************
**Name:     SPIBurstRead
**Function: SPI burst read mode
**Input:    adr-----address for read
**          ptr-----data buffer point for read
**          length--how many bytes for read
**Output:   None
**********************************************************/
void SPIBurstRead(u8 adr, u8 *ptr, u8 length)
{
  unsigned char i;
  if(length<=1)                                            //length must more than one
    return;
  else
  {
    S_SCK=0; 
    S_NCS=0;
    SPICmd8bit(adr); 
    for(i=0;i<length;i++)
    ptr[i] = SPIRead8bit();
    S_NCS=1;  
  }
}
/**********************************************************
**Name:     SPIBurstWrite
**Function: SPI burst write mode
**Input:    adr-----address for write
**          ptr-----data buffer point for write
**          length--how many bytes for write
**Output:   none
**********************************************************/
void BurstWrite(u8 adr, u8 *ptr, u8 length)
{ 
  unsigned char i;

  if(length<=1)                                            //length must more than one
    return;
  else  
  {   
    S_SCK=0;
    S_NCS=0;        
    SPICmd8bit(adr|0x80);
    for(i=0;i<length;i++)
    SPICmd8bit(ptr[i]);
    S_NCS=1;  
  }
}


