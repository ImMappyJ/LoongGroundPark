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

#endif
