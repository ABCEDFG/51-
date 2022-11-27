#include <reg52.h>
#include <wendu.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 AA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 CC[]={0x00,0x40};
u8 a,b,c,d,z;

void delay(u16 i)
{
 	while(i--);
}

void Shuju(int x)		  //处理数据，千、百、十、个位
{
	float t;
	if(x<0)
	{
	 	z=1;
		x=x-1;
		x=~x;
		t=x;
		x=t*0.0625*100+0.5;
	}
	else
	{
		z=0;
		t=x;
		x=t*0.0625*100+0.5;
	}
	a=x%10;
	b=x/10%10;
	c=x/100%10;
	d=x/1000%10;
}

void Acc()			 //数码管显示
{
	   LSC=0, LSB=0, LSA=0;
	   P0=AA[a];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=AA[b];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=0x80;
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=1;
	   P0=AA[c];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=0;
	   P0=AA[d];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=1;
	   P0=CC[z];
	   delay(50);
	   P0=0x00;
}

void main()
{
	while(1)
	{
		Shuju(DS18B20_Wendu());
		Acc();	
	}

}