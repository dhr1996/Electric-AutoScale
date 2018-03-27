#include "Includes.h"

//*AD相关：*//
float 	 zerob,/*开机零点内码*/
     zeroc,/*按键零点内码*/
     ad_20,
     ad_value;/*初始内码值*/
    

bit  flgwd/*AD内码稳定值*/;
//*重量相关：*//
unsigned char wd_1,wd_2;
float  ad_17,ad_1d;
float  ad_array[12],/*初始内码众值*/
	         point[4];  /*校准4个内码值*/
	
//$$$$$$$$$$$$$$$$$$$$$$$$ 滤波 $$$$$$$$$$$$$$$$$$$$$$

bit flgpower;//cxr 2008.8.13


void sznb_initial()
{
	ad_20=0.0;
	flgwd=0;
	wd_1=0;
	wd_2=0;
}

/******************************************************************************
* 函数名称: AdStore
*
* 函数功能: 刷新adbuf数组
*
* 参数输入: 
*         将采样到的内码值，存入adbuf数组里
* 返回值:
*     SUCCESS -- 成功； FAIL--读取失败
* 注意事项:
*       
* 历史纪录：
*     修改人		 日期		    	 版本号       修改记录
*     陈欣茹     2012-03-04            1.0.0         创建
*
******************************************************************************/
uchar AdStore()
{
	ulong ulSample = 0;
	char i;
	
	if(1)//(ADRead(&ulSample) == SUCCESS)
	{
		ad_value =(float)ulSample;
      if(flgpower)
        {
            for(i=0; i<12; i++) ad_array[i]=ad_value;
            ad_20=ad_value;
        }
		return SUCCESS;
	}
	else 
	  	return FAIL;
		//	d_print(" ad1=%.1f ", adBuf[0]);
}
float pjnb(unsigned char n)
{
	float ave;
	unsigned char i;

	ave=0.0;
	for(i=0; i<n; i++)
	ave=ave+ad_array[i];
    ave=ave/n;
    return ave;
}
uchar filter()
{
char i;
float rt=0.0,ad_16=0.0,dat=0.0;
	
  if(AdStore()==SUCCESS)
  {
	  for(i=8;i>0;i--)
    	     ad_array[i+1]=ad_array[i];
            ad_array[0]=ad_value;
	       rt=pjnb(8);

	dat=rt-ad_20;
	ad_16=dat;
	
	if(absolute(ad_value-ad_20)>(40*ad_1d))
	{
    	flgwd=0;
		ad_20=0.98*ad_16+ad_20;
        ad_array[0]=ad_value;
	}
    else if(absolute(ad_16)>(10*ad_1d))
	{
		flgwd=0;
        ad_20 =0.98*ad_16+ad_20;
        	
	}
	
	else
	{
		if(!flgwd)
		{
			ad_17=0.0;
			wd_2=0;
			if(wd_1>8)   //12
			{
				flgwd=1;
				ad_20=0.98*ad_16+ad_20;   //0.98
			}
			else
				ad_20=rt;
		}
		else
		{
			/*if(absolute(ad_16)<(0.8*ad_1d))
				wd_2++;
			else
				wd_2=11;
			if(wd_2>3)
			{
				wd_2=0;*/
			if(dat>8)
				dat=8;
			else if(dat<(-8))
				dat=(-8);
			if((dat*ad_17)>0.0)
				ad_17=dat+ad_17;
			else
				ad_17=dat;
			if(absolute(ad_17)>38)
			{
				ad_20=rt;
				flgwd=0;
			}
			else
				ad_20=0.0125*ad_16+ad_20;
			}
		}
	}

//       wd_3++;
        ad_20=ad_20;
    if(absolute(ad_16)<(0.8*ad_1d))
    {
    	wd_1++;
    	if(wd_1>100)
    		wd_1=100;
    }
    else
    	wd_1=0;
   		return SUCCESS;
	}
  else 
	  return FAIL;
}

