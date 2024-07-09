
/********************?eòY3?**************************±?1??????éSDA,SCKò??ú??é?à-µ?×è??
*****************1.3  4PIN IIC OLED FOR STM32F103*************
*****STM32F103?y?¯**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    
***** BY:GU 
********************************************************/


#include "stm32f10x.h"
#include "delay.h"
#include "OLED_2.h"
#include "OLEDFONT_2.h"

#define OLED_FONT_12  12
#define OLED_FONT_16  16
#define OLED_FONT_24  24

#define OLED_MODE_FILLED    1
#define OLED_MODE_NO_FILLED 0

/**********SPIòy??·?????á??óoled?á???ü??êµ?ê?é??DT??*********/

#define IIC_SCK_PIN 5
#define IIC_SDA_PIN 6

#define OLED_COLUMN_NUMBER 128
#define OLED_LINE_NUMBER 64
#define OLED_COLUMN_OFFSET 2
#define OLED_PAGE_NUMBER OLED_LINE_NUMBER/8
/**********SPIòy??·?????á??óoled?á???ü??êµ?ê?é??DT??*********/

#define IIC_SCK_0  GPIOA->BRR=0X0020       // éè??sck?ó?úµ?PB5   ??á?
#define IIC_SCK_1  GPIOA->BSRR=0X0020       //????
#define IIC_SDA_0  GPIOA->BRR=0X0040       // éè??SDA?ó?úµ?PB6
#define IIC_SDA_1  GPIOA->BSRR=0X0040

const unsigned char  *point1;
unsigned char ACK1=0;
const unsigned char  OLED_init_cmd1[25]=			//SH1106
{
  
  /*0xae,0X00,0X10,0x40,0X81,0XCF,0xff,0xa1,0xa4,
  0xA6,0xc8,0xa8,0x3F,0xd5,0x80,0xd3,0x00,0XDA,0X12,
  0x8d,0x14,0xdb,0x40,0X20,0X02,0xd9,0xf1,0xAF*/
       0xAE,//1?±???ê?
	
       0xD5,//éè??ê±?ó·??µòò×ó,?eµ'?µ?ê
       0x80,  //[3:0],·??µòò×ó;[7:4],?eµ'?µ?ê

       0xA8,//éè???y?¯?·êy
       0X3F,//??è?(1/64)
	
       0xD3,//éè????ê???ò?
       0X00,//??è??a0
	
       0x40,//éè????ê??aê?DD [5:0],DDêy.
	
       0x8D,//µ?oé±?éè??
       0x14,//bit2???a??/1?±?
       0x20,//éè???ú'?µ??·??ê?
       0x02,//[1:0],00??áDµ??·??ê?;01??DDµ??·??ê?;10,ò3µ??·??ê?;??è?10;
       0xA1,//?????¨ò?éè??,bit0:0,0->0;1,0->127;  A1
	
       0xC8,//éè??COMé¨?è·??ò;bit3:0,??í¨??ê?;1,???¨ò???ê? COM[N-1]->COM0;N:?y?¯?·êy (C0 ·-×a??ê?) C8
	   
       0xDA,//éè??COMó2?tòy??????
       0x12,//[5:4]????  
	   
       0x81,//??±è?èéè??
       0x66,//1~255;??è?0X7F (áá?èéè??,??'ó??áá)
	   
       0xD9,//éè???¤3?µ??ü?ú
       0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
	   
       0xDB,//éè??VCOMH µ??1±??ê
       0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	   
       0xA4,//è?????ê??a??;bit0:1,?a??;0,1?±?;(°×?á/oú?á)
	   
       0xA6,//éè????ê?·?ê?;bit0:1,·'?à??ê?;0,?y3???ê? 
       
       0xAF,//?a????ê?     
};

const unsigned char  picture_tab1[]={
/*------------------------------------------------------------------------------
;  ?'???t / ??×? : C:\Documents and Settings\Administrator\×à??\D??¨???t?D (2)\logo.bmp×???
;  ?í?á???¨??????: 128?á64
------------------------------------------------------------------------------*/
//0x80,0x40,0x10,//?íµ?????êy,??µ?????êy???íµ?×??úêy??2?êyéè???é??
0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x00,0x80,0xE1,0xFF,0xFF,0x87,0x21,0x00,0x00,0x84,
0x21,0x00,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0xE0,0x01,0x84,0x21,0x80,0x01,0x84,
0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,
0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,
0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0x80,0x01,0x84,0x21,0x80,0x03,0x84,
0x21,0xF8,0x1F,0x84,0x21,0x00,0x00,0x84,0xE1,0xFF,0xFF,0x87,0x01,0x00,0x00,0x80,
0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,
0x01,0x00,0x30,0x80,0x01,0x00,0x18,0x80,0x01,0x00,0x1C,0x80,0x01,0x00,0x0E,0x80,
0x01,0x80,0x07,0x80,0x01,0xC0,0x03,0x80,0x01,0xE0,0x01,0x80,0x01,0xF0,0x00,0x80,
0x01,0x78,0x00,0x80,0x01,0x3C,0x00,0x80,0x01,0x3E,0x00,0x80,0x01,0x3E,0x00,0x80,
0x01,0xFE,0xFF,0x80,0x01,0xFE,0xFF,0x80,0x01,0xFE,0xFF,0x80,0x01,0x00,0xFC,0x80,
0x01,0x00,0xFC,0x80,0x01,0x00,0x3C,0x80,0x01,0x00,0x1E,0x80,0x01,0x00,0x0F,0x80,
0x01,0x80,0x07,0x80,0x01,0xC0,0x03,0x80,0x01,0xE0,0x01,0x80,0x01,0x70,0x00,0x80,
0x01,0x38,0x00,0x80,0x01,0x18,0x00,0x80,0x01,0x0C,0x00,0x80,0x01,0x00,0x00,0x80,
0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,
0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0x01,0x00,0x00,0x80,0xFF,0xFF,0xFF,0xFF,

};


