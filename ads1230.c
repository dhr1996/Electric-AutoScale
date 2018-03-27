#include "includes.h"

extern void delayms(uint ms);
extern void hex2Ascii(uchar *pHex, uchar len, uchar *pAsc);

//SCLK: P3.3
//DOUT: P3.2
//PDWN: P3.0
//SPEED:P2.0
#define CLK_HIGH()  {P3OUT |=  0x08;}
#define CLK_LOW()   {P3OUT &= ~0x08;}
#define PDWN_HIGH() {P3OUT |=  0x01;}
#define PDWN_LOW()  {P3OUT &= ~0x01;}
#define SPEED_LOW() {P2OUT &= ~0x01;}
#define SPEED_HIGH(){P2OUT |=  0x01;}

#define DOUT        ((P3IN & 0x04)>>2)
#define NOP         __no_operation

#define DELAY1US() {uint i = 1; while (--i);}
#define ADS_CLK() {CLK_HIGH(); DELAY1US();CLK_LOW(); DELAY1US();}

uchar ADS1232_CAL(void)
{
	uchar i;

	while (DOUT);
	for (i=0; i<26; i++) {
		ADS_CLK();
	}
	
	return SUCCESS;
}

/************读取一次ADS1232数据***********/
ulong ADS1232_Read(void)  
{
	uchar i;
    ulong ulAD = 0x00000000;
	
	for (i=0; i<20; i++) {  
		ADS_CLK();
		ulAD <<= 1;
		if (DOUT) {
			ulAD |= 0x00000001;
		}
	}
	ADS_CLK();
	ADS_CLK();
	ADS_CLK();
	ADS_CLK();
	//ulAD ^= 0x080000;	
	return ulAD;
}

void initAD(void)
{
	
	P3DIR |=  0x09; //0,3      --output
	P3DIR &= ~0x04; //2, Dout  --input
	P2DIR |=  0x01; //speed    --output

	PDWN_HIGH();
	SPEED_LOW(); //SPEED_HIGH();
	CLK_LOW();
	PDWN_LOW();
	delayms(1);
	PDWN_HIGH();
	
	ADS1232_CAL();
}

uchar ADRead(ulong *ad) 
{
	if (DOUT) {
		return FAIL;
	}
	
	*ad = ADS1232_Read();
	return SUCCESS;
}

void adTest(void)
{
	ulong ulAD, ulDat, ulLastAD, ulFilter;
	uchar ucRet;
	uchar buf[16];
	uchar cnt = 0;
	uchar i;

	while (1) {		
		if (readKey() != KEY_NULL) {  //任意按键按下，则退出
			break;
		}
		
		//读取一个AD，然后发送到串口
		ucRet = ADRead(&ulAD);		
		if (ucRet == SUCCESS) {
			if (++cnt < 4) {
				//continue;
			}
			cnt = 0;
			
			//ulAD >>= 2;			
			//ulFilter = (ulAD + 3*ulLastAD)/4;
			ulFilter = ulAD;
			 
			buf[0] = ulFilter/100000 + '0';
			ulDat  = ulFilter%100000;
			buf[1] = ulDat/10000 + '0';
			ulDat  = ulFilter%10000;
			buf[2] = ulDat/1000 + '0';
			ulDat  = ulFilter%1000;
			buf[3] = ulDat/100 + '0';
			ulDat  = ulFilter%100;
			buf[4] = ulDat/10 + '0';
			ulDat  = ulFilter%10;
			buf[5] = ulDat + '0';
			buf[6] = '\x0d';
			buf[7] = '\x0a';
#ifdef _TEST_BY_UART			
			writeUart(buf, 8);
#else
			for (i=0; i<5; i++) {    //去掉前导0
				if (buf[i] == '0') {
					buf[i] = ' ';
				} else {
					break;
				}
			}
			buf[6] = '\x0';	
			display(buf);
#endif

			ulLastAD = ulAD;
		}
	}
}

