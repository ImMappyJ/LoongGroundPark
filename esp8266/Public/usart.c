#include "usart.h"		 
#include "delay.h"		
#include "string.h"
#include "ESP8266.h"

int receive_finished;
uint8_t ret;

uint16_t USART_RX_STA=0;       //����״̬���	
uint8_t USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�

uint8_t USART2_RX_FLAG;       //����״̬���	
uint16_t USART2_RX_STA=0;       //����״̬���	
uint8_t USART2_RX_BUF[MAX_DATA_COUNT];     //���ջ���,���USART_REC_LEN���ֽ�
uint8_t USART2_TX_BUF[MAX_DATA_COUNT];     //���ջ���,���USART_REC_LEN���ֽ�

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


int fputc(int ch,FILE *p)  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
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
* �� �� ��         : USART1_Init
* ��������		   : USART1��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/ 
void USART1_Init(u32 bound)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //��ʱ��
 
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX			   //�������PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX			 //��������PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ��ʼ��GPIO */
	

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
}

/*******************************************************************************
* �� �� ��         : USART1_IRQHandler
* ��������		   : USART1�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/ 
void USART1_IRQHandler(void)                	//����1�жϷ������  ����
{
		u8 Res;
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a �س����н�β)
		{
					Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
					
					if((USART_RX_STA&0x8000)==0)//����δ���
					{
									if(USART_RX_STA&0x4000)//���յ���0x0d
									{
											if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
											else USART_RX_STA|=0x8000;	//��������� 
									}
									else //��û�յ�0X0D
									{	
											if(Res==0x0d)USART_RX_STA|=0x4000;
											else
											{
													USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
													USART_RX_STA++;
													if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
											}		 
									}
					}   		 
     } 	
	
} 	


/*******************************************************************************
* �� �� ��         : USART2_Init
* ��������		   : USART2��ʼ������
* ��    ��         : bound:������
* ��    ��         : ��
*******************************************************************************/ 
void USART2_Init(u32 bound)
{
   //GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //��ʱ��
 
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//TX			   //�������PA9
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOA,&GPIO_InitStructure);  /* ��ʼ����������IO */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//RX			 //��������PA10
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOA,&GPIO_InitStructure); /* ��ʼ��GPIO */
	

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������1
	
	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
	
	USART_ClearFlag(USART2, USART_FLAG_TC);
		
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//��������ж�

	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����	
}

/*******************************************************************************
* �� �� ��         : USART2_IRQHandler
* ��������		   : USART2�жϺ���
* ��    ��         : ��
* ��    ��         : ��
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
	
	if (receive_finished == 1)	//�������
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


