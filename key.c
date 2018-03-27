#include "includes.h"

uchar gJmpKeyVal = KEY_NULL;

extern void hex2Ascii(uchar *pHex, uchar len, uchar *pAsc);
extern uchar gbPowerOn;

const uchar keyTable[] = {
	0x01, 0x11, 0x31, 0x71, 
	0x02, 0x12, 0x32, 0x72,
	0x74, 0x78, 0x04, 0x14,
	0x34, 0x08, 0x18, 0x38,
	POWER_KEY
};

const uchar *pKeyStr[] = {
	"     7",	"     8",	"   IMR",	"     5",
	"     6",	"    SF",	"  CONT",	"     3",
	"     4",	"   COD",	"    T1",	"     1",
	"     2",	"     9",	"     0",	"    T2",
	POWER_KEY_STR,
	"      "
};

ulong gulKeyBits;

//P1.4~1.7, P2.4~2.7, P1.2 --IO
void initKey(void)
{
	P1SEL &= 0x0f; //io
	P2SEL &= 0x0f;
	P1SEL &= ~0x04; 

	P1DIR &= ~0x04;
	
	P1REN &= 0x0f;
	P2REN |= 0xf0; //pull up
	
}

uchar getCurKeyVal(void)
{
	uchar c,l;
	uchar keyVal = KEY_NULL;
	
	P1DIR |= 0xf0; //out
	P2DIR &= 0x0f; //in

	P1OUT &= 0x0f; //out--0
	l      = P2IN & 0xf0;
	if (l != 0xf0) {
		P1DIR &= 0x0f;
		P2DIR |= 0xf0;
		P2OUT |= 0xf0; //out --1
		c = P1IN & 0xf0;
		if (c != 0) {
			keyVal = (c) + (~l>>4);
		}
	}

	if ((P1IN & 0x04) == 0x00) {
		keyVal = POWER_KEY;
	}

	return keyVal;
}

uchar readKey(void)
{
	uchar keyVal = KEY_NULL;
	
	keyVal = getCurKeyVal();
	
	if (keyVal != KEY_NULL) {
		delayms(30);
		if (getCurKeyVal() != keyVal) {
			return KEY_NULL;
		}
		
		if ((gJmpKeyVal == KEY_NULL) ||(gJmpKeyVal != keyVal)){			
			gJmpKeyVal = keyVal;
		} else {
			keyVal = KEY_NULL;
		}
	} else {
		gJmpKeyVal = KEY_NULL;
	}

	if ((keyVal != KEY_NULL) && gbPowerOn) {
		beep(ON);
		delayms(50);
		beep(OFF);
	}
	
	return keyVal;
}

#ifdef _TEST_BY_UART
void keyTest(void)
{
	uchar lastKey = KEY_NULL;
	uchar keyVal = KEY_NULL;
	uchar buf[4];
	extern void delayms(uint ms);
	
	buf[2] = '\x0d';
	buf[3] = '\x0a';

	while (1) {
		delayms(100);
		keyVal = readKey();
		if (keyVal != KEY_NULL) {
			hex2Ascii(&keyVal, 1, buf);
			writeUart(buf, 4);
			if (keyVal == lastKey) {  //双击按键，退出
				break;
			}
			lastKey = keyVal;
		} else {
			if ((P1IN & 0x04) == 0x00) {
				buf[0] = 'O';
				buf[1] = 'N';
				writeUart(buf, 4);
				while (!(P1IN & 0x04));
			}
		}
		
	}	
}
#else
uchar whichKey(uchar keyVal)
{
	uchar i; 

	for (i=0; i<sizeof(keyTable); i++) {
		if (keyVal == keyTable[i]) {
			break;
		}
	}
	return i;	
}

void keyTest(void)
{
	uchar keyVal = KEY_NULL;

	gulKeyBits = 0;
	while (1) {
		delayms(30);
		keyVal = readKey();
		if (keyVal != KEY_NULL) {
			gulKeyBits |= (1UL<<whichKey(keyVal));
			display(pKeyStr[whichKey(keyVal)]);
			if (gulKeyBits == 0x1FFFF) {  //所有按键都按过后，退出
				delayms(700);
				break;
			}
			
		}		
	}	
}
#endif
void key_init()
	{
		kval=0.0;
		kindex=0x80;
	}

void key_end()
{
		kval=0.0;
		kindex=0;
}

bit key_status()
	{
		if(kindex&0x80) return 1;
		else return 0;
	}

void key_process(unsigned char dat)
	{
		float weigh ;
		unsigned char 	i;
	
		if((dat==KEY_POINT)&&(kindex&0x7f)==0)
		  {
			kindex++;
			return;
		   }
		if(dat<KEY_0||dat>KEY_9) return;
	
		if((kindex&0x7f)==0)
			kval=kval*10+(dat-'0');
		else
		{
			weigh=1.0;
			for(i=0; i<(kindex&0x7f); i++)
				weigh=weigh/10.0;
			kval=kval+weigh*(dat-'0');
			kindex++;		  
		}	   
}

