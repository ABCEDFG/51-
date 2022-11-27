/*k1¼üÓÒÒÆledµÆÒ»Î»£¬k2×óÒÆ*/
/*k3¼üÓÒÒÆledµÆÁ½Î»£¬k4×óÒÆ*/

#include <reg52.h>
#include <intrins.h>

#define led P2
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

typedef unsigned int u16;
typedef unsigned char u8;

void delay(u16 i)
{
   while(i--);
}

void keypros()
{
   if(k1==0)
   {
   	  delay(1000);
	  if(k1==0)
	  {	 
		   led=_crol_(led,1);	 
	  }
	  while(k1==0);
   }
      if(k2==0)
   {
   	  delay(1000);
	  if(k2==0)
	  {	 
		   led=_cror_(led,1);	 
	  }
	  while(k2==0);
   }
      if(k3==0)
   {
   	  delay(1000);
	  if(k3==0)
	  {	 
		   led=_crol_(led,2);	 
	  }
	  while(k3==0);
   }
         if(k4==0)
   {
   	  delay(1000);
	  if(k4==0)
	  {	 
		   led=_cror_(led,2);	 
	  }
	  while(k4==0);          
}
	}

void main()
{
led=0xfe;
while(1)
{ 
   keypros();
   }
}