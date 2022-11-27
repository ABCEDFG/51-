#include<reg52.h>
#include<lcd1602.h>

typedef unsigned int u16;
typedef unsigned char u8;

u8 A[9];
u16 x1,x2;
u8 n,z;

void delay(u16 i)
{
 	while(i--);
}

void shu()
{
	u16 c,b;
	c=x1;
	b=n=0;
	if(x1>9999)
	{
		z=1;
	 	x2++;
		x1=0;
	}
	while(c!=0)
	{
		A[n]=c%10;
		c=c/10;
		n++;
	} 
	if(z==1)
	{
	 	n=4;
	}
	b=x2;	
	while(b!=0)
	{
		A[n]=b%10;
		b=b/10;
		n++;
	}	
}	

void main()
{
 	u8 i;
	LCD1602Init();
	x1=x2=0;
	z=0;
	while(1)
	{
		i=0;
		shu();
		while(i<n)	
		{
		 	Write2(A[n-1-i]+'0');
			i++;
		}
		delay(50000);
		delay(50000);
		delay(2000);
		Write1(0x01);
		x1++;
	}
}