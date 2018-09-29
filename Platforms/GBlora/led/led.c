#include "board_cfg.h"
#include "led.h"

void led_init()
{
    SET_GLED_PIN(); 
    SET_RLED_PIN();   
} 
void led_off(unsigned char led)
{
	switch (led)
        {
          case 1:GLED=LEDOFF;break;
          case 2:RLED=LEDOFF;break;
          case 3:GLED=LEDOFF;RLED=LEDOFF;break;
          default:break;
        }
}
void led_on(unsigned char led)
{
	switch (led)
        {
          case 1:GLED=LEDON;break;
          case 2:RLED=LEDON;break;
          case 3:GLED=LEDON;RLED=LEDON;break;
          default:break;
        }	
}
void led_toggle(unsigned char led)
{
       switch (led)
        {
          case 1:GLED^=1;break;
          case 2:RLED^=1;break;
          case 3:GLED^=1;RLED^=1;break;
          default:break;
        }
	
}


