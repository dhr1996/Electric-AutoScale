#include "includes.h"

bit flgljnum;
bit flgljsum;

unsigned char ljnum;/*累计次数*/
float ljsum;/*累计总数*/

float cl,je;/*称量值*//*总价值*/
           

//$$$$$$$$$$$$$$$$$$$$$$$$ 查表 $$$$$$$$$$$$$$$$$$$$$$
//*精度查表*//

float const  b_array[]={ 0.0, 1.0/3.0, 2.0/3.0, 1.0 };/*AD坐标系数*/

bit flgovv;/*重量溢出标志*/
bit flgzero;/*重量零点标志*/

float absolute(float dat)
{
	if(dat<0.0) return (-dat);
	else return dat;
}

//$$$$$$$$$$$$$$$$$$$$$$$$ 称量 $$$$$$$$$$$$$$$$$$$$$$

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
    
	cl=scale(2);		   /*起按键零点为零点坐标，算出当前称量比例值*/
	if(cl>2.0 || cl<-2.0) cl=2.0;/*限制称量比例值范围*/
	cl=cl*RANGE;/*得出毛重值*/
	//……判断重量有无溢出……//

    if(cl>flt) flgovv=1;/*称量大于F.S+9d，有溢出*/
	else	   flgovv=0;//……称量零点判断……//
		
	flt=DIV*0.25;
	if(absolute(cl)<=flt) flgzero=1;/*称量小于或等于0.25d，则认为处于零点状态*/
	else		  flgzero=0;
		//……零点跟踪……//
	flt=DIV*0.5;
	if(absolute(cl)>flt) zero_num=0;
	else zero_num++;/*称量小于或等于1.3d，则进行跟踪计算*/
	if(zero_num>20) /*跟踪20次，称量均小于或等于1.3d，则进行零点跟踪*/
	{
		zero_num=0;
		zeroc=ad_20;
	}

}

/****************************************************
*   函数功能：计算总价最大范围
*   调入参数：要送显示的总价值
*   返回参数：返回溢出标志。0为无益处；1为有溢出。
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
*   函数功能：送显总价值
*   调入参数：begin,送显的起始位；total,送显的总位数。
*****************************************************/
void jeval_output(float dat)
		{
	//		unsigned char  poin=0;
		
			clrdisp(2);
			if(flgovv) je=0.0;
			else if(dat<0.0) je=0.0;
			else je=kval*dat;
		
		
			if(flgov_je(1,je))/*为1有溢出*/
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
*   函数功能：重量以kg显示
*   调入参数：净重值，及所处在的模式
*   返回参数：根据价格单位换算的重量值
*****************************************************/
float disp_weight(float dat)
{
    unsigned char div_i;

    div_i=1;
    //*如为双量程设置，进行单双量程转化*//
    	
            flt=DIV/2.0;
            flt=absolute(dat)+flt;
            flt=(long)(flt/DIV);
            flt=flt*DIV;
            //*保留小数点位数*//		
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
*   函数功能：累计加法公式
*   调入参数：要累计的值。
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


