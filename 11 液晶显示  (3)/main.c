#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit RS=P2^6;
sbit RW=P2^5;
sbit EN=P2^7;

void Mang_a()		   //判断液晶忙不忙
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

void Xie_b(u8 b)	  //写LCD1602指令	一个字节
{
 	Mang_a();
	RS=0;
	RW=0;
	P0=b;
	EN=0;
	EN=1;
}		

void Xian_c(u8 c)	   //写一个字节的数据
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
    Xie_b(0x01);	 //清屏
 	Xie_b(0x38);	 //设置16*2显示
	Xie_b(0x0e);	 //开显示、光标、光标闪烁
	Xie_b(0x06);	 //写入数据后光标右移  地址指针右移
	Xie_b(0x80 | 0x04);	 //显示地址————1.1
	Xian_c(5+'0');
	Xian_c(6+'0');
	Xian_c(7+'0');
	Xian_c(8+'0');	
	while(1);
}					   