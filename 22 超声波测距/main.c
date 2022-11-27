/*Trig��P2^0,Echo��P2^1*/

#include <reg52.h>
#include <intrins.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit RX=P2^1;
sbit TX=P2^0;
bit flag=0;

typedef unsigned int u16;
typedef unsigned char u8;

//              0    1    2    3    4    5    6    7    8    9    A    b    c    d    E    f    -
u8 code AA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40,0x80};
u8 BB[5]={0,0,0,17,0};
u16 t1=0;
u16 t2=0;
u16 s=0;

void delay(u16 i)
{
 	while(i--);
}

void Init()   //��ʱ����ʼ��
{
 	TMOD=0x11;   //��T0Ϊ��ʽ1
	TH0=0;
	TL0=0;
	TH1=0xf8;   //2ms��ʱ
	TL1=0x30;
	ET0=1;   //����T0�ж�
	ET1=1;	 //����T1�ж�
	TR1=1;	 //�򿪶�ʱ��T1�ж�
	EA=1;	 //�����ж�
}

void shi()		//������
{
 	t1=TH0*256+TL0;   //����������ʱ��
	TH0=0;
	TL0=0;
	s=(u16)(t1*0.17);   //���� ��λ mm
}

void shu()
{
	if(s>4000||flag==1)
	{
	 	flag=0;
		BB[0]=16;	// -
		BB[1]=16;	// -
		BB[2]=16;	// -
		BB[4]=16;	// -
	}
	else
	{
	 	 BB[0]=s%10;
		 BB[1]=s/10%10;
		 BB[2]=s/100%10;
		 BB[4]=s/1000%10;
	}
}

void Acc()
{
   u8 i;
   for(i=0;i<5;i++)
   {
   	  switch(i)
	  {
	   case(7):
	            LSC=1, LSB=1, LSA=1;break;
	   case(6):
	            LSC=1, LSB=1, LSA=0;break;
	   case(5):
	            LSC=1, LSB=0, LSA=1;break;
	   case(4):
	            LSC=1, LSB=0, LSA=0;break;
	   case(3):
	            LSC=0, LSB=1, LSA=1;break;
	   case(2):
	            LSC=0, LSB=1, LSA=0;break;
	   case(1):
	            LSC=0, LSB=0, LSA=1;break;
	   case(0):
	            LSC=0, LSB=0, LSA=0;break;
	  }
	  P0=AA[BB[i]];
	  delay(10);
	  P0=0x00;
   }
}

void ding1() interrupt 1   //�����Զ��T0��ʱ�����
{
 	flag=1;   //����������Χ
}

void ding2() interrupt 3   //2ms���һ��
{
 	TH1=0xf8;   //��ʱ2ms
	TL1=0x30;	
	Acc();
	t2++;   //��ʱ400��     
	if(t2>=400)   //800ms����һ�Σ���ֹ��������
	{
	 	t2=0;
		TX=1;
		_nop_();_nop_();	  // 20us �ĸ�ƽ��ѹ���������
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		TX=0;
	}
}

void main()
{
 	Init();
	while(1)
	{
	 	while(!RX);
		TR0=1;   //�򿪶�ʱ��T0�ж�
		while(RX);
		TR0=0;   //�رն�ʱ��T1�ж�
		shi();
		shu();
		Acc();
	}
}
