#ifndef _RF_H_
#define _RF_H_


#include "types.h"
#include "sx1276.h"



typedef struct 
{
 unsigned char softVersion;
 unsigned char rfPower;
 unsigned short  rfChannel;
}rfParmeter_t;


extern rfParmeter_t rfParmeter;


void rf_init();

void  rf_setParameter();

void rf_set_gpio();
void rf_enableIrq();
void rf_disableIrq();



void rf_config_sendParam();  
void rf_config_receiveParam();
void rf_send_message(uint32 maclength,unsigned char *macdata);
void rf_receive_message();
void rf_clear_irq();
void rf_standbyMode();
uint8 rf_cca();
void rf_config_ccaParam();

void rf_setChannel(u8 channel);
void rf_setPower(u8 power);
#endif