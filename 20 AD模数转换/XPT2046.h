#ifndef _XPT2046_H
#define _XPT2046_H

#include<reg52.h>
#include<intrins.h>

#ifndef u8 
#define u8 unsigned char 
#endif 

#ifndef u16
#define u16 unsigned int
#endif

sbit CHU=P3^7;	//数据输出
sbit CLK=P3^6;
sbit RU=P3^4;   //数据输入
sbit CS=P3^5;		

u16 XPT2046_AD(u8 x);

#endif
