#include <reg51.h>
#include <intrins.h>

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

typedef unsigned int u16;
typedef unsigned char u8;

void Fasong(u8 dat)
{
   u8 a;
   SRCLK=0;
   RCLK=0;
   for(a=0;a<8;a++)
   {
   	  SER=dat>>7;
	  dat<<=1;
	  SRCLK=1;
	  _nop_();
	  _nop_();			    
	  SRCLK=0;

   }
   RCLK=1;
   _nop_();
   _nop_();
   RCLK=0;
}

void main()
{
  Fasong(0x80);
  P0=0x7f;
  _nop_();
  _nop_();
}