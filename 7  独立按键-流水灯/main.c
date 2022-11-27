/*按k1键，流水灯移动一位*/

#include <reg52.h>
#include <intrins.h>

#define led P2
sbit k1=P3^1;

typedef unsigned int u16;
typedef unsigned char u8;

void delay(u16 i)
{
   while(i--);
}

void main()
{	
  u8 a=0;
 led=0xfe;

while(1)
{ 
if(k1==0)
{
   delay(1000);
   if(k1==0)
   {
	  if(a<7)
	  {
	  led=_crol_(led,1);
	  a+=1;
	  }
	  
	  else
	 {
	  if(a<14)
	  {
	  led=_cror_(led,1);
	  a+=1;
	  }
	  else 
	  {
	  	a=1;
        led=_crol_(led,1);
	  }
	  }
	   while(!k1);
	  }
	   }
	  }
   }
