

#include "board_cfg.h"

#ifdef LORA1
#ifdef S_SPI

#include "s_spi.h"





void s_spi_init(void)
{

        set_SSCK_PIN_out;
        set_SMISO_PIN_in;
        set_SMOSI_PIN_out;
        set_SNCS_PIN_out;
}


void s_spi_write_byte(unsigned char WrPara)
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


unsigned char s_spi_read_byte(void)
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


unsigned char s_spi_read(unsigned char adr)
{
   unsigned char tmp;
   s_spi_write_byte(adr);
   tmp=s_spi_read_byte();
   
   S_NCS=1;
   
   return (tmp);
}


void s_spi_write(unsigned short int WrPara)                
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


void s_spi_burstread(unsigned char adr, unsigned char *ptr, unsigned char length)
{
  unsigned char i;
  if(length<=1)                                            //length must more than one
    return;
  else
  {
    S_SCK=0; 
    S_NCS=0;
    s_spi_write_byte(adr); 
    for(i=0;i<length;i++)
    ptr[i] = s_spi_read_byte();
    S_NCS=1;  
  }
}



void s_spi_burstwrite(unsigned char adr, unsigned char *ptr, unsigned char length)
{ 
  unsigned char i;

  if(length<=1)                                            //length must more than one
    return;
  else  
  {   
    S_SCK=0;
    S_NCS=0;        
    s_spi_write_byte(adr|0x80);
    for(i=0;i<length;i++)
    s_spi_write_byte(ptr[i]);
    S_NCS=1;  
  }
}


#endif
#endif