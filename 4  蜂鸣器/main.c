#include <reg51.h>

sbit beep=P1^5;

typedef unsigned int u16;
typedef unsigned char u8;

void delay(u16 i)
{
  while(i--);
}

void main()
{
	while(1)
	{
  		beep=~beep;	
		delay(4410);
  	}
}