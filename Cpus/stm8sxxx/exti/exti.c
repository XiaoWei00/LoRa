#include "exti.h"
#include "csma.h"
#include "led.h"
#include "rf.h"
#include "IotOS.h"
#include "app.h"



unsigned char rfStateFlag=1;//����

void exti_init()
{
   EXTI_CR1 = 0x40; // PD�������ش����ж�  0100 0000
}


/**********************************************************
	�ⲿ�ж�PD���                    
**********************************************************/ 
#pragma vector =EXTI3_vector
__interrupt void EXTI_PD(void)
{
  
     if(rfStateFlag==0) //���ͽ���
     {
       led_off(LED_GREEN);
       txState=sendEndState; 
       
     }
     else              //���ս���
     {
       tasksEvents[APP] |=RECEIVE_CONTINUOUS_MESSAGE;
     }
     rf_clear_irq();
}





