#include<reg52.h>
#include<XPT2046.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 a,b,c,d,z;
u16 x=0;

void delay(u16 i)
{
 	while(i--);
}

void Shuju()		  //处理数据，千、百、十、个位
{
	
	a=x%10;
	b=x/10%10;
	c=x/100%10;
	d=x/1000%10;
}

void Acc()			 //数码管显示
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BAA[a];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=BAA[b];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=BAA[c];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=1;
	   P0=BAA[d];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=0;
	   P0=0x00;
	   delay(50);
	   P0=0x00;
}

void main()
{
 	u8 t=0;
	while(1)
	{
		if(t>=50)
		{
			t=0;
			x=XPT2046_AD(0xa4);	//电位器0x94、热敏0xd4、光敏0xa4、外接0xe4
		}
		t++;
		Shuju();
		Acc();
	}	
}
















	