#include "IotOS.h"
#include "led.h"
#include "app.h"
#include "hal.h"
#include "mac.h"
#include "nwk.h"

typedef  unsigned short (*tasksHandlerFun)(unsigned char tasksId,unsigned short events);

unsigned short int tasksEvents[tasksNum];

const tasksHandlerFun tasksFun[]={
	mac_process_events,
	nwk_process_events,
	hal_process_events,
	app_process_events
};

const unsigned char tasksCount=(sizeof(tasksFun)/sizeof(tasksFun[0])); 



void iotos_init()
{
	
  tasksEvents[APP] |=SEND_PERIODIC_MESSAGE; //周期性发送消息
  	
}
	
void iotos_start()
{
	
	while(1)
	{
         iotos_run();
		
	}
	
}

void iotos_run()
{
	
      char index=0;
	
	do{
            if(tasksEvents[index])
            {
                    break;
            }
	}while(++index<tasksCount);
		
	if(index<tasksCount)
	{
		unsigned short int events;
		
		INT_OFF();//禁止全局中断
		events=tasksEvents[index];
		tasksEvents[index]=0;
		INT_ON();//使能全局中断
                
	        events=(tasksFun[index])(index,events);
  
        
		INT_OFF();
		tasksEvents[index] |=events;
		INT_ON();
             	
	}
	
}