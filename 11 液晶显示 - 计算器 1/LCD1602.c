#include<lcd1602.h>

void delay1ms(uint c)   //延时1ms
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

void Write1(uchar x)	//写入命令
{
 	EN=0;
	RS=0;		 	//输入命令
	RW=0;		 	//RW=1时读
	LCD=x;
	delay1ms(1);
	EN=1;			 //读取信息
	delay1ms(1);
	EN=0;			 //下降延执行
}

void Write2(uchar dat)	//写入数据、一字节
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

void LCD1602Init()	 //液晶初始化
{
	Write1(0x38);	//光标右移、屏幕不动
	Write1(0x01);	//清屏
	Write1(0x0e);	//显示开、有光标、光标闪烁
//	Write1(0x06);	//
	Write1(0x80);	//初始输入地址 1.1
}

