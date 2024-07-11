#include "usart.h"
#include "SysTick.h"
#include "esp8266.h"



int main(void)
{		
	  SysTick_Init(72);
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  
    USART1_Init(115200);
	  USART2_Init(9600);
	
    esp8266_start_post();
	  
    while(1){

			read_data(1);
			Analysis_data();
			delay_ms(600);		
		
		}    
    
}
