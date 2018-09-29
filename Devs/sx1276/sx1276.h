#ifndef _SX1276_H_
#define _SX1276_H_



#include "types.h"




#define CHANNEL1 0    //433MHz
#define CHANNEL2 1    //434MHz
#define CHANNEL3 2    //435MHz
#define CHANNEL4 3    //436MHz
#define CHANNEL5 4   //437MHz



#define POWER1   0   //20dbm
#define POWER2   1   //17dbm
#define POWER3   2   //14dbm
#define POWER4   3   //11dbm



extern u8 gb_SF;
extern u8  gb_BW;
extern u8  CR;	//LR_RegModemConfig1 

extern unsigned char gb_RxData[32];   

extern u8 cca;

void SX1276_LoRaEntryRx(void);
void SX1276_LoRaRxPacket(void);
void SX1276_LoRaEntryTx(void);
void SX1276_LoRaTxPacket(unsigned char *data,uint32 length);
void SX1276_LoRaClearIrq(); //Clear irq
void SX1276_Standby(); //Entry Standby mode  
void delayms(unsigned int t);
void SX1276_Sleep(void);
void SX1276_Standby(void);


uint8 SX1276_LoRaCCA(void);

void SW_Swith_RX();
void SW_Swith_TX();
void SX1276_Parameters_Select();
void RF_IRQ_DS();
void RF_IRQ_EN();
void Sx1276M_GpioInt();


void SX1276_LoRaEntryCAD(void);


void SX1276_baseConfig();
void SX1276_SetChannel(u8 channel);
void SX1276_SetPower(u8 power);
/*!
 * SX1276 Internal registers Address
 */
//SX1276 Internal registers Address
#define LR_RegFifo                                  0x0000
// Common settings
#define LR_RegOpMode                                0x0100
#define LR_RegFrMsb                                 0x0600
#define LR_RegFrMid                                 0x0700
#define LR_RegFrLsb                                 0x0800
// Tx settings
#define LR_RegPaConfig                              0x0900
#define LR_RegPaRamp                                0x0A00
#define LR_RegOcp                                   0x0B00
// Rx settings
#define LR_RegLna                                   0x0C00
// LoRa registers
#define LR_RegFifoAddrPtr                           0x0D00
#define LR_RegFifoTxBaseAddr                        0x0E00
#define LR_RegFifoRxBaseAddr                        0x0F00
#define LR_RegFifoRxCurrentaddr                     0x1000
#define LR_RegIrqFlagsMask                          0x1100
#define LR_RegIrqFlags                              0x1200
#define LR_RegRxNbBytes                             0x1300
#define LR_RegRxHeaderCntValueMsb                   0x1400
#define LR_RegRxHeaderCntValueLsb                   0x1500
#define LR_RegRxPacketCntValueMsb                   0x1600
#define LR_RegRxPacketCntValueLsb                   0x1700
#define LR_RegModemStat                             0x1800
#define LR_RegPktSnrValue                           0x1900
#define LR_RegPktRssiValue                          0x1A00
#define LR_RegRssiValue                             0x1B00
#define LR_RegHopChannel                            0x1C00
#define LR_RegModemConfig1                          0x1D00
#define LR_RegModemConfig2                          0x1E00
#define LR_RegSymbTimeoutLsb                        0x1F00
#define LR_RegPreambleMsb                           0x2000
#define LR_RegPreambleLsb                           0x2100
#define LR_RegPayloadLength                         0x2200
#define LR_RegMaxPayloadLength                      0x2300
#define LR_RegHopPeriod                             0x2400
#define LR_RegFifoRxByteAddr                        0x2500
#define LR_RegModemConfig3                         0x2600

// I/O settings
#define REG_LR_DIOMAPPING1                          0x4000
#define REG_LR_DIOMAPPING2                          0x4100
// Version
#define REG_LR_VERSION                              0x4200
// Additional settings
#define REG_LR_PLLHOP                               0x4400
#define REG_LR_TCXO                                 0x4B00
#define REG_LR_PADAC                                0x4D00
#define REG_LR_FORMERTEMP                           0x5B00

#define REG_LR_AGCREF                               0x6100
#define REG_LR_AGCTHRESH1                           0x6200
#define REG_LR_AGCTHRESH2                           0x6300
#define REG_LR_AGCTHRESH3                           0x6400


#endif