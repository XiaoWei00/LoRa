#include "rf.h"

#include "types.h"




rfParmeter_t rfParmeter;

void rf_init()
{
  
  rfParmeter.softVersion=1;  //����汾��
  
  rf_set_gpio();
  
  rf_setParameter();
  
  rf_config_receiveParam(); //����ģʽ
  rf_enableIrq();     //���ж�
  
}


void rf_set_gpio() //
{
 
  Sx1276M_GpioInt();
  
}

void rf_setParameter() //ѡ����Ƶ����  SF BW CR
{
   
  SX1276_Parameters_Select();  //BW SF CR
  //////
   SX1276_baseConfig();  // 
}

void rf_enableIrq() //����Ƶ�ж�
{
    RF_IRQ_EN();
}

void rf_disableIrq() //����Ƶ�ж�
{
    RF_IRQ_DS();
}
void rf_config_sendParam()
{
  
  SX1276_LoRaEntryTx();
}
void rf_config_receiveParam()
{
    SX1276_LoRaEntryRx();
    
}
void rf_send_message(uint32 maclength,unsigned char *macdata)
{

  SX1276_LoRaTxPacket(macdata,maclength);
}

void rf_receive_message()
{
  SX1276_LoRaRxPacket();
}


void rf_clear_irq()
{
  SX1276_LoRaClearIrq();
}
void rf_standbyMode()
{
   SX1276_Standby(); //Entry Standby mode
}


uint8 rf_cca()
{
  return SX1276_LoRaCCA();
}
void rf_config_ccaParam()
{
   SX1276_LoRaEntryCAD();
}

void rf_setChannel(u8 channel)
{
  SX1276_SetChannel(channel);
}
void rf_setPower(u8 power)
{
  SX1276_SetPower(power);
}









