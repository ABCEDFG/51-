#include<reg52.h> 

typedef unsigned int u16;
typedef unsigned char u8;

sbit led=P2^0;
sbit K3=P3^2;		 //P3.2Ϊ�ⲿ�ж�0  P3.4Ϊ�ⲿ�ж�1

void delay(u16 i)
{
 	while(i--);
}

void Init0()		  //�ⲿ�ж�0��ʼ��
{
 	IT0=1;		   //���ⲿ�ж�0�½��ش���
	EX0=1;		   //���ⲿ�ж�0
	EA=1;		   //�����ж�
}

void main()
{
 	Init0();
	while(1);
}

void Deng() interrupt 0	   //�ⲿ�ж�0�жϳ���
{
 	delay(1000);
	if(K3==0)
	{
	 	led=~led;
	}
}