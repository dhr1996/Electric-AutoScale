#include <HX711.h> 
#include <nokia5110.h>
#include <Keypad.h>

/*******************************/
int keydisplay[10] =  {};
unsigned int keynum= 0;
 int j= 0;
 int k =0;
 int t = 0;
long int last_value = 0;
double zhongliang = 3;
double money = 0;
 double GG = 0;
 int l = 0;
/*******************************/
char key;
int zhi_1,zhi_2,zjz,zjs;
int asd;
int ax=0;
int as;
  double hx7111;
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
int zxc=0;
float 	 zerob, zeroc,ad_20,ad_value;
int flgpower=1;    
int Filter_Value;
#define FILTER_N 100
char  flgwd/*AD内码稳定值*/;
//*重量相关：*//
char wd_1,wd_2;
float  ad_17,ad_1d;
float  ad_array[12],/*初始内码众值*/
	         point[4];  /*校准4个内码值*/
//byte rowPins[ROWS] = {P4_0, P4_3, P1_2, P1_3}; //connect to the row pinouts of the kpd
//byte colPins[COLS] = {P1_4,P1_5,P2_4,P2_5}; //connect to the column pinouts of the kpd
byte rowPins[ROWS] = {P8_2, P3_7, P4_0, P4_3}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {P1_2,P1_3,P1_4,P1_5};
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int a,b,c,d,e,f,g;

unsigned long loopCount;
unsigned long startTime;
String msg;
HX711 hx(23, 24,128,2.08); 

static nokia5110 lcd;
#define FILTER_N 12
int Filter(int input)
{
  int i;
  int filter_sum = 0;
  for(i = 0; i < FILTER_N; i++) {
    filter_sum += hx.read();
   delay(1);
  return (int)(filter_sum / FILTER_N);
}
}
double x=0;
double zs=0;
 double sum = 0; 

/********************************/

char change_keynum(char numchar)
{  

     switch(numchar)
     {
       case '0':
             {
                 keynum = 0;
                 return keynum;
                 break;
             }
       case '1':
             {
                 keynum = 1;
               return keynum;
                 break;
             }
       case '2':
             {
                 keynum = 2;
                return keynum;
                 break;
             }
       case '3':
             {
                 keynum = 3;
                 return keynum;
                 break;
             }
       case '4':
             {
                 keynum = 4;
                 return keynum;
                 break;
             }
       case '5':
             {
                 keynum = 5;
                return keynum;
                 break;
             }
       case '6':
             {
                 keynum = 6;
                return keynum;
                 break;
             }
       case '7':
             {
                 keynum = 7;
                return keynum;
                 break;
             }
       case '8':
             {
                 keynum = 8;
               return keynum;
                 break;
             }
       case '9':
             {
                 keynum = 9;
                return keynum;
                 break;
             }
       case '*':
             {
                 keynum = 10;            
                 return keynum;
                 break;
             }
        case '#':
             {
                 keynum = 11;
                return keynum;
                 break;
             }
        case 'A':
             {
                 keynum = 12;
                return keynum;
                 break;
             }
         case 'B':
             {
                 keynum = 13;
                 return keynum;
                 break;
             }
        case 'C':
             {
                 keynum = 14;
                return keynum;
                 break;
             }
        case 'D':
             {
                 keynum = 15;
                return keynum;
                 break;
             }
        default:
            {
                keynum = 16;
                return keynum;
            }
             
     }
}

int pow1(int sum, int n)
{
int temp = sum;
  if(n == 0)
  {
      sum = 1;
  }
  else 
  {
    for (int a=1; a<n; a++)
    {
      sum *= temp;
    }
  }
 return sum; 
}
 void display_1(void)
{
  static int counter = 0;
  lcd.setCursor(0, 0);
  lcd.print("unit price: ");
  lcd.setCursor(0,1);lcd.print("0          ");
  lcd.println("y/g");
  
  lcd.setCursor(0, 2);
  lcd.print("weight: ");
   lcd.print("0  ");
  lcd.println("g");

  lcd.setCursor(0,3);
  lcd.print("total price: ");
  lcd.setCursor(0,4);
  lcd.print("0            ");
  lcd.println("y");  
  
  lcd.setCursor(0,5);
  lcd.print("add: ");
  counter++;
}
void part_3(void)
{
    loopCount++;
    if ( (millis()-startTime)>5000 ) 
    {
        startTime = millis();
        loopCount = 0;
    }
    if (kpd.getKeys())
    {  
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                  t++;
                  if(j == 0)
                  {
                     lcd.setCursor(0,1);
                     lcd.print("          "); 
                     delay(100);
                     lcd.setCursor(0,4);
                     lcd.print("          ");
                     
                  }
                  if(t == 3)
                  {
                      t = 0;
                      change_keynum(kpd.key[i].kchar);
                      if(keynum< 10)
                      {
                       keydisplay[j] = keynum;
                        lcd.setCursor(j*6,1);
                        lcd.print(keynum);   
                      j++;
//                      digitalWrite(P1_0,HIGH);
//                      delay(400);
//                      digitalWrite(P1_0,LOW);
//                      delay(400);
                  }
                  if(keynum == 10)
                  {
                      last_value = 0;
                      k=j;
                      j=0;
                      while(k >= 0)
                      {
                      last_value += keydisplay[j]*pow1(10,k-1);
                      keydisplay[j] = 0;
                      k--;
                      j++;
                      }
                      k = 0;
                      j = 0;
                      
                   }
                            if(keynum == 11)
                            {
                                GG  += (last_value*zhongliang);
                                l++;
                            }
                            Serial.print(keynum);
                            if(keynum == 12)
                            {
                               l = 0;
                               GG = 0;
                            }
                 }
            }
        }
    }
