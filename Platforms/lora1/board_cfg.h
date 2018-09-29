

#include "select.h"

#ifdef LORA1

/*
硬件平台配置
*/

//////**********************//////////////

#ifndef _BOARD_CFG_H_
#define _BOARD_CFG_H_


#include "stm8io_cfg.h"




////////**********1***********///////

/*****

LoRa1.0

*******/
/*
LED
*/
//高电平点亮  1  
//低电平点亮  0  
#define LEDON 0    

//
#define LED1_IO  PB4_O 
#define LED2_IO  PB5_O
#define LED3_IO  PB6_O
#define LED4_IO  PB7_O

//
#define LED_TX  LED1_IO
#define LED_RX  LED2_IO

//
#define set_LED1_PIN_out  SET_PIN_OUT(B,4)
#define set_LED2_PIN_out  SET_PIN_OUT(B,5)
#define set_LED3_PIN_out  SET_PIN_OUT(B,6)
#define set_LED4_PIN_out  SET_PIN_OUT(B,7)

/*
KEY
*/
//
#define KEYON 0
//
#define KEY1_IO PB3_I
//



/*
S_SPI
*/
//
#define S_SCK    PC5_O
#define S_MISO   PC7_I
#define S_MOSI   PC6_O
#define S_NCS    PE5_O

//
#define  set_SSCK_PIN_out  SET_PIN_OUT(C,5)
#define  set_SMISO_PIN_in  SET_PIN_IN(C,7)
#define  set_SMOSI_PIN_out SET_PIN_OUT(C,6)
#define  set_SNCS_PIN_out  SET_PIN_OUT(E,5)








#endif


#endif



