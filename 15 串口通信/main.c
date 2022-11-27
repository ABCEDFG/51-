#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
u16 p,z;
u8 o;

void delay(u16 i)
{
   while(i--);
}

void Acc()
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BAA[o];
	   delay(500);
	   P0=0x00;
}


void chuan()
{
 	 TMOD=0x20;	  //T1 8位计数模式，自动重装载
	 TH1=0xf4;	  //波特率4800
	 TL1=0xf4;
	 PCON=0x80;	  //波特率倍增
	 TR1=1;		  //启动 T1
	 SCON=0x50;	  //串口方式 1 
	 ES=1;		  //允许串口通信
	 EA=1;		  //打开总中断
}

void main()
{
 	 chuan();
	 while(1);
}

void duan() interrupt 4
{
 	u16 u,p;
	u=SBUF;		 //接受并保存数据
	RI=0;		 //取消接收中断申请
	SBUF=u;		 //发送数据至 PC
	o=u-'0';	 
	p=500;
	while(p--)	 //数码管显示
	{
		Acc();
	}
	while(!TI);
	TI=0;		 //取消发送中断申请
	
}