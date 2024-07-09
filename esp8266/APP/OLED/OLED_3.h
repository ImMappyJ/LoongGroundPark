#ifndef __OLED_3_H
#define __OLED_3_H

extern const unsigned char  picture_tab2[]; 
extern const unsigned char  *point2;

void IO_init2(void);
void OLED_clear2(void);
void OLED_full2(void);
void OLED_init2(void);
void Picture_display2(const unsigned char *ptr_pic);
void Picture_ReverseDisplay2(const unsigned char *ptr_pic);
void OLED_Show_number2(u8 x,u8  y,u8  number );
void OLED_Show_chinese2(u8 x,u8  y,u8  number );
void OLED_Show_string2(u8 x,u8  y,u8  number );
void OLED_Show_picture2(u8 x,u8  y,u8  number );

#endif
