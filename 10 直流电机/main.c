#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit motor=P1^0;

void delay(u16 i)
{
   while(i--);
}

void main()
{
   while(1)
   {
       motor=1;
	   delay(1);
   }		 
}