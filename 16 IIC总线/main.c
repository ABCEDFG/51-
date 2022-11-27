/*****************************************************************************
���Ա������ݣ��ϵ粻��ʧ
���� k1 �������ݣ� k2 �鿴���棬 k3 ��һ�� k4 ���� 	
******************************************************************************/
																			 
#include <reg52.h>
#include <i2c.h>

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 a,b,c,d;
char x;

void delay(u16 i)
{
 	while(i--);
}


void jian()				//���尴������
{
 	if(k1==0)			 //��������
	{
	 	delay(1000);
		if(k1==0)
		{
		 	At24c02_Write(1,x);	 //�������ݵ� 1 
		}
		while(!k1);
	}

 	if(k2==0)			  //��ȡ���������
	{
	 	delay(1000);
		if(k2==0)
		{
		 	x=At24c02_Read(1);	//�鿴�������� 1
		}
		while(!k2);
	}

 	if(k3==0)			//x++
	{
	 	delay(1000);
		if(k3==0)
		{
		 	x++;
			if(x>255)
			{
			 	x=0;
			}
		}
		while(!k3);
	}

 	if(k4==0)		   //����
	{
	 	delay(1000);
		if(k4==0)
		{
		 	x=0;
		}
		while(!k4);
	}
}

void Shuju()		  //�������ݣ�ǧ���١�ʮ����λ
{
    
	a=x%10;
	b=x/10%10;
	c=x/100%10;
	d=x/1000%10;
}

void Acc()			 //�������ʾ
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BAA[a];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=BAA[b];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=BAA[c];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=1;
	   P0=BAA[d];
	   delay(50);
	   P0=0x00;
}

void main()
{
	x=0;
	while(1)
	{
		jian();
		Shuju();
		Acc();
	}
}
