#include <stdlib.h>

#include "csma.h"
#include "rf.h"
#include "timer.h"
#include "led.h"

#include "uart.h"



//������ķ�Χ
#define  MaxRandomNum   7   //���ֵ
#define  MinRandomNum   1  //��Сֵ


//����˱ܴ���
#define  MaxBoNum    6


uint8 txState=0;   //״̬
uint8 txBoNum=0;   //�˱ܴ��� 
uint8 txDeNum=0;  //�ŵ����м�����





void set_slottime(uint32 waittime)
{
      timer4Num=waittime;
}
void set_backofftime(uint32 backofftime)
{
      timer2Num=backofftime;
}

uint8 get_randomSeed()//��ȡ������� 
{
   return TIM1_CNTRL;
}
uint8 generate_backoff_randomNum()  // ����������˼���ֵ
{
       uint8 randomNum;
       srand(get_randomSeed()); //
       randomNum=rand()%(MaxRandomNum+1-MinRandomNum)+MinRandomNum;
       return randomNum;
}

void mac_send_message(uint32 maclength,unsigned char *macdata)
{
    txState=preCcaState;
    uint8 backoffRandomNum=0; 
    while (txState!=endState)
    {
           
       switch (txState)
       {
           
       case preCcaState :
               
                rf_config_ccaParam();
                txState=ccaState;
                break;
                     
       case ccaState:
                 if(txBoNum==MaxBoNum)   //��������˱ܴ���          
                 {
                
                   txBoNum=0;  
                             // ��������
                   txState=endState;
                   
                 }
                 else 
                {
                    if(rf_cca()==_BUSY)   //�ж��ŵ��Ƿ����
                    {
                            printf("txDeNum=%d\r\n",txDeNum);
                            
                          txDeNum=0;
                          txState=backoffState;  //�ŵ���æ������
                          led_on(LED_RED);
               
                    } 
                    else
                    { 
                      
                       txDeNum++;        //
                       
                       txBoNum=0;
                       
                       if(txDeNum==2)   //�������μ�⣬�ŵ�����,�������ݰ�
                       {
                         txDeNum=0;
                         txState=sendPacketState; 
                         
                       }
                       else
                       {
                         
                         set_slottime(12);    //time*4.08  ms   
                         timer4On();        //�ȴ�һ��slottime 
                         txState=idleState;
                       }        
                     }   
                  }
                 break;
                 
        case  sendPacketState:
                
                 rf_config_sendParam();              //���÷��Ͳ���
                 rf_enableIrq();     //���ж�
                 rf_send_message(maclength,macdata); //��������
              
                 led_on(LED_GREEN);
                 txState=idleState;
                 break;
         
        case  idleState:
            
                  //  do something
                break;
                
        case  backoffState:
                
           
                txBoNum++;  //�˱ܴ���+1
                led_on(LED_RED);
                
                backoffRandomNum=generate_backoff_randomNum(); //�����˱������
                set_backofftime(backoffRandomNum);  //time*    ����   ms
                timer2On();
         
                txState=idleState;
                break;
                
        case  sendEndState:
                rf_standbyMode();
                txState=endState;
                break;
            
    
       }
    
    }
    
}

