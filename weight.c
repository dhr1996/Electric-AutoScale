#include "includes.h"

bit flgljnum;
bit flgljsum;

unsigned char ljnum;/*�ۼƴ���*/
float ljsum;/*�ۼ�����*/

float cl,je;/*����ֵ*//*�ܼ�ֵ*/
           

//$$$$$$$$$$$$$$$$$$$$$$$$ ��� $$$$$$$$$$$$$$$$$$$$$$
//*���Ȳ��*//

float const  b_array[]={ 0.0, 1.0/3.0, 2.0/3.0, 1.0 };/*AD����ϵ��*/

bit flgovv;/*���������־*/
bit flgzero;/*��������־*/

float absolute(float dat)
{
	if(dat<0.0) return (-dat);
	else return dat;
}

//$$$$$$$$$$$$$$$$$$$$$$$$ ���� $$$$$$$$$$$$$$$$$$$$$$

float scale(unsigned char sel_zero)
{
	float dat,rt;
	char  i;
	switch(sel_zero){
	    case 0:	dat=point[0];
			break;
	    case 1:	dat=zerob;
			break;
	    case 2:	dat=zeroc;
			break;
	}
	dat=dat-point[0];
	dat=ad_20-dat;
	for(i=1; i<4; i++){
	    if(dat<point[i]) break;
	}
	if(i==4) i--;
	//--------------------
	rt=(b_array[i]-b_array[i-1])/(point[i]-point[i-1]);
	rt=rt*(dat-point[i-1])+b_array[i-1];
	return rt;
}

void judge_process()
{
    //unsigned char i;
    
	cl=scale(2);		   /*�𰴼����Ϊ������꣬�����ǰ��������ֵ*/
	if(cl>2.0 || cl<-2.0) cl=2.0;/*���Ƴ�������ֵ��Χ*/
	cl=cl*RANGE;/*�ó�ë��ֵ*/
	//�����ж����������������//

    if(cl>flt) flgovv=1;/*��������F.S+9d�������*/
	else	   flgovv=0;//������������жϡ���//
		
	flt=DIV*0.25;
	if(absolute(cl)<=flt) flgzero=1;/*����С�ڻ����0.25d������Ϊ�������״̬*/
	else		  flgzero=0;
		//���������١���//
	flt=DIV*0.5;
	if(absolute(cl)>flt) zero_num=0;
	else zero_num++;/*����С�ڻ����1.3d������и��ټ���*/
	if(zero_num>20) /*����20�Σ�������С�ڻ����1.3d�������������*/
	{
		zero_num=0;
		zeroc=ad_20;
	}

}

/****************************************************
*   �������ܣ������ܼ����Χ
*   ���������Ҫ����ʾ���ܼ�ֵ
*   ���ز��������������־��0Ϊ���洦��1Ϊ�������
*****************************************************/
bit flgov_je(unsigned char poin,float dat)
{
  unsigned char i;
  long  val;

    for(i=0;i<poin;i++)
    	dat=dat*10.0;

   val=(long)dat;

	if(val>999999)
		return 1;
	else
		return 0;
}

/****************************************************
*   �������ܣ������ܼ�ֵ
*   ���������begin,���Ե���ʼλ��total,���Ե���λ����
*****************************************************/
void jeval_output(float dat)
		{
	//		unsigned char  poin=0;
		
			clrdisp(2);
			if(flgovv) je=0.0;
			else if(dat<0.0) je=0.0;
			else je=kval*dat;
		
		
			if(flgov_je(1,je))/*Ϊ1�����*/
			{
				disp[3]=CHAR_0;
				disp[4]=CHAR_V;
			}
			else
			{
				//dispFloat(0,6,1,je);
			}
		
		}


/****************************************************
*   �������ܣ�������kg��ʾ
*   �������������ֵ���������ڵ�ģʽ
*   ���ز��������ݼ۸�λ���������ֵ
*****************************************************/
float disp_weight(float dat)
{
    unsigned char div_i;

    div_i=1;
    //*��Ϊ˫�������ã����е�˫����ת��*//
    	
            flt=DIV/2.0;
            flt=absolute(dat)+flt;
            flt=(long)(flt/DIV);
            flt=flt*DIV;
            //*����С����λ��*//		
            if(div_i>=3)
            	flt=flt/1000.0;
			if(flt!=0.0 && dat<0.0)
		      flt=-flt;
           // dispFloat(0,6,1,flt);
            if(div_i<3)
            	flt=flt/1000.0;         		
	return flt;
}
/****************************************************
*   �������ܣ��ۼƼӷ���ʽ
*   ���������Ҫ�ۼƵ�ֵ��
*****************************************************/
void lj_adding(float dat)
{
//	unsigned char data poin;

	flgljnum=0;
	if(ljnum>98)
		flgljnum=1;
	else
	{
		flt=dat+ljsum;
		flgljsum=0;
		if(!flgov_je(1,flt))
		{
			ljsum=flt;
			ljnum++;
		}
		else
			flgljsum=1;
	}
}


