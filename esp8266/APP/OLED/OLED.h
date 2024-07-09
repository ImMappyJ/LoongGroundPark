#ifndef __OLED_H
#define __OLED_H
#include "OLED_2.h"
#include "OLED_3.h"

extern const unsigned char  picture_tab[]; 
extern const unsigned char  *point;

void IO_init(void);
void OLED_clear(void);
void OLED_full(void);
void OLED_init(void);
void Picture_display(const unsigned char *ptr_pic);
void Picture_ReverseDisplay(const unsigned char *ptr_pic);
void OLED_Show_number(u8 x,u8  y,u8  number );
void OLED_Show_chinese(u8 x,u8  y,u8  number );
void OLED_Show_string(u8 x,u8  y,u8  number );
void OLED_Show_picture(u8 x,u8  y,u8  number );

#endif
