#ifndef		__FILTER_H__
#define		__FILTER_H__

extern bit flgpower;//cxr 2008.8.13
extern bit  flgwd/*AD�����ȶ�ֵ*/;
extern float 	 zerob,/*�����������*/
		 zeroc,/*�����������*/
		 ad_20;

extern float    point[4];/*У׼4������ֵ*/

extern float    ad_1d;

uchar filter();
void sznb_initial();


#endif