/*******ê±?ó3?ê??¯******************/
void SYS_init1(unsigned char PLL)
{
	
		 
	RCC->APB1RSTR = 0x00000000;//?'???áê?			 
	RCC->APB2RSTR = 0x00000000; 	  
  	RCC->AHBENR = 0x00000014;  //?¯????ê?éá'?oíSRAMê±?óê1?ü.????1?±?.	  
  	RCC->APB2ENR = 0x00000000; //íaéèê±?ó1?±?.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ê1?ü?ú2????ùê±?óHSION
	
	RCC->CFGR &= 0xF8FF0000;   //?'??SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //?'??HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //?'??HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //?'??PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	while(((RCC->CFGR>>2)& 0x03 )!=0x00); 	
	RCC->CIR = 0x00000000;     //1?±??ùóD?D??		 
	//?????òá?±í				  
  
//	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);//éè??NVICµ??òá?±í??ò???'??÷
	
 	RCC->CR|=0x00010000;  //ía2????ùê±?óê1?üHSEON
	while(((RCC->CR>>17)&0x00000001)==0);//µè'yía2?ê±?ó?íD÷
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//µ???2??µ???
	RCC->CFGR|=PLL<<18;   //éè??PLL?µ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//µè'yPLL???¨
	RCC->CFGR|=0x00000002;//PLL×÷?a?µí3ê±?ó	 
	while(((RCC->CFGR>>2)&0x03)!=0x02);   //µè'yPLL×÷?a?µí3ê±?óéè??3é1|
	
	
}

void IO_init1(void)
{	  GPIO_InitTypeDef     GPIO_InitStructure;
//	RCC->APB2ENR|=1<<3;    //ê1?üPORTBê±?ó 
	
//	GPIOB->CRL&=0X00FFFFFF;				//??B56?ú?????aí¨ó??a??ê?3?,×?'ó50MH

	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIOB->CRL|=0X07700000;				//B7?????aí¨ó?í?íìê?3?,×?'ó50MH
//		
//	GPIOB->ODR=0XFFFF;
}

/**************************IIC???é·??ío¯êy************************************************

 *************************************************************************/
//D'è?  ×?oó??SDAà-????ò?µè'y'óéè±?2úéúó|'e
void IIC_write1(unsigned char date)
{
	unsigned char i, temp;
	temp = date;
			
	for(i=0; i<8; i++)
	{	IIC_SCK_0;
		
        if ((temp&0x80)==0)
            IIC_SDA_0;
        else IIC_SDA_1;
		temp = temp << 1;
		delay_us(1);			  
		IIC_SCK_1;
		delay_us(1);
		
	}
	IIC_SCK_0;
	delay_us(1);
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
//								2?Dèòaó|'e
//	if (READ_SDA==0)
//		ACK1 = 1;
//	else ACK1 =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
	

}
//???¯D?o?
//SCL?ú??µ????ú????SDAóé??µ????òµíµ???µ?±??¯?¨ò??a???¯D?o?
void IIC_start1()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //?ùóD2ù×÷?áê?êí·?SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
        IIC_write1(0x78);
        
}

//í??1D?o?
//SCL?ú??µ????ú????SDAóéµíµ????ò??µ???µ?±??¯?¨ò??aí??1D?o?
void IIC_stop1()
{
	IIC_SDA_0;
	delay_us(1);
	IIC_SCK_1;
	delay_us(3);
	IIC_SDA_1;
	
}

void OLED_send_cmd1(unsigned char o_command)
  {
    
    IIC_start1();
    IIC_write1(0x00); 
    IIC_write1(o_command);
    IIC_stop1();
    
  }
void OLED_send_data1(unsigned char o_data)
  { 
    IIC_start1();
    IIC_write1(0x40);
    IIC_write1(o_data);
    IIC_stop1();
   }
