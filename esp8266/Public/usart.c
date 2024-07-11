#include "usart.h"		 
#include "delay.h"		
#include "string.h"
#include "ESP8266.h"

int receive_finished;
uint8_t ret;

uint16_t USART_RX_STA=0;       //接收状态标记	
uint8_t USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节

uint8_t USART2_RX_FLAG;       //接收状态标记	
uint16_t USART2_RX_STA=0;       //接收状态标记	
uint8_t USART2_RX_BUF[MAX_DATA_COUNT];     //接收缓冲,最大USART_REC_LEN个字节
uint8_t USART2_TX_BUF[MAX_DATA_COUNT];     //接收缓冲,最大USART_REC_LEN个字节

uint8_t send_data[] = {0x01, 0x02, 0x00, 0x00, 0x00, 0x1D, 0xB8, 0x03};

uint8_t receive_data1[] = {0x01, 0x02, 0x04, 0x01, 0x00, 0x00, 0x00, 0xFA, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data2[] = {0x01, 0x02, 0x04, 0x02, 0x00, 0x00, 0x00, 0xFA, 0x5A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data3[] = {0x01, 0x02, 0x04, 0x04, 0x00, 0x00, 0x00, 0xFA, 0xD2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data4[] = {0x01, 0x02, 0x04, 0x08, 0x00, 0x00, 0x00, 0xF9, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data5[] = {0x01, 0x02, 0x04, 0x10, 0x00, 0x00, 0x00, 0xFF, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data6[] = {0x01, 0x02, 0x04, 0x20, 0x00, 0x00, 0x00, 0xF0, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data7[] = {0x01, 0x02, 0x04, 0x40, 0x00, 0x00, 0x00, 0xEE, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data8[] = {0x01, 0x02, 0x04, 0x80, 0x00, 0x00, 0x00, 0xD2, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data9[] = {0x01, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0xAA, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data10[] = {0x01, 0x02, 0x04, 0x00, 0x02, 0x00, 0x00, 0x5A, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data11[] = {0x01, 0x02, 0x04, 0x00, 0x04, 0x00, 0x00, 0xBA, 0x23, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data12[] = {0x01, 0x02, 0x04, 0x00, 0x08, 0x00, 0x00, 0x7A, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data13[] = {0x01, 0x02, 0x04, 0x00, 0x10, 0x00, 0x00, 0xFA, 0x27, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data14[] = {0x01, 0x02, 0x04, 0x00, 0x20, 0x00, 0x00, 0xFA, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data15[] = {0x01, 0x02, 0x04, 0x00, 0x40, 0x00, 0x00, 0xFA, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data16[] = {0x01, 0x02, 0x04, 0x00, 0x80, 0x00, 0x00, 0xFA, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data17[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x01, 0x00, 0xFA, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data18[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x02, 0x00, 0xFA, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data19[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x04, 0x00, 0xF9, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data20[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x08, 0x00, 0xFC, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data21[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x10, 0x00, 0xF6, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data22[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x20, 0x00, 0xE2, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t receive_data23[] = {0x01, 0x02, 0x04, 0x00, 0x00, 0x40, 0x00, 0xCA, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


int fputc(int ch,FILE *p)  //函数默认的，在使用printf函数时自动调用
{
	USART_SendData(USART1,(u8)ch);	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	return ch;
}

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx,ch);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

void Usart_SendArray( USART_TypeDef *pUSARTx, uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for(i=0;i<Length;i++){
	    Usart_SendByte(pUSARTx,Array[i]);
	}
}

/*******************************************************************************
* 函 数 名         : USART1_Init
* 函数功能		   : USART1初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/ 
void USART1_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART1, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

/*******************************************************************************
* 函 数 名         : USART1_IRQHandler
* 函数功能		   : USART1中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
void USART1_IRQHandler(void)                	//串口1中断服务程序  接收
{
		u8 Res;
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a 回车换行结尾)
		{
					Res =USART_ReceiveData(USART1);	//读取接收到的数据
					
					if((USART_RX_STA&0x8000)==0)//接收未完成
					{
									if(USART_RX_STA&0x4000)//接收到了0x0d
									{
											if(Res!=0x0a)USART_RX_STA=0;//接收错误,重新开始
											else USART_RX_STA|=0x8000;	//接收完成了 
									}
									else //还没收到0X0D
									{	
											if(Res==0x0d)USART_RX_STA|=0x4000;
											else
											{
													USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
													USART_RX_STA++;
													if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//接收数据错误,重新开始接收	  
											}		 
									}
					}   		 
     } 	
	
} 	


/*******************************************************************************
* 函 数 名         : USART2_Init
* 函数功能		   : USART2初始化函数
* 输    入         : bound:波特率
* 输    出         : 无
*******************************************************************************/ 
void USART2_Init(u32 bound)
{
   //GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //打开时钟
 
	
	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//TX			   //串口输出PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //复用推挽输出
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* 初始化串口输入IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//RX			 //串口输入PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //模拟输入
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* 初始化GPIO */
	

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
	USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
	USART_Cmd(USART2, ENABLE);  //使能串口1 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//开启相关中断

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、	
}

/*******************************************************************************
* 函 数 名         : USART2_IRQHandler
* 函数功能		   : USART2中断函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/ 
u8 Serial_GetRxFlag(void) {
	  
    if (USART2_RX_FLAG==1) {  
				
        USART2_RX_FLAG=0;
        return 1;
    }
			  return 0;
}

void USART2_IRQHandler(void) {
		static uint8_t Rxstate=0;
	  static uint8_t pRxPacket=0;

    if (USART_GetITStatus(USART2,USART_IT_RXNE) == SET) {
				uint8_t RxData=USART_ReceiveData(USART2);
				if(Rxstate==0){
						if(RxData==0x01){
								Rxstate=1;
							  pRxPacket=0;
								USART2_RX_BUF[pRxPacket++]=RxData;
						}
				}else if(Rxstate==1){
							USART2_RX_BUF[pRxPacket++]=RxData;
					    if(pRxPacket>=14){
								 	Rxstate=0;
								  USART2_RX_FLAG=1;
							}
				}
				
				USART_ClearITPendingBit(USART2,USART_IT_RXNE);
    }
		
		if (USART_GetITStatus(USART2, USART_IT_IDLE) != SET)
	{
		
		receive_finished = 1;   		                  
		USART_ClearITPendingBit(USART2, USART_IT_IDLE);
	}
	
	USART2->SR;
	USART2->DR;
	
}

void read_data(int read_enable)
{
	int j;

	if (read_enable == 1)	
	{
		read_enable = 0;
		USART2_TX_BUF[0] = 0x01;	
		USART2_TX_BUF[1] = 0x02;
		USART2_TX_BUF[2] = 0x00;
		USART2_TX_BUF[3] = 0x00;
		USART2_TX_BUF[4] = 0x00;
		USART2_TX_BUF[5] = 0x1D;
		USART2_TX_BUF[6] = 0xB8;	
		USART2_TX_BUF[7] = 0x03;
	}

	for (j = 0; j < 8; j++)							
	{
		while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
		USART_SendData(USART2, USART2_TX_BUF[j]);
	}
	
}

void Analysis_data(void)
{
	
	if (receive_finished == 1)	//接收完成
	{
		receive_finished = 0;

          ret = memcmp(USART2_RX_BUF, receive_data1,8);
					if(ret==0){
           					
						esp8266_post_1();
						
					}
					
					ret = memcmp(USART2_RX_BUF, receive_data2, 8);
					if(ret==0){	
            			
						esp8266_post_2(); 
            						
					}
		
					ret = memcmp(USART2_RX_BUF, receive_data3, 8);
					if(ret==0){			
						
						esp8266_post_3();
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data4, 8);
					if(ret==0){			
						
						esp8266_post_4();
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data5, 8);
					if(ret==0){			
						
						esp8266_post_5(); 
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data6, 8);
					if(ret==0){			
						
						esp8266_post_6();
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data7, 8);
					if(ret==0){			
						
						esp8266_post_7();
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data8, 8);
					if(ret==0){			
						
						esp8266_post_8(); 
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data9, 8);
					if(ret==0){			
						
						esp8266_post_9();
            						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data10, 8);
					if(ret==0){			
						
						esp8266_post_10();
            						
					}
					
					ret = memcmp(USART2_RX_BUF, receive_data11, 8);
					if(ret==0){
            						
						esp8266_post_11(); 
           						
					}
					
					ret = memcmp(USART2_RX_BUF, receive_data12, 8);
					if(ret==0){	
            						
						esp8266_post_12();
            						
					}
		
					ret = memcmp(USART2_RX_BUF, receive_data13, 8);
					if(ret==0){			
						
						esp8266_post_13(); 
          				
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data14, 8);
					if(ret==0){			
						
						esp8266_post_14(); 
            					
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data15, 8);
					if(ret==0){			
						
						esp8266_post_15();
           					
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data16, 8);
					if(ret==0){			
						
						esp8266_post_16();
           						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data17, 8);
					if(ret==0){			
						
						esp8266_post_17();
           						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data18, 8);
					if(ret==0){			
						
						esp8266_post_18(); 
          					
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data19, 8);
					if(ret==0){			
						
						esp8266_post_19();
           						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data20, 8);
					if(ret==0){			
						
						esp8266_post_20();
          					
					}		
					
					ret = memcmp(USART2_RX_BUF, receive_data21, 8);
					if(ret==0){			
						
						esp8266_post_21();
          				
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data22, 8);
					if(ret==0){			
						
						esp8266_post_22();
          						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data23, 8);
					if(ret==0){			
						
						esp8266_post_23();
          						
					}	
		
		USART2_RX_STA = 0;
	}

	
}


