#ifndef		__OPERATION_H__
#define		__OPERATION__

//$$$$$$$$$$$$$$$$$$$$$$$$ 24C01�洢�ռ䶨�� $$$$$$$$$$$$$$$$$$$$$$
#define CHIP1_CONFIG	 0  /*��������*/
#define CHIP1_AD_CON     1  /*У׼����ֵ��1~16)*/
	
#define CHIP1_PRICE_DOT_SWITCH     30 //������ʾС���㿪��   2009-7-9 xp
	
	
#define CHIP2_PRICE      0  /*����С����*/
#define CHIP2_TOTAL      1  /*�ܼ�С����*/
#define CHIP2_FILTER     2  /*�˲�����*/
#define CHIP2_UNIT_SYS   3  /*�۸�ģʽ*/
#define CHIP2_SIN_DBL    4  /*��˫����*/
#define CHIP2_EC         5  /*��������*/
#define CHIP2_BAUD       6  /*������*/
#define CHIP2_SERIES     7  /*ͨѶ��ʽ*/
#define CHIP2_UNIT_PRICE 8  /*�۸�λ����*/
#define CHIP2_UNITS      9  /*ǰ��״̬��־*/
#define CHIP2_SET_PRICE  10 /*�Ƿ������۴洢*/

#define CHIP3_DOT_SIGN   60
//$$$$$$$$$$$$$$$$$$$$$$$$ 24C01�������� $$$$$$$$$$$$$$$$$$$$$$
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

extern unsigned char sys;/*״̬ģʽ*/

extern unsigned char 
    timer,/*��ʱ��ʱ��*/
    timer_price/*�������º�ʱʱ��*/,
    timer_ec,
    timer_bs,
    zero_num/*������*/;
//*������أ�*//
extern unsigned char kindex/*ָʾ����״��*/;
extern float kval/*����ֵ*/;

extern float flt;
extern float kzng;/*ȥƤֵ*/
extern unsigned char pass_num;

extern bit flgflj;
extern bit  flag_print;
extern unsigned char disp[20];

void clrdisp(uchar dat);

void default_EPROM();
void keybord();
void monito();

#endif

