#ifndef _BASICRF_H_
#define _BASICRF_H_

/*
ͬһ������ȼ� 
�� if �����Ⱥ�˳��
*/


#define SEND_URAT_MESSAGE 0X0001           // ���ʹ�����Ϣ

#define RECEIVE_CONTINUOUS_MESSAGE 0X0002 //����������Ϣ

#define SEND_PERIODIC_MESSAGE  0X0004  //  �����Է�����Ϣ






unsigned short app_process_events(unsigned char tasksId,unsigned short events);



#endif