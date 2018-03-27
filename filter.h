#ifndef		__FILTER_H__
#define		__FILTER_H__

extern bit flgpower;//cxr 2008.8.13
extern bit  flgwd/*AD内码稳定值*/;
extern float 	 zerob,/*开机零点内码*/
		 zeroc,/*按键零点内码*/
		 ad_20;

extern float    point[4];/*校准4个内码值*/

extern float    ad_1d;

uchar filter();
void sznb_initial();


#endif
