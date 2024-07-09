#ifndef __OLED_H
#define __OLED_H

extern const unsigned char  picture_tab1[]; 
extern const unsigned char  *point1;

void IO_init1(void);
void OLED_clear1(void);
void OLED_full1(void);
void OLED_init1(void);
void Picture_display1(const unsigned char *ptr_pic);
void Picture_ReverseDisplay1(const unsigned char *ptr_pic);
void OLED_Show_number1(u8 x,u8  y,u8  number );
void OLED_Show_chinese1(u8 x,u8  y,u8  number );
void OLED_Show_string1(u8 x,u8  y,u8  number );
void OLED_Show_picture1(u8 x,u8  y,u8  number );

#endif
