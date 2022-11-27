#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

typedef	unsigned int u16;
typedef unsigned char u8;

u8 code AA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 x,BB[8]={0};

void delay(u16 i)
{
 	while(i--);
}

void T0Init()			  //��ʱ����ʼ��	
{
 	TR0=1;            //������ʱ��
	TMOD|=0x01;        //��ʱ������ģʽ1��16λ��ʱ����ģʽ
	TH0=0xfc;		   //��ֵ  ��ʱ1����
	TL0=0x66; 		   //��ֵ
	ET0=1;				//�򿪶�ʱ���ж�
	EA=1;				//�����ж�
}

void Acc()					   //�������ʾ
{
   u8 i;
   for(i=0;i<8;i++)
   {
   	  switch(i)
	  {
	   case(7):
	            LSC=1, LSB=1, LSA=1;break;				//ʮʱ
	   case(6):											
	            LSC=1, LSB=1, LSA=0;break;				//ʱ
	   case(5):
	            LSC=1, LSB=0, LSA=1;break;				//����
	   case(4):
	            LSC=1, LSB=0, LSA=0;break;				//ʮ��
	   case(3):
	            LSC=0, LSB=1, LSA=1;break;				//��
	   case(2):
	            LSC=0, LSB=1, LSA=0;break;				//����
	   case(1):											
	            LSC=0, LSB=0, LSA=1;break;				//ʮ��
	   case(0):											
	            LSC=0, LSB=0, LSA=0;break;				//��
	  }
	  if(i!=2&&i!=5)
	  {
	    	P0=AA[BB[i]];
	  }
	  else
	  {
	   		P0=0x40;
	  }
	  delay(100);
	  P0=0x00;
   }
}

void Count(u16 s)			   //���ִ���
{
	u8 i,m,h;
	u16 n;
	n=1;
	if(s==60)
	{
		x=0;
		s=0;
		m++;
	}
	if(m==60)
	{
	 	m=0;
		h++;
	}	
	for(i=0;i<2;i++)
	{
 		BB[i]=s/n%10;
		BB[i+3]=m/n%10;
		BB[i+6]=h/n%10;
		n*=10;
	}
}

void Tiem0() interrupt 1
{
    u16 i;       
	TH0=0xfc;
	TL0=0x66;
	i++;
	if(i==1000)	//1000ms �� 1s
	{
		i=0;	
	    x++;
	}
}

void main()
{
	x=0;
 	T0Init();
	while(1)
	{
	 	Count(x);
		Acc();
	}
}
 