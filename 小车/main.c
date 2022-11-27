#include <STC15.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit you1=P3^3;	//右轮
sbit you2=P3^2;

sbit zuo1=P5^5;	//左轮
sbit zuo2=P5^4;

sbit bizuo=P1^2;	//避障 左红外
sbit biyou=P1^0;	//避障 右红外

sbit xunzuo=P1^3;	//循迹 左红外
sbit xunyou=P1^1;	//循迹 右红外

sbit key=P1^5;	//按键

sbit led1=P1^4;	//车尾左 灯
sbit led2=P3^7;	//车尾右 灯

u8 x=0;

void delay(u16 i)
{
	while(i--);
}

void Qian()	//前进
{
	u8 i;
	you2=0;
	zuo2=0;
	for(i=0;i<100;i++)	//软件调节 使左右轮转速相同
	{
		if(i<97)
		{
			you1=1;
		}
		else
		{
			you1=0;
		}
		if(i<99)
		{
			zuo1=1;
		}
		else
		{
			zuo1=0;
		}
	}
}

void Hou()	//后退
{
	u8 i;
	you1=0;
	zuo1=0;
	for(i=0;i<100;i++)
	{
		if(i<97)
		{
			you2=1;
		}
		else
		{
			you2=0;
		}
		if(i<99)
		{
			zuo2=1;
		}
		else
		{
			zuo2=0;
		}
	}
}

void Zuo()	//左拐
{
	u8 i;
	zuo1=0;
	you2=0;
	for(i=0;i<11;i++)
	{
		if(i<10)
		{
			you1=1;
		}
		else
		{
			you1=0;
		}
	}
}


void You()	//右拐
{
	u8 i;
	you1=0;
	zuo2=0;
	for(i=0;i<11;i++)
	{
		if(i<10)
		{
			zuo1=1;
		}
		else
		{
			zuo1=0;
		}
	}
}

void Bi()	//避障
{
	//bizuo=biyou=1;
	while(bizuo==0)	//左前方有障碍物	
	{
		You();
	}
	while(biyou==0)	//右前方有障碍物
	{
		Zuo();
	}
}

void Xun()	//循迹
{
	while(xunzuo==1&&xunyou==0)	//右踩线
	{
		Zuo();
	}
	while(xunzuo==0&&xunyou==1)	//左踩线
	{
		You();
	}
}

void Key()
{
	if(key==0)
	{
		delay(1000);
		if(key==0)
		{
			x=!x;
		}
		while(key==0)
		{
			if(x==0)
			{
				led1=0;	//左灯亮表示避障
			}
			else
			{
				led2=0;	//右灯亮表示循迹
			}
		}
		led1=1;	//松开按键 灯灭
		led2=1;
	}
}


void main()
{
	while(1)
	{
		Key();
		if(x==0)
		{
			Qian();
			Bi();
		}
		else
		{
			Qian();
			Xun();
		}
	}
}
