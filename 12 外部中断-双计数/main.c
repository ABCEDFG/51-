/*现象 数码管从 0 开始计数*/
/*范围0~9999 */
/*，x y 双计数、都是从0开始, 按k3键切换，x 计数时 y 停止计数、反之亦然*/

#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit ALSC=P2^4;
sbit k3=P3^2;
sbit led=P2^0;


typedef unsigned int u16;
typedef unsigned char u8;

u8 code BAA[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};

u8 a,b,c,d,e,f,g,h,kg;
u16 p,o,z1,z2;

void delay(u16 i)
{
   while(i--);
}

void Init0()
{
 	IT0=1;
	EX0=1;
	EA=1;
}

void Shu(u16 o)	   //数字处理
{

	a=o%10;
	b=o/10%10;
	c=o/100%10;
	d=o/1000%10;
	if(o>=9999)	 //高4位z1 z2  以突破65535的限制
	{
		if(kg!=0)
		{
			 if(z1==9999)
			{   
	    		z1=0; 
			}
			else
			{ 
				z1++;
			}
		}
		else
		{
		 	 if(z2==9999)
			{   
	    		z2=0; 
			}
			else
			{ 
				z2++;
			}

		}
	}
	if(kg!=0)
	{
		e=z1%10;
		f=z1/10%10;
		g=z1/100%10;
		h=z1/1000%10;
	}
	else
	{
		e=z2%10;
		f=z2/10%10;
		g=z2/100%10;
		h=z2/1000%10;
	}
}

void Acc()	//数码管显示
{
	   ALSC=0, LSB=0, LSA=0;
	   P0=BAA[a];
	   delay(50);
	   P0=0x00;

	   ALSC=0, LSB=0, LSA=1;
	   P0=BAA[b];
	   delay(50);
	   P0=0x00;

	   ALSC=0, LSB=1, LSA=0;
	   P0=BAA[c];
	   delay(50);
	   P0=0x00;

	   ALSC=0, LSB=1, LSA=1;
	   P0=BAA[d];
	   delay(50);
	   P0=0x00;

	   ALSC=1, LSB=0, LSA=0;
	   P0=BAA[e];
	   delay(50);
	   P0=0x00;

	   ALSC=1, LSB=0, LSA=1;
	   P0=BAA[f];
	   delay(50);
	   P0=0x00;

	   ALSC=1, LSB=1, LSA=0;
	   P0=BAA[g];
	   delay(50);
	   P0=0x00;

	   ALSC=1, LSB=1, LSA=1;
	   P0=BAA[h];
	   delay(50);
	   P0=0x00;

}


  																
void main()
{
	u16 x,y;
   z1=z2=kg=x=y=0;
   Init0();
   while(1)
   {
      p=1;
	  if(kg!=0)
	  {
	  	x++;
	  	Shu(x);
		if(x>=9999)
		{
		 	x=0;
		}
	  }
	  else
	  {
	   	y++;
		Shu(y);
		if(y>=9999)
		{
		 	y=0;
		}
	  }
   		while(p)
		{
   	 		 Acc();
			 p--;
		} 
   }
}

void deng() interrupt 0
{
 	delay(1000);
	if(k3==0)
	{
	 	kg=~kg;
	}
}