void Column_set1(unsigned char column)
  {
	column+=OLED_COLUMN_OFFSET;
    OLED_send_cmd1(0x10|(column>>4));    //éè??áDµ??·????
    OLED_send_cmd1(0x00|(column&0x0f));   //éè??áDµ??·µí??  
    	 
  }
void Page_set1(unsigned char page)
  {
    OLED_send_cmd1(0xb0+page);
  }
void OLED_clear1(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
          Page_set1(page);
          Column_set1(0);	  
          for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
            {
              OLED_send_data1(0x00);
            }
      }
  }
void OLED_full1(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
        Page_set1(page);
        Column_set1(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data1(0xff);
          }
      }
  }
void OLED_init1(void)
  {
    unsigned char i;
    for(i=0;i<25;i++)
      {
        OLED_send_cmd1(OLED_init_cmd1[i]);
      }
  }

void Picture_display1(const unsigned char *ptr_pic)
  {
    unsigned char page,column;
    for(page=0;page<(OLED_LINE_NUMBER/8);page++)        //page loop
      { 
	Page_set1(page);
	Column_set1(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data1(*ptr_pic++);
          }
      }
  }
void Picture_ReverseDisplay1(const unsigned char *ptr_pic)
{
    unsigned char page,column,data;
    for(page=0;page<(OLED_LINE_NUMBER/8);page++)        //page loop
      { 
	Page_set1(page);
	Column_set1(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            data=*ptr_pic++;
            data=~data;
            OLED_send_data1(data);
          }
      }
  }

/**
  * @brief  OLED_SetPos,éè??1a±ê
  * @param   x,1a±êx???? ·??§ 0-128
	*		       y,1a±êy???? ·??§ 0-7
  * @retval ?T
  */
void OLED_SetPos1(unsigned char x, unsigned char y) //???????
{
	OLED_send_cmd1(0xb0+y);

	OLED_send_cmd1(((x&0xf0)>>4)|0x10);  //???????? ?????
	OLED_send_cmd1((x&0x0f)|0x01);
}
/**
  * @brief  OLED_Show_Number_16,??ê?êy×?,êy×?'óD?16*16
  * @param  x,1a±êx???? ·??§ 0-8
	*		      y,1a±êy???? ·??§ 0-7
	*		    number Dèòa??ê?µ?êy×???·??§0-99
  * @retval ?T
  */
void  OLED_Show_number1(u8 x,u8  y,u8  number )
{
	uint32_t i=0;
	if(number>9){
	OLED_SetPos1(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(number_array1[number/10*16+i]);
	}
	OLED_SetPos1(15*(x-1)+1,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(number_array1[number/10*16+i]);
	}
	OLED_SetPos1(15*(x-1)+1+16,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(number_array1[number%10*16+i]);
	}
	OLED_SetPos1(15*(x-1)+1+16,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(number_array1[number%10*16+i]);
	}
	}
	if(number<9){
		OLED_SetPos1(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(number_array1[number*16+i]);
	}
		OLED_SetPos1(15*(x-1)+1,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(number_array1[number*16+i]);
	}
		
	}
}

void OLED_Show_chinese1(u8 x,u8  y,u8  number )
{
	uint32_t i=0;
	OLED_SetPos1(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(chinese_array1[number*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(chinese_array1[number*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(chinese_array1[number*2+1][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(chinese_array1[number*2+1][i]);
	}
}

void OLED_Show_string1(u8 x,u8  y,u8  number )
{
		uint32_t i=0;
	OLED_SetPos1(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(string_array1[number*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(string_array1[number*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(string_array1[number*2+1][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(string_array1[number*2+1][i]);
	}
}

void OLED_Show_picture1(u8 x,u8  y,u8  number)
{
	uint32_t i=0,j=(number-1)*8;

	OLED_SetPos1(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	j++;
		OLED_SetPos1(15*(x+1-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	
	j++;
		OLED_SetPos1(15*(x-1)+1,y+1-1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y+1-1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1,y+1-1+1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y+1-1+1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	
j++;
		OLED_SetPos1(15*(x+1-1)+1,y+1-1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y+1-1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1,y+1-1+1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y+1-1+1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	
		j++;
		OLED_SetPos1(15*(x-1)+1,y+1+1-1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y+1+1-1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1,y+1+1-1+1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y+1+1-1+1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	
			j++;
		OLED_SetPos1(15*(x+1-1)+1,y+1+1-1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y+1+1-1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1,y+1+1-1+1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y+1+1-1+1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	
			j++;
		OLED_SetPos1(15*(x-1)+1,y+1+1+1-1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y+1+1+1-1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x-1)+1,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x-1)+1+8,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	
				j++;
		OLED_SetPos1(15*(x+1-1)+1,y+1+1+1-1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y+1+1+1-1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
	OLED_SetPos1(15*(x+1-1)+1+8,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data1(picture_arrar1[j*2+1][i]);
	}
}
