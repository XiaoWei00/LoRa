#ifndef _BASICRF_H_
#define _BASICRF_H_

/*
同一层的优先级 
是 if 语句的先后顺序
*/


#define SEND_URAT_MESSAGE 0X0001           // 发送串口消息

#define RECEIVE_CONTINUOUS_MESSAGE 0X0002 //连续接收消息

#define SEND_PERIODIC_MESSAGE  0X0004  //  周期性发送消息






unsigned short app_process_events(unsigned char tasksId,unsigned short events);



#endif