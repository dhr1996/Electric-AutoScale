#ifndef		__WEIGHT_H__
#define		__WEIGHT_H__

extern bit flgovv;/*重量溢出标志*/
extern bit flgzero;/*重量零点标志*/

extern float  cl;/*称量值*/

extern float  ljsum;/*累计总数*/
extern bit flgljnum;
extern bit flgljsum;
extern unsigned char ljnum;/*累计次数*/

float absolute(float dat);
float scale(unsigned char sel_zero);
void judge_process();
void jeval_output(float dat);
float disp_weight(float dat);
void lj_adding(float dat);

#endif

