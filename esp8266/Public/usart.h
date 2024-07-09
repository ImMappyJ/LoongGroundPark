#ifndef __usart_H
#define __usart_H

#include "system.h" 
#include "stdio.h" 


#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define MAX_DATA_COUNT  		16  	//定义最大接收字节数 200

void USART1_Init(u32 bound);

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         				//接收状态标记	

void USART2_Init(u32 bound);

extern u8  USART2_RX_BUF[MAX_DATA_COUNT]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART2_RX_STA;         				//接收状态标记	 

u8 Serial_GetRxFlag(void);
void Serial_SendPacket(void);
extern uint8_t data_ready_to_send;
void USART2_SendData(void);

#endif


