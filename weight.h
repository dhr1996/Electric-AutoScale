#ifndef		__WEIGHT_H__
#define		__WEIGHT_H__

extern bit flgovv;/*���������־*/
extern bit flgzero;/*��������־*/

extern float  cl;/*����ֵ*/

extern float  ljsum;/*�ۼ�����*/
extern bit flgljnum;
extern bit flgljsum;
extern unsigned char ljnum;/*�ۼƴ���*/

float absolute(float dat);
float scale(unsigned char sel_zero);
void judge_process();
void jeval_output(float dat);
float disp_weight(float dat);
void lj_adding(float dat);

#endif

