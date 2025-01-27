#ifndef _led_H
#define _led_H

#include "system.h"

/*  LED时钟端口、引脚定义 */
#define LED_PORT 			GPIOA  
#define LED_PIN 			GPIO_Pin_4
#define LED_PORT_RCC	RCC_APB2Periph_GPIOA

#define led1 PCout(0)
#define led2 PCout(1)
#define led3 PCout(2)


void LED_Init(void);
void LED_Init2(void);
void LED_on(void);
void LED_off(void);

#endif
