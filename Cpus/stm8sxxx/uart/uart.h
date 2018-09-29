#ifndef _UART_H_

#define _UART_H_

#include <stdio.h>
#include <iostm8s103f3.h>
#include <string.h>

extern unsigned char uRxDate[42];  //42

void uart1_init(void);
/*
void uart1_send(unsigned char UtxData);
void uart1_prints(unsigned char * pd);
*/

#endif





