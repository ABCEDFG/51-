#include <reg52.h>

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
	TMOD|=0x01;        //定时器工作模式1，16位定时计数模式
	TH0=0xfc;		   //初值  定时1毫秒
	TL0=0x66; 		   //初值
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
	  if(i!=2&&i!=5)
	  {
	    	P0=AA[BB[i]];
	  }
	  else
	  {
	   		P0=0x40;
	  }
	  delay(100);
	  P0=0x00;
   }
}

void Count(u16 s)			   //数字处理
{
	u8 i,m,h;
	u16 n;
	n=1;
	if(s==60)
	{
		x=0;
		s=0;
		m++;
	}
	if(m==60)
	{
	 	m=0;
		h++;
	}	
	for(i=0;i<2;i++)
	{
 		BB[i]=s/n%10;
		BB[i+3]=m/n%10;
		BB[i+6]=h/n%10;
		n*=10;
	}
}

void Tiem0() interrupt 1
{
    u16 i;       
	TH0=0xfc;
	TL0=0x66;
	i++;
	if(i==1000)	//1000ms 即 1s
	{
		i=0;	
	    x++;
	}
}

void main()
{
	x=0;
 	T0Init();
	while(1)
	{
	 	Count(x);
		Acc();
	}
}
 