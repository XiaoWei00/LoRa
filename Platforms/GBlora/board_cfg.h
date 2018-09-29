
/*
硬件平台配置
*/

//////**********************//////////////

#ifndef _GBBOARD_CFG_H_
#define _GBBOARD_CFG_H_


#include "io_cfg.h"




////////**********1***********///////

/*****

GBLORA

*******/
/*
LED
*/
// 低/高电平  亮

#define LEDON 0   

#define LEDOFF  !LEDON

//
#define GLED  PB0_O 
#define RLED  PE5_O

//

//
#define SET_GLED_PIN()  SET_PIN_OUT(B,0)
#define SET_RLED_PIN()  SET_PIN_OUT(E,5)


/*
KEY
*/
//
#define KEYON  0
#define KEYOFF !KEYON

//
#define KEY1 PC1_I
//

//
#define SET_KEY1_PIN() SET_PIN_IN(C,1)




//
/*
S_SPI   I/O_SPI   //
*/
//
#define S_SCK    PC4_O
#define S_MISO   PC5_I
#define S_MOSI   PC6_O
#define S_NCS    PC7_O

//
#define  SET_SCK_PIN()     SET_PIN_OUT(C,4)
#define  SET_MISO_PIN()    SET_PIN_IN(C,5)
#define  SET_MOSI_PIN()    SET_PIN_OUT(C,6)
#define  SET_NCS_PIN()     SET_PIN_OUT(C,7)

//
/*
RF     SX1278  I/O
*/

//  RF_SPI(S_SPI)
#define RF_SCK  S_SCK
#define RF_MISO S_MISO
#define RF_MOSI S_MOSI
#define RF_NCS  S_NSC

//
#define RF_RST   PD2_O
#define RF_IRQ   PD3_I
#define RF_CAD   PC2_I
//#define RF_SWITCH  



//
#define SET_RFRST_PIN() SET_PIN_OUT(D,2)
#define SET_RFIRQ_PIN() SET_PIN_IN(D,3)
//#define SET_RFSWITCH_PIN() SET_PIN_OUT()
#define SET_RFCAD_PIN()  SET_PIN_IN(C,2)


#endif







