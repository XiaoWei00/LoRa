

#include "board_cfg.h"


#ifdef LORA1
#ifdef LED

#include "led.h"
void led_init()
{
	set_LED1_PIN_out;
        set_LED2_PIN_out;
        set_LED3_PIN_out;
        set_LED4_PIN_out;
  
} 


void led_blink(unsigned char led)
{
	switch(led)
	{
	 case LED1:	
 	          LED1_IO=!LED1_IO;
	          break;
	 case LED2:
                  LED2_IO=!LED2_IO;
    		  break;
         case LED3:
                  LED3_IO=!LED3_IO;
                  break;
         case LED4:
                  LED4_IO=!LED4_IO;
                  break;
         default :
              break;	 
        }	
}

void led_off(unsigned char leds)
{
	
	#if LEDON
	LED1_IO=!(leds & 0x01);
	
	LED2_IO=!((leds & 0x02)>>1);
	
	LED3_IO=!((leds & 0x04)>>2);
	
	LED4_IO=!((leds & 0x08)>>3);
	#else
	LED1_IO=leds & 0x01;
	
	LED2_IO=(leds & 0x02)>>1;
	
	LED3_IO=(leds & 0x04)>>2;
	
	LED4_IO=(leds & 0x08)>>3;
    #endif
	
}

void led_on(unsigned char leds)
{
	#if LEDON
	LED1_IO=leds & 0x01;
	
	LED2_IO=(leds & 0x02)>>1;
	
	LED3_IO=(leds & 0x04)>>2;
	
	LED4_IO=(leds & 0x08)>>3;
	#else
	LED1_IO=!(leds & 0x01);
	
	LED2_IO= !((leds & 0x02)>>1);
	
	LED3_IO=!((leds & 0x04)>>2);
	
	LED4_IO=!((leds & 0x08)>>3);
       #endif	
	
}

#endif

#endif
