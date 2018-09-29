#ifndef _TIMER_H_
#define _TIMER_H_



#include  <iostm8s103f3.h>


extern unsigned int timer1Num; //

extern unsigned int timer4Num; //

extern unsigned int timer2Num; //



#define timer1On()   TIM1_CR1=0x01

#define timer1Off()  TIM1_CR1=0x00

#define timer4On()   TIM4_CR1=0x01

#define timer4Off()  TIM4_CR1=0X00

#define timer2On()   TIM2_CR1=0x01

#define timer2Off()  TIM2_CR1=0x00



void timer1_init(void);
void timer2_init(void);
void timer4_init(void);

#endif