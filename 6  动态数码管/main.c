#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

typedef unsigned int u16;
typedef unsigned char u8;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void delay(u16 i)
{
   while(i--);
}

void Acc()
{
   u8 i;
   for(i=0;i<8;i++)
   {
   	  switch(i)
	  {
	   case(0):
	            LSC=1, LSB=1, LSA=1;break;
	   case(1):
	            LSC=1, LSB=1, LSA=0;break;
	   case(2):
	            LSC=1, LSB=0, LSA=1;break;
	   case(3):
	            LSC=1, LSB=0, LSA=0;break;
	   case(4):
	            LSC=0, LSB=1, LSA=1;break;
	   case(5):
	            LSC=0, LSB=1, LSA=0;break;
	   case(6):
	            LSC=0, LSB=0, LSA=1;break;
	   case(7):
	            LSC=0, LSB=0, LSA=0;break;
	  }
	  P0=BAA[i];
	  delay(50000);
	  P0=0x00;
   }
}



void main()
{  
   while(1)
   {
   	  Acc();
   }
}