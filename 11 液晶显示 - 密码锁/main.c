/*初始密码位1， 密码范围0~65535*/
              
/*     4*4按键排列       */
/* 		1 2 3  开关
   		4 5 6  设置密码
   		7 8 9  *
   		c 0 OK /         */

#include<reg52.h>
#include<lcd1602.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
	 
#define jian P1

typedef unsigned int u16;
typedef unsigned char u8;

u8 BB[8];
u8 n=0,z,m,kg,se,o;
u16 y,j1,mi;

void Key();
void xian(u16 x);
void suan();

void delay(u16 i)
{
 	while(i--);
}


void Key()	 //0~9输入 、    与suan()搭配输入数字及运算方式
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
				case(0x0e): suan(); goto AA;		 //将y的值赋给x1，并清0
			}  
			jian=0xf0;
			switch(jian)
			{
			 	case(0x70): x=x,    y=y*10+x;  break;
				case(0xb0): x=x+3,  y=y*10+x;  break;
				case(0xd0): x=x+6,  y=y*10+x;  break;
				case(0xe0): m=m-1;	Write2(61);					
							if(m==2)
							{
							 	y=y*10;	
							}
							if(m==3)
							{
							 	y=0;
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
	z=0;					//用来决定运算方式1+  2-  3*  4/
	jian=0xf0;
	switch(jian)
	{
	 	case(0x70): z=1;  kg=~kg;  break;	 //  开关
		case(0xb0): z=2;  se=~se;  break;	 //  设置密码
		case(0xd0): z=3;  break;	 //  *
		case(0xe0): z=4;  break;	 //  /
	}	
}


void xian(u16 x)			   //数字处理，并显示在lcd屏上
{
	u8 i,j;
	u16 n,k;
	n=1;
	j=0;
	k=x;
	while(k!=0)	  //判断位数
	{
	 	k=k/10;
		j++;
	}
	if(m!=1)      //回退重写，以保证数字不重复
	{
		for(i=1;i<j;i++)
		{
	 		Write1(0x10);
		}
	}
	for(i=0;i<j;i++)
	{
 		BB[i]=x/n%10;
		n*=10;
	}
	for(i=0;i<j;i++)
	{
	 	Write2(BB[j-i-1]+'0');	
	}

}

void Lock()
{
	u16 hu;
 	if(kg!=0)
	{
		while(o==0 && se==0 && kg!=0)
		{
		 	hu=y;
			xian(y);
			while(hu==y && se==0 && kg!=0 && m!=1)
			{
			 	Key();
			}
			if(m==1)
			{
			 	if(mi==hu)
				{
				 	o=1;
				}
				else
				{
					Write1(0x01);
				 	Write2(88);
					Write2(88);
					Write2(88);
					while(m!=3)
					{
					 	Key();	
					}
					Write1(0x01);
					Write2(63);
				}
			}
			m=4;
		}
		if(se!=0)
		{
			Write2(63);
		 	while(m!=1 && se!=0)
			{
				hu=y;
				xian(y);
				while(hu==y && m!=1 && se!=0)
				{
			 		Key();
				}
			}
			if(se!=0)
			{
				se=0;
				mi=y;
				y=0;
				m=4;
			}	
		}
	}
}

void main()
{
	u16 hu;	//用以避免重复刷屏
 	y=se=o=0;
	mi=kg=1;
	LCD1602Init();
	Write2(63);	
	while(1)
	{
		Lock();
		while(mi==y || kg==0)
		{
			Write2(33);
		}
	}	
}