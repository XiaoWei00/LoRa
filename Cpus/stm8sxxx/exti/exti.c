#include "exti.h"
#include "csma.h"
#include "led.h"
#include "rf.h"
#include "IotOS.h"
#include "app.h"



unsigned char rfStateFlag=1;//接收

void exti_init()
{
   EXTI_CR1 = 0x40; // PD口上升沿触发中断  0100 0000
}


/**********************************************************
	外部中断PD入口                    
**********************************************************/ 
#pragma vector =EXTI3_vector
__interrupt void EXTI_PD(void)
{
  
     if(rfStateFlag==0) //发送结束
     {
       led_off(LED_GREEN);
       txState=sendEndState; 
       
     }
     else              //接收结束
     {
       tasksEvents[APP] |=RECEIVE_CONTINUOUS_MESSAGE;
     }
     rf_clear_irq();
}





