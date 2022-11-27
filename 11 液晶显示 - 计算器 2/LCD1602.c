#include<lcd1602.h>

void delay1ms(uint c)   //��ʱ1ms
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}   	
}

void Write1(uchar x)	//д������
{
 	EN=0;
	RS=0;		 	//��������
	RW=0;		 	//RW=1ʱ��
	LCD=x;
	delay1ms(1);
	EN=1;			 //��ȡ��Ϣ
	delay1ms(1);
	EN=0;			 //�½���ִ��
}

void Write2(uchar dat)	//д�����ݡ�һ�ֽ�
{
 	EN=0;
	RS=1;	
	RW=0;
	LCD=dat;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}

void LCD1602Init()	 //Һ����ʼ��
{
	Write1(0x38);	//������ơ���Ļ����
	Write1(0x01);	//����
	Write1(0x0e);	//��ʾ�����й�ꡢ�����˸
//	Write1(0x06);	//
	Write1(0x80);	//��ʼ�����ַ 1.1
}

