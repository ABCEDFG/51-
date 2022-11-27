#include<reg52.h> 

typedef unsigned int u16;
typedef unsigned char u8;

sbit led=P2^0;
sbit K3=P3^2;		 //P3.2为外部中断0  P3.4为外部中断1

void delay(u16 i)
{
 	while(i--);
}

void Init0()		  //外部中断0初始化
{
 	IT0=1;		   //开外部中断0下降沿触发
	EX0=1;		   //开外部中断0
	EA=1;		   //开总中断
}

void main()
{
 	Init0();
	while(1);
}

void Deng() interrupt 0	   //外部中断0中断程序
{
 	delay(1000);
	if(K3==0)
	{
	 	led=~led;
	}
}