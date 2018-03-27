#include "includes.h"

bit flgflj;/*重量累计标志，累计过的为1*/
bit  flag_print;
unsigned char sys;/*状态模式*/

//*显示相关：*//
float  flt;
//*重量相关：*//
float kzng,weight;/*去皮值*/
//*其它：*//
unsigned char xdata,unit_num,/*开启转换价格的个数*/ 
    unit_sign,
    timer,/*定时总时间*/
    timer_price/*按键按下后定时时间*/,
    timer_ec,
    timer_bs,
    zero_num/*零点跟踪*/;
unsigned char  m_list;
//*按键相关：*//
unsigned char  kindex;/*指示按键状况*/
float kval/*按键值*/;

unsigned char disp[20];


void dashed()
{
	unsigned char i;
	for(i=0;i<5;i++)
	{
		disp[i]=0x11;
	}
}

void clrdisp(uchar dat)
{
	char i;
	for(i=0; i<6; i++) disp[i]=0x10;
	if(dat==0)
		disp[5]=0x00;
	else if(dat==1)
		disp[0]=0x00;
}
void symbolProcT()
{

//	disp[5]&=0XFC;
	if(flgzero) 
		disp[5]|=0x01; 
	
	if(kzng!=0.0) 
		disp[5]|=0x02;
}

void symbolProc()
{

//	disp[0]&=0XFC;
	disp[0]&=0X00;

	if(ljnum!=0)
         disp[0]|=0x01;

}
void dispFloat(char begin,char total,char poin,float dat)
{
;
}

void cal_ISN()
{
	//unsigned char i;

	flt=ad_20-point[0];
	flt=kval/flt;
	flt=flt/RANGE;
	point[1]=1/(flt*3.0);
	point[2]=2*point[1];
	point[3]=3*point[1];
	point[1]=point[0]+point[1];
	point[2]=point[0]+point[2];
	point[3]=point[0]+point[3];
/*	wr2401(config_2402,config);
	for(i=0; i<16; i++)
	{
		delayms(10);
		wr2401(i+1,*(((unsigned char *)point)+i));
	}*/
	zerob=point[0];
	zeroc=point[0];

	key_end();
	default_EPROM();
}


/*************************************************************
*  函数功能:  设置分度值时的显示功能
*  显示内容： "cal 1";"(内码）"；"    "
*************************************************************/
void msys03()
{
	clrdisp(0);
	disp[0]=CHAR_C;	// cal 1
	disp[1]=CHAR_A;
	disp[2]=CHAR_L;
	disp[4]=CHAR_1;
//	dispTransfer(0);

	clrdisp(1);
//	dispFloat(1,5,0,ad_20);
//	dispTransfer(1);

//	clrdisp(1);
//	dispTransfer(1);
}
/*************************************************************
*  函数功能:  设置分度值时的显示功能
*  显示内容： "cal 4";"(按键值）"；"    "
*************************************************************/
void msys04()
{
//	clrdisp(0);
    disp[0]=CHAR_C;
    disp[1]=CHAR_A;
    disp[2]=CHAR_L;
    disp[4]=CHAR_2;
//    dispTransfer(0);

//	clrdisp(1);
   // dispFloat(1,5,0,500.0);
 //   dispTransfer(1);
}


void msys10()
{
	uchar i;

	clrdisp(0);
	if(flgovv) 
    {
	   dashed();
    }
	else
	{
		weight=disp_weight(cl-kzng);
		symbolProcT();
	}
     
//	 dispTransfer(0);

		//……显示按键值……//
    clrdisp(1);
//    dispFloat(1,5,EP_ROM.dot_price,kval);
         i=kindex&0x7f;
         if(i)i--;
         dispFloat(1,5,i,kval);
	symbolProc();
//	unitProc(1<<EP_ROM.unit_sys);
   	//dispTransfer(1);
   
   	//……总价显示……//
   	clrdisp(2);
   	jeval_output(weight);
   	//dispTransfer(2);
}

/****************************************************
*   函数功能：累计值显示
*   显示内容："(累计次数";"ALL"；"（累计值）"
*****************************************************/
void msys20()
{
	unsigned char ljnum_1;

	clrdisp(0);
	if(!flgljnum)
	{
		ljnum_1=ljnum;
		if(flgljsum)
			ljnum_1++;
		dispFloat(0,4,0,ljnum_1);
		if(disp[1]==0x10)
    	{
    	    disp[1]=0x00;
    	   	if(disp[2]==0x10)
    	   		disp[2]=0x00;
    	}
	}
	else
	{
		disp[1]=CHAR_MINUS;
    	disp[2]=CHAR_MINUS;
    	disp[3]=CHAR_MINUS;
	}
	disp[0]=CHAR_MINUS;	// "-"
    disp[4]=CHAR_MINUS;
   // dispTransfer(0);

    clrdisp(1);
    disp[3]=CHAR_A;		// all
    disp[4]=CHAR_L;
    disp[5]=CHAR_L;
   // dispTransfer(1);

    clrdisp(2);
    if(!flgljsum)
    {
       // dispFloat(0,6,EP_ROM.dot_total,ljsum);	
    }
    else
    {
    	disp[4]=CHAR_0;
    	disp[5]=CHAR_L;
    }
   // dispTransfer(2);
}
/*************************************************************
*  函数功能:  清楚累计值
*  显示内容： "Clear?";" YES "；"    "
*************************************************************/
void msys30()
{
	clrdisp(0);
	disp[0]=CHAR_C;
	disp[1]=CHAR_L;
	disp[2]=CHAR_E;
	disp[3]=CHAR_A;
	disp[4]=CHAR_R;
	//dispTransfer(0);

	clrdisp(1);
	disp[3]=CHAR_Y;
	disp[4]=CHAR_E;
	disp[5]=CHAR_S;
	//dispTransfer(1);

	clrdisp(2);
	//dispTransfer(2);
}

