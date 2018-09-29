#include <stdlib.h>

#include "csma.h"
#include "rf.h"
#include "timer.h"
#include "led.h"

#include "uart.h"



//随机数的范围
#define  MaxRandomNum   7   //最大值
#define  MinRandomNum   1  //最小值


//最大退避次数
#define  MaxBoNum    6


uint8 txState=0;   //状态
uint8 txBoNum=0;   //退避次数 
uint8 txDeNum=0;  //信道空闲检测次数





void set_slottime(uint32 waittime)
{
      timer4Num=waittime;
}
void set_backofftime(uint32 backofftime)
{
      timer2Num=backofftime;
}

uint8 get_randomSeed()//获取随机种子 
{
   return TIM1_CNTRL;
}
uint8 generate_backoff_randomNum()  // 产生随机回退计数值
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
                 if(txBoNum==MaxBoNum)   //大于最大退避次数          
                 {
                
                   txBoNum=0;  
                             // 丢包处理
                   txState=endState;
                   
                 }
                 else 
                {
                    if(rf_cca()==_BUSY)   //判断信道是否空闲
                    {
                            printf("txDeNum=%d\r\n",txDeNum);
                            
                          txDeNum=0;
                          txState=backoffState;  //信道繁忙，回退
                          led_on(LED_RED);
               
                    } 
                    else
                    { 
                      
                       txDeNum++;        //
                       
                       txBoNum=0;
                       
                       if(txDeNum==2)   //连续两次检测，信道空闲,发送数据包
                       {
                         txDeNum=0;
                         txState=sendPacketState; 
                         
                       }
                       else
                       {
                         
                         set_slottime(12);    //time*4.08  ms   
                         timer4On();        //等待一个slottime 
                         txState=idleState;
                       }        
                     }   
                  }
                 break;
                 
        case  sendPacketState:
                
                 rf_config_sendParam();              //配置发送参数
                 rf_enableIrq();     //打开中断
                 rf_send_message(maclength,macdata); //发送数据
              
                 led_on(LED_GREEN);
                 txState=idleState;
                 break;
         
        case  idleState:
            
                  //  do something
                break;
                
        case  backoffState:
                
           
                txBoNum++;  //退避次数+1
                led_on(LED_RED);
                
                backoffRandomNum=generate_backoff_randomNum(); //产生退避随机数
                set_backofftime(backoffRandomNum);  //time*    （）   ms
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

