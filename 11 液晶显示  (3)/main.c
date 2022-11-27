#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit RS=P2^6;
sbit RW=P2^5;
sbit EN=P2^7;

void Mang_a()		   //�ж�Һ��æ��æ
{
 	u8 a;
	P0=0xff;
	RS=0;
	RW=1;
	do
	{
	 	EN=1;
		a=P0;
		EN=0;
	} while(a & 0x80);
	EN=1;
}

void Xie_b(u8 b)	  //дLCD1602ָ��	һ���ֽ�
{
 	Mang_a();
	RS=0;
	RW=0;
	P0=b;
	EN=0;
	EN=1;
}		

void Xian_c(u8 c)	   //дһ���ֽڵ�����
{
 	Mang_a();
	RS=1;
	RW=0;
	P0=c;
	EN=0;
	EN=1;
}

void main()
{
    Xie_b(0x01);	 //����
 	Xie_b(0x38);	 //����16*2��ʾ
	Xie_b(0x0e);	 //����ʾ����ꡢ�����˸
	Xie_b(0x06);	 //д�����ݺ�������  ��ַָ������
	Xie_b(0x80 | 0x04);	 //��ʾ��ַ��������1.1
	Xian_c(5+'0');
	Xian_c(6+'0');
	Xian_c(7+'0');
	Xian_c(8+'0');	
	while(1);
}					   