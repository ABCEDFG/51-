/*****************************************************************************
可以保存数据，断电不丢失
键： k1 保存数据， k2 查看保存， k3 加一， k4 归零 	
******************************************************************************/
																			 
#include <reg52.h>
#include <i2c.h>

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 a,b,c,d;
char x;

void delay(u16 i)
{
 	while(i--);
}


void jian()				//定义按键功能
{
 	if(k1==0)			 //保存数据
	{
	 	delay(1000);
		if(k1==0)
		{
		 	At24c02_Write(1,x);	 //保存数据到 1 
		}
		while(!k1);
	}

 	if(k2==0)			  //读取保存的数据
	{
	 	delay(1000);
		if(k2==0)
		{
		 	x=At24c02_Read(1);	//查看保存数据 1
		}
		while(!k2);
	}

 	if(k3==0)			//x++
	{
	 	delay(1000);
		if(k3==0)
		{
		 	x++;
			if(x>255)
			{
			 	x=0;
			}
		}
		while(!k3);
	}

 	if(k4==0)		   //归零
	{
	 	delay(1000);
		if(k4==0)
		{
		 	x=0;
		}
		while(!k4);
	}
}

void Shuju()		  //处理数据，千、百、十、个位
{
    
	a=x%10;
	b=x/10%10;
	c=x/100%10;
	d=x/1000%10;
}

void Acc()			 //数码管显示
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BAA[a];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=BAA[b];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=BAA[c];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=1;
	   P0=BAA[d];
	   delay(50);
	   P0=0x00;
}

void main()
{
	x=0;
	while(1)
	{
		jian();
		Shuju();
		Acc();
	}
}
