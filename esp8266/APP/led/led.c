#include "led.h"

/*******************************************************************************
* 函 数 名         : LED_Init
* 函数功能		   : LED初始化函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void LED_Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;//定义结构体变量
		
		RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin=LED_PIN;  //选择你要设置的IO口
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //设置推挽输出模式
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //设置传输速率
		GPIO_Init(LED_PORT,&GPIO_InitStructure); 	   /* 初始化GPIO */
		
		GPIO_SetBits(LED_PORT,LED_PIN);   //将LED端口拉高，熄灭所有LED			LED=1;
	
}

void LED_Init2()
{
  GPIO_InitTypeDef     GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

void LED_on()
{
  GPIO_SetBits(GPIOA,GPIO_Pin_0);
}

void LED_off()
{ 
  GPIO_ResetBits(GPIOA,GPIO_Pin_0);
}

