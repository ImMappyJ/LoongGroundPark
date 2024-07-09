
/********************���ݳ�**************************����˾ģ��SDA,SCK�������������裬
*****************1.3  4PIN IIC OLED FOR STM32F103*************
*****STM32F103����**************************
***** PB5----3  SCK   ,  PB6----4  SDA   ,    
***** BY:GU 
********************************************************/


#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"
#include "OLEDFONT.h"

#define OLED_FONT_12  12
#define OLED_FONT_16  16
#define OLED_FONT_24  24

#define OLED_MODE_FILLED    1
#define OLED_MODE_NO_FILLED 0

/**********SPI���ŷ��䣬����oled��������ʵ������޸�*********/

#define IIC_SCK_PIN 5
#define IIC_SDA_PIN 6

#define OLED_COLUMN_NUMBER 128
#define OLED_LINE_NUMBER 64
#define OLED_COLUMN_OFFSET 2
#define OLED_PAGE_NUMBER OLED_LINE_NUMBER/8
/**********SPI���ŷ��䣬����oled��������ʵ������޸�*********/

#define IIC_SCK_0  GPIOB->BRR=0X0020       // ����sck�ӿڵ�PB5   ����
#define IIC_SCK_1  GPIOB->BSRR=0X0020       //��λ
#define IIC_SDA_0  GPIOB->BRR=0X0040       // ����SDA�ӿڵ�PB6
#define IIC_SDA_1  GPIOB->BSRR=0X0040

const unsigned char  *point;
unsigned char ACK=0;
const unsigned char  OLED_init_cmd[25]=			//SH1106
{
  
  /*0xae,0X00,0X10,0x40,0X81,0XCF,0xff,0xa1,0xa4,
  0xA6,0xc8,0xa8,0x3F,0xd5,0x80,0xd3,0x00,0XDA,0X12,
  0x8d,0x14,0xdb,0x40,0X20,0X02,0xd9,0xf1,0xAF*/
       0xAE,//�ر���ʾ
	
       0xD5,//����ʱ�ӷ�Ƶ����,��Ƶ��
       0x80,  //[3:0],��Ƶ����;[7:4],��Ƶ��

       0xA8,//��������·��
       0X3F,//Ĭ��(1/64)
	
       0xD3,//������ʾƫ��
       0X00,//Ĭ��Ϊ0
	
       0x40,//������ʾ��ʼ�� [5:0],����.
	
       0x8D,//��ɱ�����
       0x14,//bit2������/�ر�
       0x20,//�����ڴ��ַģʽ
       0x02,//[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
       0xA1,//���ض�������,bit0:0,0->0;1,0->127;  A1
	
       0xC8,//����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·�� (C0 ��ת��ʾ) C8
	   
       0xDA,//����COMӲ����������
       0x12,//[5:4]����  
	   
       0x81,//�Աȶ�����
       0x66,//1~255;Ĭ��0X7F (��������,Խ��Խ��)
	   
       0xD9,//����Ԥ�������
       0xf1,//[3:0],PHASE 1;[7:4],PHASE 2;
	   
       0xDB,//����VCOMH ��ѹ����
       0x30,//[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	   
       0xA4,//ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	   
       0xA6,//������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ 
       
       0xAF,//������ʾ     
};

