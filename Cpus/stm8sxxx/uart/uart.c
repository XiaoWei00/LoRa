#include "uart.h"
#include "IotOS.h"
#include "hal.h"


unsigned char uRxDate[42]={""};

void uart1_init(void)
{
	
        UART1_CR2=0x24;   //0010  0100  ����ʹ��  �����ж�ʹ��
      // UART1_CR2=0x00;
        
	UART1_SR=0;  //
        
	UART1_CR1=0; //����żУ��
        
	UART1_CR3=0;  //1λֹͣλ  
        
	//UART1_BRR2 = 0x00;         // ���ò�����19200
	//UART1_BRR1 = 0x1A;         // 8M/19200 = 0x01A0
        
       // UART1_BRR2 = 0x01;         // ���ò�����9600
	//UART1_BRR1 = 0x34;         // 8M/9600= 0X0341
        
        UART1_BRR2 = 0x05;         // ���ò�����115200
	UART1_BRR1 = 0x04;         // 8M/115200 = 0x0045
        
        
	UART1_CR2_TEN=1; //���ڷ���ʹ��
}
/***********************************************
�� ��:	send_char_com( unsigned char ch)
�� ��:	���ڷ���һ��ʮ����������PC
*********************************************** */  
/*
void uart1_send(unsigned char UtxData)
{
	//UART1_CR2_TEN=1; //���ڷ���ʹ��
 	while(!UART1_SR_TXE);
  		UART1_DR = UtxData;         //
   	while(!UART1_SR_TC);//TC==0 ������� �ȴ�UART ����������ɣ�
		//UART1_CR2_TEN=0;//���ڷ��ͽ�ֹ
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

/*************Uart1 �����ж����*********************/
#pragma vector=UART1_R_RXNE_vector
__interrupt void UART1_R_RXNE(void)
{
  
      char Urxtemp;
      static unsigned char startFlag=0;
      static unsigned char endFlag=0;
      static unsigned char index=0;  
  
      Urxtemp=UART1_DR;  //�жϱ�־λ  ���
      
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
         printf("ATָ��error\r\n");
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



//STM8S,printf�����ض��� 

int fputc(int ch, FILE *f)
{ 
  while (!(UART1_SR&0x80)); 
  UART1_DR=ch;
  return ch; 
} 












