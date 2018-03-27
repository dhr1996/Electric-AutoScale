
#include "includes.h"

//115200bps
void initUart(void)
{
	P4SEL  |= 0x03;							  // P4.0,1 = USART1 TXD/RXD

	UCTL1  |= SWRST;
	ME2    |= UTXE1 + URXE1;				  // Enabled USART1 TXD/RXD
	UCTL1  |= CHAR;							  // 8-bit character, SWRST = 1
	UTCTL1 |= SSEL1 + SSEL0 + URXSE;		  // UCLK = SMCLK, start edge detect
	UBR01   = 0x09;							  // 115200 from 1Mhz, 1048576/115200
	UBR11   = 0x00;
	UMCTL1  = 0x08;							  // Modulation
	UCTL1  &= ~SWRST;						  // Initialize USART state machine
	IE1    &= ~URXIE1;						  // DISABLE USART1 RX interrupt
}

uchar readUart(uchar *buf, uchar len, uchar *pLen)
{


	return 0;
}


uchar readUart1B(uchar *buf)
{
	uchar ucRet = 1;
	
	if (IFG2 & URXIFG1) {
		*buf = RXBUF1;
		ucRet = 0;
	}

	return ucRet;
}


uchar writeUart(uchar *buf, uchar len)
{
	uchar i;

	for (i=0; i<len; i++) {
		TXBUF1 = buf[i];
		while (!(IFG2 & UTXIFG1));	// USART0 TX buffer ready?
	}

	return 0;
}

void delay10us(uint ui10us)
{
	int i;

	while (ui10us--) {
		i = 2;
		while (i--);
	}
}

uchar uartTest(void)
{
	uchar TxBuf[256];
	uchar RxBuf[256];
	uint  i;

	memset(RxBuf, 0xff, sizeof(RxBuf));
	
	for (i=0; i<=0xff; i++) {
		TxBuf[i] = i;
		writeUart(TxBuf+i, 1);
		delay10us(2);           //wait cpu to receive the data
		readUart1B(RxBuf+i);
	}

	if (memcmp(TxBuf, RxBuf, sizeof(TxBuf)) == 0) {
		display("    OK");
		return 0;
	} else {
		display("  FAIL");
		return 1;
	}
}
