#include "includes.h"

void initIo(void)
{
	P2DIR |= 0x08; //output, backlight
	P3DIR |= 0x10; // beep

	P4DIR |= 0x08; //5V电源使能
	P4OUT |= 0x08;

	P1DIR |= 0x40; //output, backlight
	P4OUT |= 0x40;
	P3DIR |= 0xe0; //output, backlight
	P3OUT |= 0xe0;
	P4DIR |= 0x10; //output, backlight
	P4OUT |= 0x10;

}

void backLight(uchar onOff)
{
	if (onOff == ON) {
		P2OUT |= 0x08;
	} else {
		P2OUT &= ~0x08;
	}
}

void beep(uchar onOff)
{
	if (onOff == ON) {
		P3OUT |= 0x10;
	} else {
		P3OUT &= ~0x10;
	}
}

