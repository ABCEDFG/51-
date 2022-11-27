#include <STC15.h>

typedef unsigned char u8;
typedef unsigned int u16;

sbit you1=P3^3;	//����
sbit you2=P3^2;

sbit zuo1=P5^5;	//����
sbit zuo2=P5^4;

sbit bizuo=P1^2;	//���� �����
sbit biyou=P1^0;	//���� �Һ���

sbit xunzuo=P1^3;	//ѭ�� �����
sbit xunyou=P1^1;	//ѭ�� �Һ���

sbit key=P1^5;	//����

sbit led1=P1^4;	//��β�� ��
sbit led2=P3^7;	//��β�� ��

u8 x=0;

void delay(u16 i)
{
	while(i--);
}

void Qian()	//ǰ��
{
	u8 i;
	you2=0;
	zuo2=0;
	for(i=0;i<100;i++)	//������� ʹ������ת����ͬ
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

void Hou()	//����
{
	u8 i;
	you1=0;
	zuo1=0;
	for(i=0;i<100;i++)
	{
		if(i<97)
		{
			you2=1;
		}
		else
		{
			you2=0;
		}
		if(i<99)
		{
			zuo2=1;
		}
		else
		{
			zuo2=0;
		}
	}
}

void Zuo()	//���
{
	u8 i;
	zuo1=0;
	you2=0;
	for(i=0;i<11;i++)
	{
		if(i<10)
		{
			you1=1;
		}
		else
		{
			you1=0;
		}
	}
}


void You()	//�ҹ�
{
	u8 i;
	you1=0;
	zuo2=0;
	for(i=0;i<11;i++)
	{
		if(i<10)
		{
			zuo1=1;
		}
		else
		{
			zuo1=0;
		}
	}
}

void Bi()	//����
{
	//bizuo=biyou=1;
	while(bizuo==0)	//��ǰ�����ϰ���	
	{
		You();
	}
	while(biyou==0)	//��ǰ�����ϰ���
	{
		Zuo();
	}
}

void Xun()	//ѭ��
{
	while(xunzuo==1&&xunyou==0)	//�Ҳ���
	{
		Zuo();
	}
	while(xunzuo==0&&xunyou==1)	//�����
	{
		You();
	}
}

void Key()
{
	if(key==0)
	{
		delay(1000);
		if(key==0)
		{
			x=!x;
		}
		while(key==0)
		{
			if(x==0)
			{
				led1=0;	//�������ʾ����
			}
			else
			{
				led2=0;	//�ҵ�����ʾѭ��
			}
		}
		led1=1;	//�ɿ����� ����
		led2=1;
	}
}


void main()
{
	while(1)
	{
		Key();
		if(x==0)
		{
			Qian();
			Bi();
		}
		else
		{
			Qian();
			Xun();
		}
	}
}
