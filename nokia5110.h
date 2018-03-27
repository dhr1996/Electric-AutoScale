#ifndef _NOKIA5110_H_
#define _NOKIA5110_H_

//#include <hidef.h>      /* common defines and macros */
//#include "derivative.h"      /* derivative-specific definitions */

//#include "common.h"
//#include "gpio.h"



#define uchar unsigned char  //自己加的
#define uint unsigned int   //自己加的

//位操作定义
/*#define LCD_RST  PTB4_OUT 
#define LCD_CE   PTB5_OUT 
#define LCD_DC   PTB6_OUT 
#define SDIN     PTB7_OUT 
#define SCLK     PTC2_OUT */

/*#define LCD_RST  P1_6
#define LCD_CE   P3_6
#define LCD_DC   P3_5
#define SDIN     P3_7 
#define SCLK     P8_2 */

#define LCD_RST_1()  {P1OUT |=  0x40;}
#define LCD_RST_0()  {P1OUT &= ~0x40;}
#define LCD_CE_1()   {P3OUT |=  0x40;}
#define LCD_CE_0()   {P3OUT &= ~0x40;}
#define LCD_DC_1()   {P3OUT &= ~0x20;}
#define LCD_DC_0()   {P3OUT |=  0x20;}
#define SDIN_1()   {P3OUT |=  0x80;}
#define SDIN_0()   {P3OUT &= ~0x80;}
#define SCLK_1()   {P3OUT &= ~0x10;}
#define SCLK_0()   {P3OUT |=  0x10;}

#define LCD_RST  P3OUT |= 0x10;
//函数声明
void Delay_us(uint ut);
void LCD_Init(void);
void LCD_clear(void);
void LCD_write_byte(uchar, uchar);
void LCD_set_XY(uchar , uchar );      
void LCD_write_char(uchar );
void LCD_Write_Char(uchar ,uchar ,uchar);
void LCD_Write_Num(uchar ,uchar ,uint,uchar);
void LCD_write_english_string(uchar ,uchar ,char *); 
void LCD_write_chinese(uchar , uchar , char *);
void LCD_write_chinese_string(uchar , uchar ,char *);
void LCD_Write_String(uchar , uchar ,char *);
void LCD_draw_bmp_pixel(uchar ,uchar ,uchar *, uchar ,uchar );

#endif