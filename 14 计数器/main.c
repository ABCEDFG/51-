//         P3^4 与 P3^1	相接，按键则计数器计数，并由数码管显示，按键次数
#include <reg52.h>

sbit led=P2^0;
sbit k1=P3^1;
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

typedef	unsigned int u16;
typedef unsigned char u8;

u8 code AA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 x,BB[8]={0};

void delay(u16 i)
{
 	while(i--);
}

void T0Init()			  //定时器初始化	
{
 	TR0=1;            //启动定时器
	TMOD|=0x05;        //定时器工作模式1，16位定时计数模式
	TH0=0x00;
	TL0=0x00;
	ET0=1;				//打开定时器中断
	EA=1;				//打开总中断
}

void Acc()					   //数码管显示
{
   u8 i;
   for(i=0;i<8;i++)
   {
   	  switch(i)
	  {
	   case(7):
	            LSC=1, LSB=1, LSA=1;break;				//十时
	   case(6):											
	            LSC=1, LSB=1, LSA=0;break;				//时
	   case(5):
	            LSC=1, LSB=0, LSA=1;break;				//——
	   case(4):
	            LSC=1, LSB=0, LSA=0;break;				//十分
	   case(3):
	            LSC=0, LSB=1, LSA=1;break;				//分
	   case(2):
	            LSC=0, LSB=1, LSA=0;break;				//——
	   case(1):											
	            LSC=0, LSB=0, LSA=1;break;				//十秒
	   case(0):											
	            LSC=0, LSB=0, LSA=0;break;				//秒
	  }
	  P0=AA[BB[i]];
	  delay(100);
	  P0=0x00;
   }
}

void Count(u16 s)			   //数字处理
{
	u8 i,m,h;
	u16 n;
	n=1;	
	for(i=0;i<2;i++)
	{
 		BB[i]=s/n%10;
		n*=10;
	}
}

void LED()
{
 	if(k1==0)
	{
	 	delay(1000);
		if(k1==0)
		{
			led=~led;
		}
		while(k1==0);	
	}
}

void Tiem0() interrupt 1
{
    u16 i;
	x++;
}

void main()
{
	x=0;
 	T0Init();
	while(1)
	{
		LED();
		Count(TL0);
		Acc();
	}
}
 