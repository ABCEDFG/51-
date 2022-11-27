#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit led1=P2^0;

void delay(u16 i)
{
   while(i--);
}

void main()
{
   while(1)
   {
   	  led1=~led1;
	  delay(50000);	//—” ±0.45s
   }

}