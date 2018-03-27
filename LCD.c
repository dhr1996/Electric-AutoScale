//*****************************************************************************
//  LCD, Displays Numbers on a 2-Mux LCD
//
//  ACLK = LFXT1 = 32768Hz, MCLK = SMCLK = default DCO = 32 x ACLK = 1048576Hz
//  //* An external watch crystal between XIN & XOUT is required for ACLK *//	
//
//                                 Connections MSP430 -> LCD
//                                 -------------------------
//         
//                           MSP430x44x MCU           2 mux LCD
//                                   
/* ��������: 
*      ��ʾ
*
* ע������:
*     ���������ʾ��Χ���򿳵���������ݣ�����Ҫ���Ե�
*     ����̫��Ϊ"12345678"�����������ʾ6λ�������ʾ"123456"
*
* ��ʷ��¼��
*     �޸���     ����           �汾               ��־
*      ��ƽ    2012-05-11     01-00-00            Create 
*
*****************************************************************************/
#include  "includes.h"


char* LCD = LCDMEM;
uchar gaucLcdBuf[LCD_SEG_NUM];
const uchar lcdTable[] = {
	0xED, 0x0C, 0x79, 0x3D, 0x9C, 0xB5, 0xF5, 0x2C, 0xFD, 0xBD, //'0' - '9'
	0xFC, 0xD5, 0xE1, 0x5D, 0xF1, 0xF0,                         //'A' - 'F'
	0x00, 0x00, 0x40, 0x00, 0xF4, 0xC1,0x64, //'G'-'M'
	0x54, 0x55, 0x00, 0x00, 0x50, 0xB4,0xD1, //'n'-'t'
	0xCD, 0x00, 0x00, 0x00, 0x9D, 0x00       //'U'-'Z'
};

uchar gLcdTestFinished = FALSE;

/******************************************************************************

******************************************************************************/
void  display(const char *pcFormat, ...)
{
	va_list ap;
	uchar   buf[20];
	uchar   i;
	uchar   dat;
	uchar   point = 0;	
	uchar  *pBuf = buf;
	
	memset(buf, 0x00, sizeof(buf)); //Ĭ��ȫ��Ϊ0��������ʾ

	//��ʽ�����͹������ⲿ��ʾ���ݣ����뻺����
	va_start(ap, pcFormat);				 
	vsprintf(buf, pcFormat, ap);
	va_end(ap);							 

	 //�γ���ʾ������
   	for (i=0; i<DIGIT_NUM; i++) {  
		dat = *pBuf++;
		if (dat == '.') {   //���֧��һ��С����
			dat = *pBuf++;
			point = i;

		}
		
		if (dat >= '0' && dat <= '9') {
			gaucLcdBuf[i] = lcdTable[dat - '0'];
		} else if(dat >= 'a' && dat <= 'z') {
			gaucLcdBuf[i] = lcdTable[dat - 'a'+10];
		} else if(dat >= 'A' && dat <= 'Z') {
			gaucLcdBuf[i] = lcdTable[dat - 'A'+10];
		} else{
			gaucLcdBuf[i] = 0x00;
		}
	}

	//���͵���ʾ��Ԫ
	for (i=0; i<LCD_SEG_NUM; i++) {
		if (i < DIGIT_NUM*2) {
			LCD[2*DIGIT_NUM-2-i] = ((gaucLcdBuf[i/2] & 0x30)|(gaucLcdBuf[i/2]>>6));
			LCD[2*DIGIT_NUM-1-i] = (((gaucLcdBuf[i/2]<<4) & 0x30)|((gaucLcdBuf[i/2]>>2)&0x03));			
			i++;
		} else {
			LCD[i] = 0x00;
		}
	}	

	if (point != 0){
		LCD[2*DIGIT_NUM+point-1] = 0x01;
	}
}

	
void initLcd(void)
{
	uchar i;
	
	LCDCTL = LCDSG0_6 + LCD2MUX + LCDON;	  // 2-Mux LCD, segments S0-S35
	BTCTL  = BT_fLCD_DIV128;				  // LCD clock freq is ACLK/128
	P5SEL  = 0xE4;							  // Select P5.2,5-7 as Com and Rxx

	//ȫ��
	for (i=0; i<LCD_SEG_NUM; i++) {        
	  LCD[i] = 0x00;
	}
}

//����FAIL�����������˳�
uchar delayExitByKey(uint uiMs)
{
	while (uiMs--) {
		if (readKey() != KEY_NULL) { //�а������£�����Ѿ�������һ�����˳�
			if (gLcdTestFinished == TRUE) {
			 	return FAIL;
			}
		}
		delayms(1);
	}
	return SUCCESS;
}

void lcdTest(void)
{
	uchar i;

	gLcdTestFinished = FALSE;
	while (1) {
	  	//clr display
		for (i=0; i<LCD_SEG_NUM; i++) {
			LCD[i] = 0;
		}

		for (i=0; i<LCD_SEG_NUM; i++){
		  LCD[i] = 0x01;
		  if (delayExitByKey(300) == FAIL) {
		   	  return;
		  }
		  
		  LCD[i] = 0x03;
		  if (delayExitByKey(300) == FAIL) {
		   	  return;
		  }

		  LCD[i] = 0x13;
		  if (delayExitByKey(300) == FAIL) {
		   	  return;
		  }

		  LCD[i] = 0x33;
		  if (delayExitByKey(300) == FAIL) {
		   	  return;
		  }

		}

		gLcdTestFinished = TRUE;
	}
}

