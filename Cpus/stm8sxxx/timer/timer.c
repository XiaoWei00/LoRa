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


void timer1_init()   //1ms  产生一次中断
{
  TIM1_PSCRH = 0x1F;  // 8M系统时钟    f=fck/(PSCR+1)
  TIM1_PSCRL = 0x3F;  // PSCR=0x1F3F，f=8M/(0x1F3F+1)=1000Hz，每个计数周期1ms
  

  TIM1_ARRH = 0x00;  // 
  TIM1_ARRL = 0x01;  // ///////每记数1次产生一次中断，即1ms  
  
  TIM1_IER = 0x01;    // 计数更新  中断使能
  //timer1On();
}


void timer4_init()  // 4.08 ms 产生 一次中断
{
    TIM4_PSCR=0x07;//  f=fck/2^PSC    f=8M/128=62.5KHz   16us
    
    TIM4_CNTR=255;//计数器值  255  16us  16*255=4080us=4.08ms
    
    TIM4_ARR=255;//自动重装的值  
   
    TIM4_IER=0x01;//计数更新  中断使能
    //timer4On();
}

void timer2_init()  //400ms
{
   TIM2_PSCR=0x07;  ////  f=fck/2^PSC    f=8M/128=62.5KHz   16us

   TIM2_CNTRH=0X61;
   TIM2_CNTRL=0XA8;   //计算器值   25000 16*25000=400ms
     
     
   TIM2_ARRH=0X3D;
   TIM2_ARRL=0X09;  //自动重装值
     
   TIM2_IER=0x01;//计数更新  中断使能  
   //timer2On();
}


/**********************************************************
	Timer1 中断入口                    
**********************************************************/ 
#pragma vector=TIM1_OVR_UIF_vector
__interrupt void TIM1_OVR_UIF(void)//10ms  一个周期
{
     
     TIM1_SR1= 0;  // 清除更新中断标记 
     timer1Count++;
   
   
    if(timer1Count>=timer1Num)
    {
       tasksEvents[APP] |=SEND_PERIODIC_MESSAGE;
       timer1Count=0;  
    } 
    
   
}
/*************Timer4中断入口*********************/
#pragma vector=TIM4_OVR_UIF_vector
__interrupt void TIM4_OVR_UIF(void)// 4.08 ms
{
  
    TIM4_SR=0;
    timer4Count++;
    
    if(timer4Count>=timer4Num)
    {
      txState=ccaState;     //等待结束，进行第二次信道空闲检测
     
      timer4Off();    //关闭定时器4
      
      timer4Count=0;
      timer4Num=0; 
    }
  
   
}

/*************Timer2中断入口*********************/
#pragma vector=TIM2_OVR_UIF_vector
__interrupt void TIM2_OVR_UIF(void)//   400ms
{  
    TIM2_SR1= 0;  // 清除更新中断标记 
    timer2Count++;
    if(timer2Count>=timer2Num)
    {
      txState=ccaState;     //回退结束，重新进行信道空闲检测
     
      led_off(LED_RED);
      
      timer2Off();    //关闭定时器2
      
      timer2Count=0;
      timer2Num=0; 
    }
  
    
   
}