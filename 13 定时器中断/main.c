#include <reg52.h>

typedef	unsigned int u16;

sbit led=P2^0;

void T0Init()			  //定时器初始化	
{
 	TR0=1;            //启动定时器
	TMOD|=0x01;        //定时器工作模式1，16位定时计数模式
	TH0=0xfc;		   //初值  定时1毫秒
	TL0=0x66; 
	ET0=1;				//打开定时器中断
	EA=1;				//打开总中断
}

void Tiem0() interrupt 1
{
    u16 i;       
	TH0=0xfc;
	TL0=0x66;
	i++;
	if(i==1000)
	{
	   i=0;
	   led=~led	;
	}
}

void main()
{
 	T0Init();
	while(1);
}
 