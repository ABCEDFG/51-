#ifndef __DS1302_H_
#define __DS1302_H_

#include<reg52.h>
#include<intrins.h>

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16 
#define u16 unsigned int
#endif

sbit CLK=P3^6;
sbit SDA=P3^4;
sbit CE=P3^5;

void DS1302_Write(u8 addr,u8 dat);
u8 DS1302_Read(u8 addr);
void DS1302_Init();
void DS1302_Shi();

extern u8 SHU[7];  

#endif
