#include <reg51.h>
#include <intrins.h>
 
sbit CLK=P3^6;
sbit RCLK=P3^5;
sbit SDA=P3^4;

typedef unsigned int u16;
typedef unsigned char u8;

u8 ledwei[]={0x7f,0xfd,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
u8 shi[]={0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

void delay(u16 i)
{
 	while(i--);
}

void dian(u8 x)	  //
{
	u8 a;
	CLK=0;
 	RCLK=0;
	for(a=0;a<8;a++)
	{
	 	SDA=x>>7;
		x<<=1;
		CLK=1;
		_nop_();
		_nop_();
		CLK=0;
		_nop_();
	}
	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}

void you()
{
 	u8 i;
	for(i=0;i<8;i++)
	{
	 	ledwei[i]=_cror_(ledwei[i],1);
	}
}

void shang()
{
	u8 i;
	for(i=0;i<8;i++)
	{
	 	shi[i]=_crol_(shi[i],1);
	}
}	

void xia()
{
 	u8 i;
	for(i=0;i<8;i++)
	{
	 	shi[i]=_cror_(shi[i],1);
	}
}

void zuo()
{
 	u8 i;
	for(i=0;i<8;i++)
	{
	 	ledwei[i]=_crol_(ledwei[i],1);
	}
}

void main()
{
	u8 i,n,a,s;
	n=0;
	s=3;
 	while(1)
	{	
		n++;
		for(a=0;a<25;a++)
		{
	 		for(i=0;i<8;i++)
			{
				P0=ledwei[i];
				dian(shi[i]);
				delay(100);
				dian(0x00);
			}
		}
		if(n==22||n==44||n==58||n==64||n==69||n==81||n==101)
		{
		 	s=0;		//ио
		}
		if(n==8||n==34||n==52||n==62||n==66||n==74||n==90||n==114)
		{
		 	s=1;		//об
		}
		if(n==15||n==39||n==55||n==63||n==67||n==77||n==95||n==121)
		{
		 	s=2;		//вС
		}
		if(n==28||n==48||n==60||n==65||n==71||n==85||n==107)
		{
		 	s=3;		//ср
		}
		switch(s)
		{
			case(0): shang(); break;
		 	case(1): xia(); break;
			case(2): zuo(); break;
			case(3): you(); break;
		}
	}
}

	