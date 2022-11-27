/***************************************************************
左4位x方向，右4位y方向
停60，走27，黄3
每个方向前两位计时，第三位左方向，第四位前方向
最上-红，中间-黄，最下-绿
*****************************************************************/
 
#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

typedef unsigned int u16;
typedef unsigned char u8;

//				 0	   1	2	 3	  4	   5	6	 7	  8	   9
u8 code AA[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 code BB[]={0x01,0x40,0x08};
//对应         红   黄   绿

u8 a,b,c,d,n,m,s1,s2,z1,z2;
u16 x,y;

void delay(u16 i)
{
   while(i--);
}

void Time()	   //改变时间，红黄绿
{
	if(x==0)//x方向
	{
		n++;
		if(n==5)
		{
		 	n=0;
		}
	 	switch(n)
		{
		 	case(0):  x=27;  s1=0;  z1=2;  break;
			case(1):  x=3; 	 s1=0;  z1=1;  break;
			case(2):  x=27;	 s1=2;  z1=0;  break;
			case(3):  x=3; 	 s1=1;  z1=0;  break;
			case(4):  x=60;	 s1=0;  z1=0;  break;
		}
	}
	else
	{
	 	x--;
	}
	if(y==0)//y方向
	{
		m++;
		if(m==5)
		{
		 	m=0;
		}
	 	switch(m)
		{
		 	case(0):  y=27;  s2=0;  z2=2;  break;
			case(1):  y=3; 	 s2=0;  z2=1;  break;
			case(2):  y=27;	 s2=2;  z2=0;  break;
			case(3):  y=3; 	 s2=1;  z2=0;  break;
			case(4):  y=60;	 s2=0;  z2=0;  break;
		}
	}
	else
	{
	 	y--;
	}
}

void Count()	   //数字处理
{
	a=x%10;
	b=x/10%10;
	c=y%10;
	d=y/10%10;
}

void Acc()	//数码管显示
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BB[s2];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=BB[z2];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=AA[c];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=1;
	   P0=AA[d];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=0;
	   P0=BB[s1];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=1;
	   P0=BB[z1];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=1, LSA=0;
	   P0=AA[a];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=1, LSA=1;
	   P0=AA[b];
	   delay(50);
	   P0=0x00;
}

void main()
{
	u8 	i;
    x=y=0;
	m=3;   //使y方向27 前红 左绿
	n=-1;  //使x方向60 前红 左红
 	while(1)
	{
		Count();
		for(i=0;i<75;i++) //调节速度
		{
		 	Acc();
		}
	 	Time();
	}
}

 															