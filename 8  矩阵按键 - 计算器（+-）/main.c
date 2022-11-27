/*可以计算两个整数的四则运算，结果也是整数，可以表示正负*/
/* 4*4按键排列 */
/* 		1 2 3 +
   		4 5 6 -
   		7 8 9 *
   		c 0 = /    */

#include<reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
	 
#define jian P1

typedef int u16;
typedef unsigned char u8;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};
u8 BB[10];
u8 n=0,z,m,f;
u16 y,x1,x2;

void yun();
void Jian();
void shu(u16 x);
void Acc();
void suan();

void delay(u16 i)
{
 	while(i--);
}

void yun()		                     //z决定运算方式
{
	x1=y;
	delay(5000);
	y=0;
 	while(jian==0x70||jian==0xb0||jian==0xd0||jian==0xe0)
	{
		shu(0);
	 	Acc();
	}
	while(m!=1)
	{
		Jian();
		shu(y);
		Acc();
	}
	x2=y;
	switch(z)
	{
	 	case(1): y=x1+x2; break;
		case(2): y=x1-x2; break;
		case(3): y=x1*x2; break;
		case(4): y=x1/x2; break;
	}
}

void Jian()			   //0~9输入 、    与suan()搭配输入数字及运算方式
{
	u8 b=0,x=0;
	m=0;
    jian=0x0f;
    if(jian!=0x0f)
    {
   	 	delay(1000);
		if(jian!=0x0f)
		{
		 	switch(jian)
			{
			 	case(0x07):	x=1, m=4;   break;
				case(0x0b): x=2, m=3;   break;
				case(0x0d): x=3, m=2;   break;
				case(0x0e): suan(); goto AA;		
			}  
			jian=0xf0;
			switch(jian)
			{
			 	case(0x70): x=x,  y=y*10+x; break;
				case(0xb0): x=x+3,y=y*10+x; break;
				case(0xd0): x=x+6,y=y*10+x; break;
				case(0xe0): m=m-1;
							if(m==2)
							{
							 	y=y*10;	
							}
							if(m==3)
							{
							 	x1=x2=y=0;
							}
							
			} 
			AA: ;
			while((b<50)&&(jian!=0xf0))
			{
			 	delay(1000);
				b++;
			}
		} 
    }
}

void suan()				//选择运算方式
{
	z=0;
	jian=0xf0;
	switch(jian)
	{
	 	case(0x70): z=1, yun(); break;	 //  +
		case(0xb0): z=2, yun(); break;	 //  -
		case(0xd0): z=3, yun(); break;	 //  *
		case(0xe0): z=4, yun(); break;	 //  /
	}	
}

void shu(u16 x)			   //数字处理
{
	u8 i;
	u16 n,wei,k;
	f=0;
	wei=9;
	if(x<0)
	{
		n=10;
		k=1;
	 	x=-x;
		f=1;
		wei=0;
		while(k)	 
		{
		 	k=x/n;
			n*=10;
			wei++;  //计算位数
		}
	}
	n=1;
	for(i=0;i<8;i++)
	{
 		BB[i]=x/n%10;
		n*=10;
	}
	BB[wei]=10;
}

void Acc()					   //数码管显示
{
   u8 i;
   for(i=0;i<8;i++)
   {
   	  switch(i)
	  {
	   case(7):
	            LSC=1, LSB=1, LSA=1;break;
	   case(6):
	            LSC=1, LSB=1, LSA=0;break;
	   case(5):
	            LSC=1, LSB=0, LSA=1;break;
	   case(4):
	            LSC=1, LSB=0, LSA=0;break;
	   case(3):
	            LSC=0, LSB=1, LSA=1;break;
	   case(2):
	            LSC=0, LSB=1, LSA=0;break;
	   case(1):
	            LSC=0, LSB=0, LSA=1;break;
	   case(0):
	            LSC=0, LSB=0, LSA=0;break;
	  }
	  P0=BAA[BB[i]];
	  delay(100);
	  P0=0x00;
   }
}

void main()
{
	y=0;
	while(1)
	{
 		Jian();
		shu(y);
		Acc();
	}
}