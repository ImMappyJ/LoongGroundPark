#include "led.h"

/*******************************************************************************
* �� �� ��         : LED_Init
* ��������		   : LED��ʼ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void LED_Init()
{
		GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
		
		RCC_APB2PeriphClockCmd(LED_PORT_RCC,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin=LED_PIN;  //ѡ����Ҫ���õ�IO��
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
		GPIO_Init(LED_PORT,&GPIO_InitStructure); 	   /* ��ʼ��GPIO */
		
		GPIO_SetBits(LED_PORT,LED_PIN);   //��LED�˿����ߣ�Ϩ������LED			LED=1;
	
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

