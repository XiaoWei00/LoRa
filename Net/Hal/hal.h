#ifndef _HAL_H_
#define _HAL_H_

#include "uart.h"

#define AT_INSTRUCT  0X0001


extern unsigned char sendnum;

unsigned short hal_process_events(unsigned char tasksId,unsigned short events);



#endif 