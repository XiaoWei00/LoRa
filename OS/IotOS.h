#ifndef _IOTOS_H_
#define _IOTOS_H_


#define tasksNum 4

#define MAC 0
#define NWK 1
#define HAL 2
#define APP 3


extern unsigned short int tasksEvents[tasksNum];


#define    INT_OFF()   asm("sim") 
#define    INT_ON()    asm("rim")



void iotos_init(void);
void iotos_start(void);
void iotos_run(void);





#endif