void monito()
{
   
	switch(sys)
	{
   	    case 0x03: msys03(); break;
   	    case 0x04: msys04(); break;		  
		case 0x10: msys10(); break;
		case 0x20:
		case 0x25: msys20(); break;
		case 0x30: msys30(); break;
		default:break;
	}
}

/****************************************************
*   函数功能：读入零点内码-〉point[0]。
*   简略操作：去皮键选择；置零键确认。
*****************************************************/
void sys03(unsigned char dat)
{
	if(dat==KEY_ZERO)
	{
		point[0]=ad_20;
		key_end();
		//EP_ROM.dot_price=0x00;
		sys=0x04;
	}
}
/****************************************************
*   函数功能：计算并读入任意点内码，并把校准数据存入
              第一个24C02中。
*   简略操作：置零键确认;数字键；清除键；
*****************************************************/
void sys04(unsigned char dat)
{

	switch(dat)
	{
		case KEY_ZERO:
			    cal_ISN();
			    sys=0x10;
		        break;
/*		case KEY_0:
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:	
			    num_key(dat);
		        break;
		case KEY_CLEAR:
			    key_end();
		        break;*/
	}
}


void sys10(unsigned char dat)
{

	 float flt1;
	 
	switch(dat)
	{
		case KEY_TARE:	           
			
			flt=absolute(cl)+DIV/2.0;
			flt=(long)(flt/DIV);
			flt=flt*DIV;
			if(cl<0.0) flt=-flt;
			flt1=RANGE*1.0;
			if(flt<=flt1 && flt>=(-DIV))
			  {
				if(flgzero) kzng=0.0;
				else if(kzng==0)		kzng=cl;
			  }
	           	break;
		case KEY_ZERO:
			   // if(!flgzero)/*重量不为零，做按键置零用*/
	        	//{
		    	    flt=scale(1)*RANGE;
                    flt=absolute(flt)+DIV/2.0;;
                    flt=(long)(flt/DIV);
                    flt=flt*DIV;
		            if(absolute(flt)<=0.04*RANGE)
		            {
		            	zeroc=ad_20;
						kzng=0.0;
		            }
	        	//}
		        break;
		case KEY_0:
		case KEY_1:
		case KEY_2:
		case KEY_3:
		case KEY_4:
		case KEY_5:
		case KEY_6:
		case KEY_7:
		case KEY_8:
		case KEY_9:
		            //	if((dispbuf[7]!=0x90 &&dispbuf[7]!=0x10)||(kindex&0x7f)>3)
	            		//key_end();
			       if(!key_status())
			        	{
			        	    key_init();
			        	    key_process(dat);
			    		}
		           else if(timer_price==00)//按键时间间隔很长时清按键值
		        		{
		    	    	    key_init();
		    	    	    key_process(dat);
		    	    	}
		           else  key_process(dat);
    	            timer_price=25;
    	    	break;
		case KEY_POINT:
			    if(timer_price==00)//按键时间间隔很长时清按键值
		        	{
					  flag_print=1;
		    	    }
    	        else
    	          {
    	             if(key_status()) key_process(dat);
                   }
                break;		
        case KEY_LJ:
				flt=weight*kval;
        	    if(flt>0.0)/*可称量物品累计*/
                {
                	if(!flgflj&&((cl-kzng)>9*DIV))
                	{
                		lj_adding(flt);
                		flgflj=1;
                		sys=0x20;
                		timer=5;
                	}
                 }
                 else if(kval!=0.0)/*不可称量物品累计*/
                 {
                 	 lj_adding(kval);
                 	 sys=0x20;
                 	 timer=5;
                 }
                 else/*查看累计值*/
                 {
                 	 sys=0x25;
                 }
               //  break;	 
      //  case KEY_CLEAR:
        	    if(kval>0.0)/*清楚单价*/
               {
               	   key_end();
               }
               else if(ljsum!=0.0)/*准备删除累计值*/
               {
               	   sys=0x30;
               }
               break;  
	}
}

/****************************************************
*   函数功能：查看累计值模式
*   简略操作：任意键
*****************************************************/
void sys20()
{
	if(timer==0)
	{
    	flgljnum=0;
       	flgljsum=0;
       	sys=0x10;
       	key_end();
	}
}

/****************************************************
*   函数功能：查看累计值模式
*   简略操作：任意键
*****************************************************/
void sys25(unsigned char dat)
{
   if(dat!=KEY_NULL)
	  sys=0x10;
}
/****************************************************
*   函数功能：清除累计模式
*   简略操作：清除键；
*****************************************************/
void sys30(unsigned char dat)
{
	if(dat!=KEY_NULL)
	{
    	if(dat==KEY_CLEAR)
    	{
    		ljnum=0;
    		ljsum=0;
    	}
    	sys=0x10;
	}
}

void keybord()
{
	uchar keyval;
	
	keyval=readKey();
	switch(sys)
		 {
       	   case 0x03: sys03(keyval); break;
       	   case 0x04: sys04(keyval); break;
       	   case 0x10: sys10(keyval); break;
		   case 0x20: sys20(); break;
		   case 0x25: sys25(keyval); break;
		   case 0x30: sys30(keyval); break;
		   default:break;
		 }
}

