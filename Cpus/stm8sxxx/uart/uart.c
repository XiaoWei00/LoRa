#include "uart.h"
#include "IotOS.h"
#include "hal.h"


unsigned char uRxDate[42]={""};

void uart1_init(void)
{
	
        UART1_CR2=0x24;   //0010  0100  接收使能  接收中断使能
      // UART1_CR2=0x00;
        
	UART1_SR=0;  //
        
	UART1_CR1=0; //无奇偶校验
        
	UART1_CR3=0;  //1位停止位  
        
	//UART1_BRR2 = 0x00;         // 设置波特率19200
	//UART1_BRR1 = 0x1A;         // 8M/19200 = 0x01A0
        
       // UART1_BRR2 = 0x01;         // 设置波特率9600
	//UART1_BRR1 = 0x34;         // 8M/9600= 0X0341
        
        UART1_BRR2 = 0x05;         // 设置波特率115200
	UART1_BRR1 = 0x04;         // 8M/115200 = 0x0045
        
        
	UART1_CR2_TEN=1; //串口发送使能
}
/***********************************************
函 数:	send_char_com( unsigned char ch)
功 能:	串口发送一个十六进制数到PC
*********************************************** */  
/*
void uart1_send(unsigned char UtxData)
{
	//UART1_CR2_TEN=1; //串口发送使能
 	while(!UART1_SR_TXE);
  		UART1_DR = UtxData;         //
   	while(!UART1_SR_TC);//TC==0 发送完成 等待UART 发送数据完成，
		//UART1_CR2_TEN=0;//串口发送禁止
} 


void uart1_prints(unsigned char * pd)
{
	while((*pd)!='\0')
	{
	uart1_send(*pd);
	pd++;
	}
}
*/

/*************Uart1 接收中断入口*********************/
#pragma vector=UART1_R_RXNE_vector
__interrupt void UART1_R_RXNE(void)
{
  
      char Urxtemp;
      static unsigned char startFlag=0;
      static unsigned char endFlag=0;
      static unsigned char index=0;  
  
      Urxtemp=UART1_DR;  //中断标志位  清除
      
      if(Urxtemp=='A' && startFlag==0)
      {
         startFlag++;
      }
      else if(Urxtemp=='T' && startFlag==1)
      {
         startFlag++;
      }
      else if(Urxtemp=='+' && startFlag==2)
      {
          startFlag++;
          memset(uRxDate, 0, sizeof(uRxDate));
      }
      else if(Urxtemp=='\r'&& startFlag==3 && endFlag==0)
      {
         endFlag++;
      }
      else if(Urxtemp=='\n' && startFlag==3 && endFlag==1)
      {
         endFlag++;
      }
      else if(Urxtemp!='\r' && startFlag==3 && endFlag==0)
      {
         uRxDate[index]=Urxtemp;
         index++;
      }
      if(index>41)
      {
         index=0;
         startFlag=0;
         endFlag=0;
         printf("AT指令error\r\n");
         memset(uRxDate, 0, sizeof(uRxDate));
      }
      
      if(endFlag==2)
      {
         index=0;
         startFlag=0;
         endFlag=0;
         tasksEvents[HAL] |=AT_INSTRUCT; 
      }
}



//STM8S,printf函数重定向 

int fputc(int ch, FILE *f)
{ 
  while (!(UART1_SR&0x80)); 
  UART1_DR=ch;
  return ch; 
} 












