#include <reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit beep=P1^5;
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;



void delay(u16 i)
{
   while(i--);
}
void main()
{
   if(k1==0)
   {
   	  delay(1000);
	  if(k1==0)
	  {
	  	while(k2!=0&&k3!=0&&k4!=0)
		{
		beep=~beep;
		delay(441);
		 
	  }
	   while(k1==0);
   }
   }
      if(k2==0)
   {
  
   

   	  delay(1000);
	  if(k2==0)
	  {

	  while (k1!=0&&k3!=0&&k4!=0)
	  {
		beep=~beep;	
		delay(495); 
	  }
	  
	   while(k2==0);
   }
   }
      if(k3==0)
   
   {
   	  delay(1000);
	  if(k3==0)
	  while(k4!=0)
	  {
		beep=~beep;
		delay(556); 
	  }
	   while(k3==0);
   }
  
      if(k4==0)
   {
   	  delay(1000);
	  if(k4==0)
	  {
	  while(k1!=0&&k2!=0&&k3!=0)
	  {
		beep=~beep;
		delay(589); 
	   }
	   while(k4==0);
   }  } 
  }