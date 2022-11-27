#include<reg51.h>
#include<intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;

u8 zhong[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
u8 OO[]={0x00,0x00,0x3e,0x41,0x41,0x41,0x3e,0x00};

void delay(u16 i)
{
 	while(i--);
}

void Zhong(u8 a)
{
	u8 b;
	SRCLK=0;
	RCLK=0;
 	for(b=0;b<8;b++)
	{
	 	SER=a>>7;
		a<<=1;
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
   u8 c,i;
   while(1)
   {
   		for(i=0;i<100;i++)
		{
 		for(c=0;c<8;c++)
		{
	 		P0=zhong[c];
			Zhong(OO[c]);
			delay(100);
			Zhong(0x00);
		}
		}	
		for(i=0;i<8;i++)
		OO[i]=_crol_(OO[i],1);
}	}