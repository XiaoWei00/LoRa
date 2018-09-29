#ifndef  _LED_H_
#define  _LED_H_



  


#define LED1 0X01
#define LED2 0X02
#define LED3 0X04
#define LED4 0X08



void led_init(void);

void led_blink(unsigned char led);

void led_on(unsigned char leds);

void led_off(unsigned char leds);


#endif