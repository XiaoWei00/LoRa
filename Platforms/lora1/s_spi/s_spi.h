#ifndef _S_SPI_H_
#define _S_SPI_H_



void s_spi_init(void);
void s_spi_write_byte(unsigned char WrPara);
unsigned char s_spi_read_byte(void);
unsigned char s_spi_read(unsigned char adr);
void s_spi_write(unsigned short int WrPara) ;
void s_spi_burstread(unsigned char adr, unsigned char *ptr, unsigned char length);
void s_spi_burstwrite(unsigned char adr, unsigned char *ptr, unsigned char length);


#endif