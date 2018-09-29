#include "IotOS.h"
#include "clk.h"
#include "led.h"
#include "timer.h"
#include "uart.h"
#include "app.h"
#include "exti.h"
#include "rf.h"
#include "s_spi.h"
#include "sx1276.h"

int main(void)
{
	
	
	clk_init();
        
        INT_OFF(); //关全局中断
        
        
        timer1_init();
        timer4_init();
        timer2_init();
        
        uart1_init();
        exti_init();
        led_init();
        led_off(LED_ALL);
        
        rf_init();
  
       
        INT_ON();  // 开全局中断 

        iotos_init();
        iotos_start();
	
	return 0;
}