const unsigned char  picture_tab[]={
/*------------------------------------------------------------------------------
;  Դ�ļ� / ���� : C:\Documents and Settings\Administrator\����\�½��ļ��� (2)\logo.bmp��ģ
;  ����ߣ����أ�: 128��64
------------------------------------------------------------------------------*/
//0x80,0x40,0x10,//���������,�ߵ�������������ֽ������������ÿ�ѡ
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


/*******ʱ�ӳ�ʼ��******************/
void SYS_init(unsigned char PLL)
{
	
		 
	RCC->APB1RSTR = 0x00000000;//��λ����			 
	RCC->APB2RSTR = 0x00000000; 	  
  	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	  
  	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION
	
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	while(((RCC->CFGR>>2)& 0x03 )!=0x00); 	
	RCC->CIR = 0x00000000;     //�ر������ж�		 
	//����������				  
  
//	SCB->VTOR = 0x08000000|(0x0 & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
	
 	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	while(((RCC->CR>>17)&0x00000001)==0);//�ȴ��ⲿʱ�Ӿ���
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	PLL-=2;//����2����λ
	RCC->CFGR|=PLL<<18;   //����PLLֵ 2~16
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
	while(((RCC->CFGR>>2)&0x03)!=0x02);   //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	
	
}

void IO_init(void)
{	  GPIO_InitTypeDef     GPIO_InitStructure;
//	RCC->APB2ENR|=1<<3;    //ʹ��PORTBʱ�� 
	
//	GPIOB->CRL&=0X00FFFFFF;				//��B56������Ϊͨ�ÿ�©���,���50MH

	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	GPIOB->CRL|=0X07700000;				//B7����Ϊͨ���������,���50MH
//		
//	GPIOB->ODR=0XFFFF;
}

/**************************IICģ�鷢�ͺ���************************************************

 *************************************************************************/
//д��  ���SDA���ߣ��Եȴ����豸����Ӧ��
void IIC_write(unsigned char date)
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
//								����ҪӦ��
//	if (READ_SDA==0)
//		ACK = 1;
//	else ACK =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
	

}
//�����ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��͵�ƽ�ı仯����Ϊ�����ź�
void IIC_start()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //���в��������ͷ�SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
        IIC_write(0x78);
        
}

//ֹͣ�ź�
//SCL�ڸߵ�ƽ�ڼ䣬SDA�ɵ͵�ƽ��ߵ�ƽ�ı仯����Ϊֹͣ�ź�
void IIC_stop()
{
	IIC_SDA_0;
	delay_us(1);
	IIC_SCK_1;
	delay_us(3);
	IIC_SDA_1;
	
}

void OLED_send_cmd(unsigned char o_command)
  {
    
    IIC_start();
    IIC_write(0x00); 
    IIC_write(o_command);
    IIC_stop();
    
  }
void OLED_send_data(unsigned char o_data)
  { 
    IIC_start();
    IIC_write(0x40);
    IIC_write(o_data);
    IIC_stop();
   }
void Column_set(unsigned char column)
  {
	column+=OLED_COLUMN_OFFSET;
    OLED_send_cmd(0x10|(column>>4));    //�����е�ַ��λ
    OLED_send_cmd(0x00|(column&0x0f));   //�����е�ַ��λ  
    	 
  }
void Page_set(unsigned char page)
  {
    OLED_send_cmd(0xb0+page);
  }
void OLED_clear(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
          Page_set(page);
          Column_set(0);	  
          for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
            {
              OLED_send_data(0x00);
            }
      }
  }
void OLED_full(void)
  {
    unsigned char page,column;
    for(page=0;page<OLED_PAGE_NUMBER;page++)             //page loop
      { 
        Page_set(page);
        Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(0xff);
          }
      }
  }
void OLED_init(void)
  {
    unsigned char i;
    for(i=0;i<25;i++)
      {
        OLED_send_cmd(OLED_init_cmd[i]);
      }
  }

void Picture_display(const unsigned char *ptr_pic)
  {
    unsigned char page,column;
    for(page=0;page<(OLED_LINE_NUMBER/8);page++)        //page loop
      { 
	Page_set(page);
	Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            OLED_send_data(*ptr_pic++);
          }
      }
  }
void Picture_ReverseDisplay(const unsigned char *ptr_pic)
{
    unsigned char page,column,data;
    for(page=0;page<(OLED_LINE_NUMBER/8);page++)        //page loop
      { 
	Page_set(page);
	Column_set(0);	  
	for(column=0;column<OLED_COLUMN_NUMBER;column++)	//column loop
          {
            data=*ptr_pic++;
            data=~data;
            OLED_send_data(data);
          }
      }
  }

