#ifndef  _CSMA_H_
#define  _CSMA_H_

#include "types.h"

extern unsigned char txState;


typedef enum
{
  preCcaState,        //׼���ŵ����
  ccaState,           //�ŵ���� 
  sendPacketState,    //�������ݰ�
  backoffState,     //�˱�
  sendEndState,      //�ȴ����ͽ���
  idleState,        //����״̬
  endState,        //��ֹ
}tx_State;

void mac_send_message(uint32 maclength,unsigned char *macdata);

void mac_receive_message();



#endif