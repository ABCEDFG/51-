/*��5v �� 01*/
/*k1ת�����k2Լ0.75��k1��k3Լ0.5����k4�رյ��*/

#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit motor=P1^0;	  //�������
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

u8 x;
void delay(u16 i)
{
   while(i--);
}

void key()
{
 	if(k1==0)
	{
	 	delay(1000);
		if(k1==0)
		{
		 	x=0;		  //ȫ�̹���
		}
		while(k1==0);
	}

	if(k2==0)
	{
	 	delay(1000);
		if(k2==0)
		{
		 	x=25;		  //0.75����
		}
		while(k2==0);
	}

	if(k3==0)
	{
	 	delay(1000);
		if(k3==0)
		{
		 	x=50;		//0.5����
		}
		while(k3==0);
	}

	if(k4==0)
	{
	 	delay(1000);
		if(k4==0)
		{
		 	x=100;	   //�ϵ�
		}
		while(k4==0);
	}
}

void dong()				//���Կ��Ƶ��
{
	u8 i,j,k;
	motor=0;
	for(i=0;i<100;i++)
	{
	 	if(i>x)			//x/100Ϊ����ʱ���
		{
		 	motor=1;
		}
	}
}	

void main()
{
	x=100;			  //��ʼʱΪ�ϵ�״̬
   while(1)
   {
       key();
	   dong();
   }		 
}