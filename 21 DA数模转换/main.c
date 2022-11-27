#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit led=P2^1;
bit x;

u16 s,c,t;

void Init()   //��ʱ��1��ʼ��
{
 	TMOD|=0x10;	  //ѡ��λ��ʱ��1ģʽ
	TH1=0xff;	  //1us
	TL1=0xff;
	ET1=1;   //�򿪶�ʱ��1�ж�����		  
	EA=1;	 //�����ж�
	TR1=1;	 //�򿪶�ʱ��
} 

void main()
{
 	Init();
	while(1)
	{
	 	if(s>100)  // s	����ÿ10us��c++ �� c--
		{
		 	s=0;
			if(x==1)
			{
			 	c++;
			}
			if(x==0)
			{
			 	c--;
			}
		}
		if(c==1000)
		{
		 	x=0;
		}
		if(c==0)
		{
		 	x=1;
		}
		if(t>1000)
		{
		 	t=0;
		}
		if(t<c)
		{
		 	led=1;
		}
		else
		{
		 	led=0;
		}
	}	
}

void duan() interrupt 3
{
 	TH1=0xff;
	TL1=0xff;
	t++;
	s++;
}