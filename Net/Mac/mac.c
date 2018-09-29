#include "mac.h"
#include "rf.h"
#include "board_cfg.h"
#include "led.h"
#include "sx1276.h"
#include "uart.h"

void mac_receive_message()
{
  
    static char rxcount=0;
    rf_receive_message();
    rxcount++;
    printf("%s",gb_RxData);
    printf("\r\nrxcount=%d\r\n",rxcount);
    led_toggle(LED_RED);
   
}

unsigned short mac_process_events(unsigned char tasksId,unsigned short events)
{ 
  return events;
}