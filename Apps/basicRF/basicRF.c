#include "app.h"
#include "timer.h"
#include "uart.h"
#include "csma.h"
#include "IotOS.h" 
#include "rf.h"
#include "exti.h"
#include "hal.h"
#include "led.h"



static void app_send_message(unsigned int applength,unsigned char *appdata);
static void set_send_period(unsigned int sendtime);
static void app_receive_message();
static void app_send_uartMessage(unsigned int applength,unsigned char *appdata);

unsigned short app_process_events(unsigned char tasksId,unsigned short events)
{
	
       (void)tasksId;  //未使用参数  
       
      /* 
       if(events & SEND_URAT_MESSAGE)
       {
         app_send_uartMessage(sendnum,&uRxDate[4]);
         sendnum=0;
         return (events ^ SEND_URAT_MESSAGE);
       }
       */
      
	if(events & SEND_PERIODIC_MESSAGE)
	{
          
         // static int count;
          unsigned char appdata[]="1111111111\r\n";
          unsigned int applength=(sizeof(appdata)/sizeof(appdata[0]))-1;
          static char timerCfgFlag=0; 
          if (timerCfgFlag==0)
          {
            set_send_period(10); //(time*1)ms   
            timer1On();
            timerCfgFlag=1;
          }
          app_send_message(applength,appdata);
          
         // printf("AT%d",count++);
         // printf("%s",appdata);
          //led_toggle(LED_TX);
          return (events ^ SEND_PERIODIC_MESSAGE);
	}
       
       /*
       
        if(events & RECEIVE_CONTINUOUS_MESSAGE)
        {
           app_receive_message();
           return (events ^ RECEIVE_CONTINUOUS_MESSAGE);
        }
        */
        return events;
	
}

static void set_send_period(unsigned int sendtime)
{  
    timer1Num=sendtime;
}

static void app_send_message(unsigned int applength,unsigned char *appdata)
{
     rfStateFlag=0;  //发送
     mac_send_message(applength,appdata);
}
static void app_receive_message()
{
    mac_receive_message();
}
/*
void app_send_uartMessage(unsigned int applength,unsigned char *appdata)
{
 
    app_send_message(applength,appdata); 
    
    rfStateFlag=1;  //接收
    rf_config_receiveParam();
}
*/







