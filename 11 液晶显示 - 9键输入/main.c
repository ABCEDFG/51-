/****************************************************************************
���ã������þ��󰴼�����Ӣ����ĸ�����ֺͿո񣬲���LCD1602����ʾ��
4*4������   1 2 3 ��	  ��   ABC   DEF   ��
			4 5 6 ��	  GHI  JKL	 MNO   ��
			7 8 9 ��	 PORS  TUV  WXYZ   ��
			s 0	�ڿ�	  s    �ո�	 ��	   ��
���� ���� ��9�����붨����ͬ�� s ��ʾ����һλ���� ��ʾδ���壬0 ��ʾ�ո� 

����������k1 �л���Сд������
******************************************************************************/

#include<reg52.h>
#include<lcd1602.h>

typedef unsigned int u16;
typedef unsigned char u8;

#define key P1

sbit k1=P3^1;

u8 AA[50];
u8 BB[5];  
u8 x0,hu,n0,fz,a;

void delay(u16 i)
{
 	while(i--);
}

void Key1()
{
	u8 b;
	b=0;	//���Է�ֹ�����ظ�
 	key=0x0f;
	if(key!=0x0f)
	{
	 	delay(1000);
		if(key!=0x0f)
		{
		 	switch(key)
			{
			 	case(0x07): x0=1; break;
				case(0x0b): x0=2; break;
				case(0x0d): x0=3; break;		
			}				 
			key=0xf0;
			switch(key)
			{
			 	case(0x70): x0+=0; break;
				case(0xb0): x0+=3; break;
				case(0xd0): x0+=6; break;
				case(0xe0): x0+=9; break;
			}
			while( (b<50) && (key!=0xf0) )
			{
			 	delay(1000);
				b++;
			}
		}
	}
}

void Key2()
{
	if(k1==0)	 //�л���Сд��fz Ϊż��ʱ��д
	{
	 	delay(1000);
		if(k1==0)
		{
			fz++;
			switch(fz%3)
			{
			 	case(0): a=0;  break;
				case(1): a=32; break;
				case(2): a=1;  break;
			}
		}
		while(k1==0);
	}
}	

void Letter()
{
	u8 x,i,n;
 	switch(x0)
	{
	 	case(2):  n=3; x='A'; break;   
		case(3):  n=3; x='D'; break;
		case(4):  n=3; x='G'; break;
		case(5):  n=3; x='J'; break;
		case(6):  n=3; x='M'; break;
		case(7):  n=3; x='P'; break;
		case(8):  n=3; x='T'; break;
		case(9):  n=4; x='W'; break;
		case(10): n=9; n0--;  break;  //��һ��
		case(11): n=1; x=' '; break;  //�ո�
	}
	if(n!=9&&a!=1) //�˸�����ʱ��
	{
		if(x>64)
		{
			Write1(0xc0);     //�ڶ��е�1��
			for(i=0;i<n;i++)
			{
			 	BB[i]=x+a;
				x++;
				Write2(BB[i]);
			}
		}
		x0=100;				  
		while( x0==100 && n!=1 )  //ѡ����ĸ 1 2 3   4 
		{
			Key1();
		}
		if(n!=1)
		{
			AA[n0++]=BB[x0-1];
		}
		else
		{
			AA[n0++]=' ';
		}
	}
	else
	{
	 	if(a==1 && (x0<10||x0==11))
		{
			if(x0!=11)
			{
		 		AA[n0++]=x0+'0';  //��������
			}
			else
			{
			 	AA[n0++]='0';
			}
		}
	}	
	Write1(0x01);	  //����
	for(i=0;i<n0;i++) //��������
	{
		Write2(AA[i]);
	}		
}

void main()
{
	fz=a=0;	 //��ʼĬ��Ϊ��д
	LCD1602Init();
	while(1)
	{
		x0=100;
		while(x0==100)
		{
		 	Key1();
			Key2();	  
		}
		Letter();
	}
}