//    Serial.print(keynum);
    lcd.setCursor(0,4);
    lcd.print(last_value*zhongliang);
    lcd.setCursor(25,5);
    lcd.print(GG);
    lcd.setCursor(40,2);
    lcd.print(zhongliang);
    keynum = 0;
    digitalWrite(P1_0,HIGH);
}

float cotrol(long int base,long int num)
{
  long int value = 0;
  value = base * num;
  return value;
}

/*********************************/
 
 
void setup() 
{
    pinMode(P1_0,OUTPUT);
    lcd.begin(84, 48,0xC8);
    Serial.begin(9600);
        loopCount = 0;
    startTime = millis();
    msg = "";
for(int l=0;l<20;l++)
{
filter(hx.read());
}
delay(200);
  hx7111 = hx.read()/64;
     x=hx7111;
    filter(x);
x=  filter2(x);

 
/**********************************/
display_1();
/**********************************/
   
// hx711 = Filter(hx711);

}

void loop()
{
    
 zhongliang = part_2();
 part_3();   


}

double part_2()
{
  zs=0;
  flgpower=0;
  static int counter = 0;
  lcd.setCursor(0, 0);
   sum = hx.read(); 
   sum=filter(sum);
  sum=filter2(sum);
   sum=sum/64;
//   sum = sum - x;
//  sum=sum*0.00730*40;
 Serial.println(sum); 


if(sum > (-17.80) & sum < (-16.38)  )
{

  sum=filter(sum);
 sum=filter2(sum);
  sum = sum - x;
  sum=sum*0.00740*40;
}
if(sum>(-16.38)&sum<(-12.56))
{
sum=filter(sum);
 sum=filter2(sum);
  sum = sum - x;
  sum=sum*0.00744*40;

}
if(sum > (-12.56) & sum < (-7.50))
{
 sum=filter(sum);
 sum=filter2(sum);
  sum = sum - x;
  sum=sum*0.00740*40;


}
if(sum > (-7.50) & sum < (-2.38))
{
 sum=filter(sum);
  sum=filter2(sum);
  sum = sum - x;
  sum=sum*0.00740*40;


}
if(sum > (-2.38) & sum < (2.62))
{
sum=filter(sum);
 sum=filter2(sum);
  sum = sum - x;
  sum=sum*0.00750*40;


}
if(sum > (2.62) & sum < (8.28))
{
sum=filter(sum);
 sum=filter2(sum);
  sum = sum - x;
  sum=sum*0.00750*40;


}
if(sum>500)
{


}
if(sum<1)
{
sum=0;
}
return sum;
 Serial.println(sum); 
}
//void net_weight()
//{
//  
//  if(ax==0)
//  {
//  asd = hx.read()/64;
//  as = x ;
//  filter(asd);
//  x = asd;
//ax ++;
//  }
//if(ax==1)
//{
//x  = as;
//ax=0;
//
//}
//}

void AdStore(double dat)
{
	ulong ulSample = 0;
	char i;
	ad_value =dat;
      if(flgpower)
        {
            for(i=0; i<12; i++) ad_array[i]=ad_value;
            ad_20=ad_value;
        }//	d_print(" ad1=%.1f ", adBuf[0]);
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
double filter(double datp)
{
char i;
float rt=0.0,ad_16=0.0,dat=0.0;
	
AdStore(datp);
	  for(i=8;i>0;i--)
    	     ad_array[i+1]=ad_array[i];
            ad_array[0]=ad_value;
	       rt=pjnb(8);

	dat=rt-ad_20;
	ad_16=dat;
	
	if(abs(ad_value-ad_20)>(40*ad_1d))
	{
    	flgwd=0;
		ad_20=0.98*ad_16+ad_20;
        ad_array[0]=ad_value;
	}
    else if(abs(ad_16)>(10*ad_1d))
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
			if(abs(ad_17)>38)
			{
				ad_20=rt;
				flgwd=0;
			}
			else
				ad_20=0.0125*ad_16+ad_20;
			}
		}
	

//       wd_3++;
       // ad_20 = ad_20;
    if(abs(ad_16)<(0.8*ad_1d))
    {
    	wd_1++;
    	if(wd_1>100)
    {
    		wd_1=100;
    }
    } 
    else
       {
         wd_1=0;
       }
}





