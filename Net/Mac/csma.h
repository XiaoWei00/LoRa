#ifndef  _CSMA_H_
#define  _CSMA_H_

#include "types.h"

extern unsigned char txState;


typedef enum
{
  preCcaState,        //准备信道检测
  ccaState,           //信道检测 
  sendPacketState,    //发送数据包
  backoffState,     //退避
  sendEndState,      //等待发送结束
  idleState,        //空闲状态
  endState,        //终止
}tx_State;

void mac_send_message(uint32 maclength,unsigned char *macdata);

void mac_receive_message();



#endif