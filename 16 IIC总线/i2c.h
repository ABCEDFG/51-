#ifndef _I2C_H_
#define _I2C_H_

#include <reg52.h>

#ifndef u16 
#define u16 unsigned int
#endif

#ifndef u8
#define u8 unsigned char
#endif

sbit SDA=P2^0;
sbit SCL=P2^1;

u8 At24c02_Read(u8 addr);
void At24c02_Write(u8 addr,u8 dat);

#endif
