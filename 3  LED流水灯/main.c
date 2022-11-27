#include<reg52.h>
#include<intrins.h>
#define led P2

typedef unsigned int u16;
typedef unsigned char u8;

void delay(u16 i)
{
   while(i--);
}

void main()
{
   u8 a;
   led=0xfe;	        //0111 1111	 ÓÒ7×ó0
   	  for(a=0;a<7;a++)
	  {
	     led=_crol_(led,1);
		 delay(50000);  
	  }
	  for(a=0;a<7;a++)
	  {
	     led=_cror_(led,1);
		 delay(50000);
	  }
}