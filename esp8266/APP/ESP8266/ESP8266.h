#ifndef __ESP8266_H
#define __ESP8266_H

#include "esp8266.h"

char* esp8266_check_cmd(char *str);
char esp8266_send_cmd(char *cmd,char *ack,uint16_t waittime);
void esp8266_start_trans(void);
void esp8266_send_data(char *cmd);
void esp8266_start_post(void);

void esp8266_post_1(void);
void esp8266_post_2(void);
void esp8266_post_3(void);
void esp8266_post_4(void);
void esp8266_post_5(void);
void esp8266_post_6(void);
void esp8266_post_7(void);
void esp8266_post_8(void);
void esp8266_post_9(void);
void esp8266_post_10(void);
void esp8266_post_11(void);
void esp8266_post_12(void);
void esp8266_post_13(void);
void esp8266_post_14(void);
void esp8266_post_15(void);
void esp8266_post_16(void);
void esp8266_post_17(void);
void esp8266_post_18(void);
void esp8266_post_19(void);
void esp8266_post_20(void);
void esp8266_post_21(void);
void esp8266_post_22(void);

#endif
