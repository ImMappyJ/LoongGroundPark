#ifndef __usart_H
#define __usart_H

#include "system.h" 
#include "stdio.h" 


#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define MAX_DATA_COUNT  		16  	//�����������ֽ��� 200

void USART1_Init(u32 bound);

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         				//����״̬���	

void USART2_Init(u32 bound);

extern u8  USART2_RX_BUF[MAX_DATA_COUNT]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�  

u8 Serial_GetRxFlag(void);
void Serial_SendPacket(void);
void USART2_SendData(void);

void read_data(int read_enable);
void Analysis_data(void);

#endif


