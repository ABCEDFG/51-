#include <XPT2046.h>

void XPT2046_Write(u8 dat)
{
 	u8 i;
	CLK=0;
	for(i=0;i<8;i++)
	{
	 	RU=dat>>7;   //从最高位开始
		dat<<=1;
		CLK=0;   //上升沿放置数据
		CLK=1;
	}
}

u16 XPT2046_Read()
{
 	u16 i,dat=0;
	CLK=0;
	for(i=0;i<12;i++)
	{
		dat<<=1;   //从最高位开始
		CLK=1;
		CLK=0;
		dat|=CHU;
	}	
	return dat;
}

u16 XPT2046_AD(u8 x)   //AD转换
{
 	u8 i;
	u16 n;
	CLK=0;
	CS=0;
	XPT2046_Write(x);   //选择读取位置
	i=6;
	while(i--);   //延时等待转换结果
	CLK=1;   //发送一个周期，清除UBSY
	_nop_();
	_nop_();
	CLK=0;
	_nop_();
	_nop_();
	n=XPT2046_Read();
	CS=1;
	return n;
}