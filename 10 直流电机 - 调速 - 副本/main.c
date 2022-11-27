/*接5v 及 01*/
/*k1转速最大、k2约0.75倍k1、k3约0.5倍、k4关闭电机*/

#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit motor=P1^0;	  //电机串口
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

u8 x;
void delay(u16 i)
{
   while(i--);
}

void key()
{
 	if(k1==0)
	{
	 	delay(1000);
		if(k1==0)
		{
		 	x=0;		  //全程供电
		}
		while(k1==0);
	}

	if(k2==0)
	{
	 	delay(1000);
		if(k2==0)
		{
		 	x=25;		  //0.75供电
		}
		while(k2==0);
	}

	if(k3==0)
	{
	 	delay(1000);
		if(k3==0)
		{
		 	x=50;		//0.5供电
		}
		while(k3==0);
	}

	if(k4==0)
	{
	 	delay(1000);
		if(k4==0)
		{
		 	x=100;	   //断电
		}
		while(k4==0);
	}
}

void dong()				//用以控制电机
{
	u8 i,j,k;
	motor=0;
	for(i=0;i<100;i++)
	{
	 	if(i>x)			//x/100为供电时间比
		{
		 	motor=1;
		}
	}
}	

void main()
{
	x=100;			  //初始时为断电状态
   while(1)
   {
       key();
	   dong();
   }		 
}