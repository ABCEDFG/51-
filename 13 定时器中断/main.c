#include <reg52.h>

typedef	unsigned int u16;

sbit led=P2^0;

void T0Init()			  //��ʱ����ʼ��	
{
 	TR0=1;            //������ʱ��
	TMOD|=0x01;        //��ʱ������ģʽ1��16λ��ʱ����ģʽ
	TH0=0xfc;		   //��ֵ  ��ʱ1����
	TL0=0x66; 
	ET0=1;				//�򿪶�ʱ���ж�
	EA=1;				//�����ж�
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
 