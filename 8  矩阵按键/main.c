#include<reg52.h>

sbit AAA=P2^2;
sbit AAB=P2^3;
sbit AAC=P2^4;
	 
#define jian P1
#define deng P0

typedef unsigned int u16;
typedef unsigned char u8;

code AA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

u8 a;

void delay(u16 i)
{
    while(i--);    
}
void Jian()
{
    jian=0x0f;
    if(jian!=0x0f)
    {
	    u8 b=0;
   	 	delay(1000);
		if(jian!=0x0f)
		{
		 	switch(jian)
			{
			 	case(0x07):	a=0; break;
				case(0x0b): a=1; break;
				case(0x0d): a=2; break;
				case(0x0e): a=3; break;		
			}
			jian=0xf0;
			switch(jian)
			{
			 	case(0x70): a=a; break;
				case(0xb0): a=a+4; break;
				case(0xd0): a=a+8; break;
				case(0xe0): a=a+12; break;
			}
			while((b<50)&&(jian!=0xf0))
			{
			 	delay(1000);
				b++;
			}
		} 
    }

}

void main()
{
	AAA=0;
	AAB=0;
	AAC=0;
	while(1)
	{
	 	Jian();
		deng=AA[a];
}	}