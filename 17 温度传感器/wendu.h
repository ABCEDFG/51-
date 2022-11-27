#ifndef _WENDU_H
#define _WENDU_H

#include <reg52.h>

#ifndef u16
#define u16 unsigned int
#endif

#ifndef u8
#define u8 unsigned char
#endif

sbit shu=P3^7;

int DS18B20_Wendu();

#endif