/**
  * @brief  OLED_SetPos,���ù��
  * @param   x,���xλ�� ��Χ 0-128
	*		       y,���yλ�� ��Χ 0-7
  * @retval ��
  */
void OLED_SetPos(unsigned char x, unsigned char y) //???????
{
	OLED_send_cmd(0xb0+y);

	OLED_send_cmd(((x&0xf0)>>4)|0x10);  //???????? ?????
	OLED_send_cmd((x&0x0f)|0x01);
}
/**
  * @brief  OLED_Show_Number_16,��ʾ����,���ִ�С16*16
  * @param  x,���xλ�� ��Χ 0-8
	*		      y,���yλ�� ��Χ 0-7
	*		    number ��Ҫ��ʾ�����֣���Χ0-99
  * @retval ��
  */
void  OLED_Show_number(u8 x,u8  y,u8  number )
{
	uint32_t i=0;
	if(number>9){
	OLED_SetPos(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(number_array[number/10*16+i]);
	}
	OLED_SetPos(15*(x-1)+1,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(number_array[number/10*16+i]);
	}
	OLED_SetPos(15*(x-1)+1+16,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(number_array[number%10*16+i]);
	}
	OLED_SetPos(15*(x-1)+1+16,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(number_array[number%10*16+i]);
	}
	}
	if(number<9){
		OLED_SetPos(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(number_array[number*16+i]);
	}
		OLED_SetPos(15*(x-1)+1,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(number_array[number*16+i]);
	}
		
	}
}

void OLED_Show_chinese(u8 x,u8  y,u8  number )
{
	uint32_t i=0;
	OLED_SetPos(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(chinese_array[number*2][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(chinese_array[number*2][i]);
	}
	OLED_SetPos(15*(x-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(chinese_array[number*2+1][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(chinese_array[number*2+1][i]);
	}
}

void OLED_Show_string(u8 x,u8  y,u8  number )
{
		uint32_t i=0;
	OLED_SetPos(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(string_array[number*2][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(string_array[number*2][i]);
	}
	OLED_SetPos(15*(x-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(string_array[number*2+1][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(string_array[number*2+1][i]);
	}
}

void OLED_Show_picture(u8 x,u8  y,u8  number)
{
	uint32_t i=0,j=(number-1)*8;

	OLED_SetPos(15*(x-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	j++;
		OLED_SetPos(15*(x+1-1)+1,y-1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y-1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1,y-1+1+(y-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y-1+1+(y-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	
	j++;
		OLED_SetPos(15*(x-1)+1,y+1-1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y+1-1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1,y+1-1+1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y+1-1+1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	
j++;
		OLED_SetPos(15*(x+1-1)+1,y+1-1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y+1-1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1,y+1-1+1+(y+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y+1-1+1+(y+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	
		j++;
		OLED_SetPos(15*(x-1)+1,y+1+1-1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y+1+1-1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1,y+1+1-1+1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y+1+1-1+1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	
			j++;
		OLED_SetPos(15*(x+1-1)+1,y+1+1-1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y+1+1-1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1,y+1+1-1+1+(y+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y+1+1-1+1+(y+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	
			j++;
		OLED_SetPos(15*(x-1)+1,y+1+1+1-1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y+1+1+1-1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x-1)+1,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x-1)+1+8,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	
				j++;
		OLED_SetPos(15*(x+1-1)+1,y+1+1+1-1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y+1+1+1-1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2][i]);
	}
	OLED_SetPos(15*(x+1-1)+1,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=0;i<8;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
	OLED_SetPos(15*(x+1-1)+1+8,y+1+1+1-1+1+(y+1+1+1-1));
	for(i=8;i<16;i++)
	{
		OLED_send_data(picture_arrar[j*2+1][i]);
	}
}
