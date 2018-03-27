/******************************************************************************
*
*  
*
*
******************************************************************************/

#include "includes.h"

uchar gbPowerOn = 0;

#define MENU          "1.key 2.lcd 3.ad\x0d\x0a"
#define KEY_TEST_MENU "Enter key test, double click to exit...\x0d\x0a"
#define LCD_TEST_MENU "Enter lcd test, press any key to exit...\x0d\x0a"
#define AD_TEST_MENU  "Enter ad test, press any key to exit...\x0d\x0a"

void (* pc_0)(void);			/* 程序地址0000 */

void initSystem(void)
{
	uint i;
	
	WDTCTL = WDTPW + WDTHOLD;				  // Stop WDT
	FLL_CTL0 |= XCAP14PF;					  // Configure load caps
	for (i = 0; i < 10000; i++);			  // Delay for 32 kHz crystal to
	LCD_Init();									  // stabilize
	//initLcd();
	initIo();
	initAD();	
	//initUart();
	initKey();
	
}

void delayms(uint ms)
{
	int i;

	while (ms--) {
		i = 150;
		while (i--);
	}
}

//低字节最高位，是小端模式，和MCS51反了
void hex2Ascii(uchar *pHex, uchar len, uchar *pAsc)
{
	uchar i, j;
	uchar dat;

	for (i=0; i<len; i++) {
		j = len - 1 - i;
		dat = (pHex[j] & 0xf0)>>4;
		if (dat <= 9) {
			pAsc[2*i] = dat+'0';
		} else {
			pAsc[2*i] = dat + 0x37;
		}

		dat = (pHex[j] & 0x0f);
		if (dat <= 9) {
			pAsc[2*i+1] = dat+'0';
		} else {
			pAsc[2*i+1] = dat + 0x37;
		}
	}

}

void main(void)
{
	
	initSystem();
	
#ifndef _TEST_BY_UART
	display(" TEST ");
	delayms(2000);

	display("1.  key");
	delayms(1500);
	keyTest();

	display("2.  LCD");
	delayms(1500);
	lcdTest();

	display("3.   AD");
	delayms(1500);		
	adTest();

	
	//power off
	while (readKey() != POWER_KEY);	
	display("      ");	
	while (readKey() == POWER_KEY);  //wait the power key to release
	//reset
	pc_0 = 0;                         
	pc_0();
#else
        ;

	while (1)
	{
	 LCD_clear();
    LCD_Write_String(0, 0,"Value1:");
    LCD_Write_String(0, 1,"Value2:");
    LCD_Write_String(0, 2,"Value3:");
    LCD_Write_String(0, 3,"Value4:");
    LCD_Write_String(0, 4,"Pos   :");
    LCD_Write_String(0, 5,"Angle :");
	delayms(100);
   		judge_process();
    	keybord();
       	monito();
	}
#endif
}

