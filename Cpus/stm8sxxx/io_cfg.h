
#ifndef  _IO_CFG_H_
#define  _IO_CFG_H_

#include  <iostm8s103f3.h>


///IO   out//////

//PA
#define PA3_O  PA_ODR_ODR3

//PB
#define PB0_O  PB_ODR_ODR0
#define PB1_O  PB_ODR_ODR1
#define PB2_O  PB_ODR_ODR2
#define PB3_O  PB_ODR_ODR3
#define PB4_O  PB_ODR_ODR4
#define PB5_O  PB_ODR_ODR5
#define PB6_O  PB_ODR_ODR6
#define PB7_O  PB_ODR_ODR7

//PC
#define PC0_O  PC_ODR_ODR0
#define PC1_O  PC_ODR_ODR1
#define PC2_O  PC_ODR_ODR2
#define PC3_O  PC_ODR_ODR3
#define PC4_O  PC_ODR_ODR4
#define PC5_O  PC_ODR_ODR5
#define PC6_O  PC_ODR_ODR6
#define PC7_O  PC_ODR_ODR7

//PD
#define PD0_O  PD_ODR_ODR0
#define PD1_O  PD_ODR_ODR1
#define PD2_O  PD_ODR_ODR2
#define PD3_O  PD_ODR_ODR3
#define PD4_O  PD_ODR_ODR4
#define PD5_O  PD_ODR_ODR5
#define PD6_O  PD_ODR_ODR6
#define PD7_O  PD_ODR_ODR7

//PE
#define PE5_O  PE_ODR_ODR5

//PF
#define PF4_O  PF_ODR_ODR4


///IO   in//////

//PA
#define PA3_I  PA_IDR_IDR3

//PB
#define PB0_I  PB_IDR_IDR0
#define PB1_I  PB_IDR_IDR1
#define PB2_I  PB_IDR_IDR2
#define PB3_I  PB_IDR_IDR3
#define PB4_I  PB_IDR_IDR4
#define PB5_I  PB_IDR_IDR5
#define PB6_I  PB_IDR_IDR6
#define PB7_I  PB_IDR_IDR7

//PC
#define PC0_I  PC_IDR_IDR0
#define PC1_I  PC_IDR_IDR1
#define PC2_I  PC_IDR_IDR2
#define PC3_I  PC_IDR_IDR3
#define PC4_I  PC_IDR_IDR4
#define PC5_I  PC_IDR_IDR5
#define PC6_I  PC_IDR_IDR6
#define PC7_I  PC_IDR_IDR7

//PD
#define PD0_I  PD_IDR_IDR0
#define PD1_I  PD_IDR_IDR1
#define PD2_I  PD_IDR_IDR2
#define PD3_I  PD_IDR_IDR3
#define PD4_I  PD_IDR_IDR4
#define PD5_I  PD_IDR_IDR5
#define PD6_I  PD_IDR_IDR6
#define PD7_I  PD_IDR_IDR7

//PE
#define PE5_I  PE_IDR_IDR5

//PF
#define PF4_I  PF_IDR_IDR4



////IO  set (in /out) /////
#define SET_PIN_OUT(port,pin)     \
      do{                     \
        P##port##_DDR_DDR##pin=1;  \
        P##port##_CR1_C1##pin=1;   \
      }while(0)    
    


#define SET_PIN_IN(port,pin) \
    do{                     \
        P##port##_DDR_DDR##pin=0;  \
        P##port##_CR1_C1##pin=1;   \
        P##port##_CR2_C2##pin=0;  \
      }while(0)



#endif
        
