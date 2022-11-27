#ifndef _LCD1602_H
#define _LCD1602_H

#include<reg52.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int 
#endif

#define LCD P0

sbit RS=P2^6;
sbit EN=P2^7;
sbit RW=P2^5;

void LCD1602Init();
void Write2(uchar dat);
void Write1(uchar x);

#endif
