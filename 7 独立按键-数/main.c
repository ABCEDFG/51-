/*k1πÈ¡„°¢k2º”1°¢k3ºı1°¢k4ø™πÿ…˘“Ù*/

#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;
sbit beep=P1^5;

typedef unsigned int u16;
typedef unsigned char u8;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 a,b,c,d,e,f,z=0;
u16 x=0;
u16 t=0;
void delay(u16 i)
{
   while(i--);
}

void shu()
{
 	a=x%10;
	b=x/10%10;
	c=x/100%10;
	d=x/1000%10;
	e=x/10000%10;
	f=x/100000%10;
}

void Acc()
{
   u8 i;
   for(i=0;i<8;i++)
   {
   	  switch(i)
	  {
	   case(0):
	       	   	LSC=1, LSB=1, LSA=1;P0=0x00;break;
	   case(1):
	            LSC=1, LSB=1, LSA=0;P0=0x00;break;
	   case(2):
	            LSC=1, LSB=0, LSA=1;P0=BAA[f];break;
	   case(3):
	            LSC=1, LSB=0, LSA=0;P0=BAA[e];break;
	   case(4):
	            LSC=0, LSB=1, LSA=1;P0=BAA[d];break;
	   case(5):
	            LSC=0, LSB=1, LSA=0;P0=BAA[c];break;
	   case(6):
	            LSC=0, LSB=0, LSA=1;P0=BAA[b];break;
	   case(7):
	            LSC=0, LSB=0, LSA=0;P0=BAA[a];break;
	  }
	  delay(100);
	  P0=0x00;
   }
}

void shen()		 //…˘“Ù
{
	if(z==0)
	{
	for(t=0;t<10;t++)
	{
 		beep=~beep;
		delay(441);
	}
	}
}

void jian()
{
 	 if(k1==0)
	 {
	  	delay(1000);
		if(k1==0)
		{
		 	x=0;
			shen();
		}
		while(k1==0);
	 }

	 if(k2==0)
	 {
	  	delay(1000);
		if(k2==0)
		{
		 	x+=1;
			shen();
		}
		while(k2==0);
	 }

	 if(k3==0)
	 {
	  	delay(1000);
		if(k3==0)
		{
		 	x-=1;
			shen();
		}
		while(k3==0);
	 }

	 if(k4==0)
	 {
	  	delay(1000);
		if(k4==0)
		{
		 	z=~z;
			shen();
		}
		while(k4==0);
	 }
}

void main()
{
	while(1)
	{
 		jian();
		shu();
		Acc();
	}
}