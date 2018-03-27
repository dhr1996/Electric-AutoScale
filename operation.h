#ifndef		__OPERATION_H__
#define		__OPERATION__

//$$$$$$$$$$$$$$$$$$$$$$$$ 24C01存储空间定义 $$$$$$$$$$$$$$$$$$$$$$
#define CHIP1_CONFIG	 0  /*精度设置*/
#define CHIP1_AD_CON     1  /*校准内码值（1~16)*/
	
#define CHIP1_PRICE_DOT_SWITCH     30 //单价显示小数点开关   2009-7-9 xp
	
	
#define CHIP2_PRICE      0  /*单价小数点*/
#define CHIP2_TOTAL      1  /*总价小数点*/
#define CHIP2_FILTER     2  /*滤波参数*/
#define CHIP2_UNIT_SYS   3  /*价格模式*/
#define CHIP2_SIN_DBL    4  /*单双量程*/
#define CHIP2_EC         5  /*背光设置*/
#define CHIP2_BAUD       6  /*波特率*/
#define CHIP2_SERIES     7  /*通讯方式*/
#define CHIP2_UNIT_PRICE 8  /*价格单位开关*/
#define CHIP2_UNITS      9  /*前次状态标志*/
#define CHIP2_SET_PRICE  10 /*是否允许单价存储*/

#define CHIP3_DOT_SIGN   60
//$$$$$$$$$$$$$$$$$$$$$$$$ 24C01参数定义 $$$$$$$$$$$$$$$$$$$$$$
#define SERIES_CONTINUE 0x0
#define SERIES_STABLE	0x1
#define SERIES_OFF   	0x2

#define BACKLIGHT_AUTO	0x0
#define BACKLIGHT_OFF	0x1
#define BACKLIGHT_ON	0x2
#define BACKLIGHT_HNAD  0x3

#define weight_sin      0x0
#define weight_dbl      0x1
 enum
{
	CHAR_0,
	CHAR_1,
	CHAR_2 ,
	CHAR_3 ,
	CHAR_4 ,
	CHAR_5 ,
	CHAR_6 ,
	CHAR_7 ,
	CHAR_8 ,
	CHAR_9 ,
	CHAR_A ,
	CHAR_B ,
	CHAR_C ,
	CHAR_D ,
	CHAR_E ,
	CHAR_F ,
	CHAR_BLANK,
	CHAR_MINUS,
	CHAR_MINUSN,
	CHAR_G,
	CHAR_H ,
	CHAR_I ,
	CHAR_J ,
	CHAR_K ,
	CHAR_L ,
	CHAR_M ,
	CHAR_N ,
	CHAR_O ,
	CHAR_P ,
	CHAR_H_ ,
	CHAR_R,
	CHAR_S ,
	CHAR_T,
	CHAR_U ,
	CHAR_V ,
	CHAR_W ,
	CHAR_co ,
	CHAR_X ,
	CHAR_Y ,
	CHAR_Z ,

};

extern unsigned char sys;/*状态模式*/

extern unsigned char 
    timer,/*定时总时间*/
    timer_price/*按键按下后定时时间*/,
    timer_ec,
    timer_bs,
    zero_num/*零点跟踪*/;
//*按键相关：*//
extern unsigned char kindex/*指示按键状况*/;
extern float kval/*按键值*/;

extern float flt;
extern float kzng;/*去皮值*/
extern unsigned char pass_num;

extern bit flgflj;
extern bit  flag_print;
extern unsigned char disp[20];

void clrdisp(uchar dat);

void default_EPROM();
void keybord();
void monito();

#endif

