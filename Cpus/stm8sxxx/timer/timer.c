#include <stdio.h>
#include "timer.h"
#include "IotOS.h"
#include "app.h"
#include "csma.h"
#include "led.h"

unsigned int timer1Num=0;
unsigned int timer4Num=0;
unsigned int timer2Num=0;


unsigned int timer1Count=0;
unsigned int timer4Count=0;
unsigned int timer2Count=0;


void timer1_init()   //1ms  ����һ���ж�
{
  TIM1_PSCRH = 0x1F;  // 8Mϵͳʱ��    f=fck/(PSCR+1)
  TIM1_PSCRL = 0x3F;  // PSCR=0x1F3F��f=8M/(0x1F3F+1)=1000Hz��ÿ����������1ms
  

  TIM1_ARRH = 0x00;  // 
  TIM1_ARRL = 0x01;  // ///////ÿ����1�β���һ���жϣ���1ms  
  
  TIM1_IER = 0x01;    // ��������  �ж�ʹ��
  //timer1On();
}


void timer4_init()  // 4.08 ms ���� һ���ж�
{
    TIM4_PSCR=0x07;//  f=fck/2^PSC    f=8M/128=62.5KHz   16us
    
    TIM4_CNTR=255;//������ֵ  255  16us  16*255=4080us=4.08ms
    
    TIM4_ARR=255;//�Զ���װ��ֵ  
   
    TIM4_IER=0x01;//��������  �ж�ʹ��
    //timer4On();
}

void timer2_init()  //400ms
{
   TIM2_PSCR=0x07;  ////  f=fck/2^PSC    f=8M/128=62.5KHz   16us

   TIM2_CNTRH=0X61;
   TIM2_CNTRL=0XA8;   //������ֵ   25000 16*25000=400ms
     
     
   TIM2_ARRH=0X3D;
   TIM2_ARRL=0X09;  //�Զ���װֵ
     
   TIM2_IER=0x01;//��������  �ж�ʹ��  
   //timer2On();
}


/**********************************************************
	Timer1 �ж����                    
**********************************************************/ 
#pragma vector=TIM1_OVR_UIF_vector
__interrupt void TIM1_OVR_UIF(void)//10ms  һ������
{
     
     TIM1_SR1= 0;  // ��������жϱ�� 
     timer1Count++;
   
   
    if(timer1Count>=timer1Num)
    {
       tasksEvents[APP] |=SEND_PERIODIC_MESSAGE;
       timer1Count=0;  
    } 
    
   
}
/*************Timer4�ж����*********************/
#pragma vector=TIM4_OVR_UIF_vector
__interrupt void TIM4_OVR_UIF(void)// 4.08 ms
{
  
    TIM4_SR=0;
    timer4Count++;
    
    if(timer4Count>=timer4Num)
    {
      txState=ccaState;     //�ȴ����������еڶ����ŵ����м��
     
      timer4Off();    //�رն�ʱ��4
      
      timer4Count=0;
      timer4Num=0; 
    }
  
   
}

/*************Timer2�ж����*********************/
#pragma vector=TIM2_OVR_UIF_vector
__interrupt void TIM2_OVR_UIF(void)//   400ms
{  
    TIM2_SR1= 0;  // ��������жϱ�� 
    timer2Count++;
    if(timer2Count>=timer2Num)
    {
      txState=ccaState;     //���˽��������½����ŵ����м��
     
      led_off(LED_RED);
      
      timer2Off();    //�رն�ʱ��2
      
      timer2Count=0;
      timer2Num=0; 
    }
  
    
   
}