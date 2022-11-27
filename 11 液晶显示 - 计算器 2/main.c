/*可以计算两个自然数的四则运算，结果也是自然数，数字范围0~65535*/
/*可以显示  +  -  *  /  =                                      */
/* 4*4按键排列 */
/* 		1 2 3 +
   		4 5 6 -
   		7 8 9 *
   		c 0 = /    */

//Bug  *10时退格-1，

#include<reg52.h>
#include<lcd1602.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
	 
#define jian P1

typedef unsigned int u16;
typedef unsigned char u8;

u8 BB[8];
u8 n=0,z,m;
u16 y,x1,x2,j1;	  //  y 用来个 x1 x2 赋值，  x1 x2 用以运算

void yun();
void Key();
void xian(u16 x);
void Acc();
void suan();

void delay(u16 i)
{
 	while(i--);
}

void yun()   //z决定运算方式
{
	u16 hu;	 //用以避免重复刷屏
	x1=y;
	delay(5000);
	y=0;
	xian(y);
 	while(jian==0x70||jian==0xb0||jian==0xd0||jian==0xe0);	 //防止过度输入
	while(m!=1)								//输入第二个数的值
	{
		xian(y);
		hu=y;
		while(hu==y&&m!=1)
		{
			Key();
		}
	}
	x2=y;
	switch(z)	 //两个数计算
	{
	 	case(1): y=x1+x2; break;
		case(2): y=x1-x2; break;
		case(3): y=x1*x2; break;
		case(4): y=x1/x2; break;
	}
}

void Key()	 //0~9输入 、    与suan()搭配输入数字及运算方式
{
	u8 b=0,x=0;
	m=0;	 // 为 1 时：=   为 2 时：输入 0    为 3 时： c 
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
				case(0x0e): suan(); goto AA;		 //将y的值赋给x1，并清0
			}  
			jian=0xf0;
			switch(jian)
			{
			 	case(0x70): x=x,  y=y*10+x; break;
				case(0xb0): x=x+3,y=y*10+x; break;
				case(0xd0): x=x+6,y=y*10+x; break;
				case(0xe0): m=m-1;	Write2(61);					
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
			while((b<50)&&(jian!=0xf0))	 //防止输入多次
			{
			 	delay(1000);
				b++;
			}
		} 
    }
}

void suan()				//选择运算方式
{
	z=0;					//用来决定运算方式1+  2-  3*  4/
	jian=0xf0;
	switch(jian)
	{	    //	   运算方式  显示符号
	 	case(0x70):  z=1,  Write2(43);  yun();  break;	 //  +
		case(0xb0):  z=2,  Write2(45);  yun();  break;	 //  -
		case(0xd0):  z=3,  Write2(42);  yun();  break;	 //  *
		case(0xe0):  z=4,  Write2(47);  yun();  break;	 //  /
	}	
}

void xian(u16 x)			   //数字处理，并显示在lcd屏上
{
	u8 i,j;
	u16 n,k;
	n=1;
	k=x;
	j=0;
	while(k!=0)	//计算 x 的位数
	{
	 	k=k/10;
		j++;
	}
	if(m!=1)  //回退重写，以保证数字不重复
	{
		for(i=1;i<j;i++)
		{
	 		Write1(0x10);
		}
	}
	for(i=0;i<j;i++)    //将 x 的各个位的数赋给数组 BB
	{
 		BB[i]=x/n%10;
		n*=10;
	}
	for(i=0;i<j;i++)	//在屏上显示数字
	{
	 	Write2(BB[j-i-1]+'0');	
	}

}

void main()
{
	u16 hu;	//用以避免重复刷屏
 	y=j1=0;	//初始值
	LCD1602Init();
	while(1)
	{
	 	xian(y);
		hu=y;
		while(hu==y)
		{
		 	Key();
		}
	}
}