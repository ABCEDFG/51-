/*现象 数码管从 0 开始计数*/
/*范围0~9999 9999 */

#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit ALSC=P2^4;

sbit a1=P3^0;
sbit b1=P3^1;
sbit c1=P3^2;
sbit d1=P3^3;

typedef unsigned int u16;
typedef unsigned char u8;

u8 code BAA[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};

u8 a,b,c,d,e,f,g,h;
u16 p,o,z;

void delay(u16 i)
{
   while(i--);
}

void Shu()	   //数字处理
{
    o++;	   //0~9999
	a=o%10;
	b=o/10%10;
	c=o/100%10;
	d=o/1000%10;
	if(o>=9999)	 //高4位z  以突破65535的限制
	{
	 	if(z==9999)
		{   
    		z=0; 
		} 
		else
		{
     		z++;
		}
		e=z%10;
	 	f=z/10%10;
	 	g=z/100%10;
	 	h=z/1000%10;
	 	o=0;
	}
}

void Acc()	//数码管显示
{
	   char A,B;
	   A=1;
	   B=0;
	   a1=A; b1=c1=d1=B;
	   P1=BAA[a];
	   delay(50);
	   P0=0x00;

	   b1=A; a1=c1=d1=B;
	   P1=BAA[b];
	   delay(50);
	   P0=0x00;

	   c1=A; a1=b1=d1=B;
	   P1=BAA[c];
	   delay(50);
	   P0=0x00;

	   d1=A; a1=b1=c1=B;
	   P1=BAA[d];
	   delay(50);
	   P0=0x00;

}


  																
void main()
{
   z=0;
   o=0;
   while(1)
   {
      p=300;
	  Shu();
   		while(p)
		{
   	 		 Acc();
			 p--;
		} 
   }
}