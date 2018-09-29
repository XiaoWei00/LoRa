#ifndef  _LED_H_
#define  _LED_H_



  


#define LED_GREEN   0X01
#define LED_RED     0X02
#define LED_ALL     0x03

#define LED_TX LED_GREEN
#define LED_RX LED_RED



void led_init(void);

void led_on(unsigned char led);

void led_off(unsigned char led);

void led_toggle(unsigned char led);



#endif