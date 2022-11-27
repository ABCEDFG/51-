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
 	 TMOD=0x20;	  //T1 8λ����ģʽ���Զ���װ��
	 TH1=0xf4;	  //������4800
	 TL1=0xf4;
	 PCON=0x80;	  //�����ʱ���
	 TR1=1;		  //���� T1
	 SCON=0x50;	  //���ڷ�ʽ 1 
	 ES=1;		  //������ͨ��
	 EA=1;		  //�����ж�
}

void main()
{
 	 chuan();
	 while(1);
}

void duan() interrupt 4
{
 	u16 u,p;
	u=SBUF;		 //���ܲ���������
	RI=0;		 //ȡ�������ж�����
	SBUF=u;		 //���������� PC
	o=u-'0';	 
	p=500;
	while(p--)	 //�������ʾ
	{
		Acc();
	}
	while(!TI);
	TI=0;		 //ȡ�������ж�����
	
}