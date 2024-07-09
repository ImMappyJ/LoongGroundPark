#include "stm32f10x.h"
#include "esp8266.h"
#include "string.h"
#include "usart.h"
#include "SysTick.h"

char* esp8266_check_cmd(char *str)
{
	char *strx = NULL;

	    printf("check USART_RX_BUF:%s\r\n", USART_RX_BUF);
		strx = strstr((const char*)USART_RX_BUF, (const char*)str);

	return strx;
}


char esp8266_send_cmd(char *cmd, char *ack, uint16_t waittime)
{
	char res = 0;
	USART_RX_STA = 0;

	if(ack && waittime)		
	{
		while(--waittime)	
		{

			delay_ms(300);

                
				if(esp8266_check_cmd(ack))
				{
					
					memset(USART_RX_BUF, 0, USART_REC_LEN);
					break;
				}

		}
		if(waittime == 0)
        {
            res = 1;
        }
        else ;
	}
	memset(USART_RX_BUF, 0, USART_REC_LEN);
	return res;
}


void esp8266_start_trans(void)
{
//    int ret = 1;
    
	printf("AT+CWMODE=1\r\n");
  delay_ms(100);
    
	printf("AT+RST\r\n");
  delay_ms(1000);
  delay_ms(1000);

	printf("AT+CWJAP=Redmi K40 Pro+,123456789\r\n");
  delay_ms(100);
    
	printf("AT+CIPMUX=0\r\n");
  delay_ms(100);
    
	printf("AT+CIPSTART=TCP,172.20.10.3,9988\r\n");

	printf("AT+CIPMODE=1\r\n");
    
	printf("AT+CIPSEND\r\n");

}

void esp8266_start_post()
{
//    int ret = 1;
	
	printf("AT\r\n");
  delay_ms(2000);

	printf("AT+RST\r\n");
  delay_ms(2000);
	
	printf("AT+RESTORE\r\n");
  delay_ms(2000);

	printf("AT+CWMODE=3\r\n");
  delay_ms(1000);

	printf("AT+CIPSNTPCFG=1,8,\"ntpl.aliyun.com\"\r\n");
	delay_ms(2000);
	
	printf("AT+CWJAP=\"test\",\"12345678\"\r\n");
  delay_ms(1000);

  printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"MainControl&k153zuyAMH6\",\"a21ac43a134f588965b223dfb36ed0720816da206a6a41bfc3b309745bcf1743\",0,0,\"\"\r\n");
	delay_ms(1000);

  printf("AT+MQTTCLIENTID=0,\"k153zuyAMH6.MainControl|securemode=2\\,signmethod=hmacsha256\\,timestamp=1720351236618|\"\r\n");
	delay_ms(1000);

	
   printf("AT+MQTTCONN=0,\"iot-06z00i2zvzet7ip.mqtt.iothub.aliyuncs.com\",1883,1\r\n");
   delay_ms(1000);

   printf("AT+MQTTSUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post_reply\",1\r\n");
   delay_ms(1000);

}

void esp8266_post_1(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":101}}\",1,0\r\n");
   
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_2(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":102}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_3(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":103}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_4(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":104}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_5(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":105}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_6(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":106}}\",1,0\r\n");
   
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_7(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":107}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_8(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":108}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_9(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":109}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_10(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":110}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}void esp8266_post_11(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":111}}\",1,0\r\n");
   
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_12(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":112}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_13(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":113}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_14(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":114}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_15(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":115}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}void esp8266_post_16(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":116}}\",1,0\r\n");
   
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_17(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":117}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_18(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":118}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_19(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":119}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
void esp8266_post_20(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":120}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}

void esp8266_post_21(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":121}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}

void esp8266_post_22(){
    printf("AT+MQTTPUB=0,\"/sys/k153zuyAMH6/MainControl/thing/event/property/post\",\"{\\\"params\\\":{\\\"num\\\":122}}\",1,0\r\n");
    memset(USART_RX_BUF, 0, USART_REC_LEN);
}
