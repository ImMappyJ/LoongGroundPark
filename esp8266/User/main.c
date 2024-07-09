#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "usart.h"
#include "SysTick.h"
#include "esp8266.h"

int j;
int ret;
uint8_t USART2_RX_BUF[MAX_DATA_COUNT];

uint8_t data_ready_to_send=1;

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

int main(void)
{		
	  SysTick_Init(72);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);  //??????? ?2?
    USART1_Init(115200);
	  USART2_Init(9600);
	
    esp8266_start_post();
	  
    while(1){

				if(data_ready_to_send){
					Usart_SendArray(USART2, send_data, 8);
					delay_ms(5000);
					
				}

					ret = memcmp(USART2_RX_BUF, receive_data1, 8);
					if(ret==0){
            						
						esp8266_post_1();
						memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));
					}
					
					ret = memcmp(USART2_RX_BUF, receive_data2, 8);
					if(ret==0){	
            						
						esp8266_post_2(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}
		
					ret = memcmp(USART2_RX_BUF, receive_data3, 8);
					if(ret==0){			
						
						esp8266_post_3();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data4, 7);
					if(ret==0){			
						
						esp8266_post_4();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data5, 7);
					if(ret==0){			
						
						esp8266_post_5(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data6, 7);
					if(ret==0){			
						
						esp8266_post_6();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data7, 7);
					if(ret==0){			
						
						esp8266_post_7();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data8, 7);
					if(ret==0){			
						
						esp8266_post_8(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data9, 7);
					if(ret==0){			
						
						esp8266_post_9();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data10, 7);
					if(ret==0){			
						
						esp8266_post_10();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}
					
					ret = memcmp(USART2_RX_BUF, receive_data11, 7);
					if(ret==0){
            						
						esp8266_post_11(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}
					
					ret = memcmp(USART2_RX_BUF, receive_data12, 7);
					if(ret==0){	
            						
						esp8266_post_12();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}
		
					ret = memcmp(USART2_RX_BUF, receive_data13, 7);
					if(ret==0){			
						
						esp8266_post_13(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data14, 7);
					if(ret==0){			
						
						esp8266_post_14(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data15, 7);
					if(ret==0){			
						
						esp8266_post_15();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data16, 7);
					if(ret==0){			
						
						esp8266_post_16();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data17, 7);
					if(ret==0){			
						
						esp8266_post_17();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data18, 7);
					if(ret==0){			
						
						esp8266_post_18(); 
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data19, 7);
					if(ret==0){			
						
						esp8266_post_19();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data20, 7);
					if(ret==0){			
						
						esp8266_post_20();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}		
					
					ret = memcmp(USART2_RX_BUF, receive_data21, 7);
					if(ret==0){			
						
						esp8266_post_21();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
					ret = memcmp(USART2_RX_BUF, receive_data22, 7);
					if(ret==0){			
						
						esp8266_post_22();
            memset(USART2_RX_BUF, 0, sizeof(USART2_RX_BUF));						
					}	
					
		
		}    
    
}
