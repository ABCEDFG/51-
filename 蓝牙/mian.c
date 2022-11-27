#include "STC15.h"

#define uchar unsigned char
#define uint  unsigned int

#define _r 0X0A
#define _d 0X0D

#define T1VALUE 0XFd

sbit you1=P3^3;	//右轮
sbit you2=P3^2;

sbit zuo1=P5^5;	//左轮
sbit zuo2=P5^4;

sbit control=P1^1;

int cnt=0;

uchar code display[]="Temperature:";
uchar mode=0,flag=0;

void delay_ms(uint x)
{
  uint i,j;
  for(i=0;i<x;i++)
    for(j=0;j<110;j++);
}

void delay_us(uint x)
{
   while(x--);
}

void Qian()	//前进
{
	uchar i;
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

void UartInit(void)
{
   TMOD = 0x20;    
   PCON = 0x00;       
   SCON = 0x50;//0101 0000
   TH1=T1VALUE;
   TL1=T1VALUE;	
   ES=1;
   EA=1;     
   TR1=1;	          							  
}

void Send_Char(uchar chr)
{
	ES=0;
	SBUF=chr; 
	while(!TI);
	SCON&=~(1<<1); 
	ES=1;         
}

void Send_Str(uchar *str)
{
	ES=0;
	while(*str!='\0')
	{
		SBUF=*str; 
		while(!TI);      
		TI=0;            
		str++;
	}
	SCON&=~(1<<1);
	ES=1; 

}

int main(void)
{ 
	int i,j;
	i=10000;
	UartInit();
	control=1; 
	while(1)
	{        //手动模式
		if(flag)
		{	
			control=0;	
		}
		else
		{
			control=1;
		}		
		delay_ms(1000);	//750
		while(i--)
		{
			j=10000;
			while(j--)
			{
				Qian();
			}
		}
	}
	return 0;
}

sbit led=P1^0;
void uart_Handler(void)interrupt 4
{
	uchar dat=0;
	if(RI)
	{
		RI=0;
		dat=SBUF;
		if(dat=='1')
		{
			flag=1;
		}
		else if(dat=='z')
		{
			mode=1;	
			led=0;
		}
		else if(dat=='2')
		{
			flag=0;
		}	
		else if(dat=='s')
		{
			mode=0;
		}	
	}
}