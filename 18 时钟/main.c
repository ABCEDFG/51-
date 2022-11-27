#include<reg52.h>
#include<ds1302.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 a,b,c,d,e,f;

void delay(u16 i)
{
 	while(i--);
}

void Shuju()		  
{
	a=SHU[4]/16;
	b=SHU[4]&0x0f;
	c=SHU[5]/16;
	d=SHU[5]&0x0f;
	e=SHU[6]/16;
	f=SHU[6]&0x0f;
}

void Acc()			 // ˝¬Îπ‹œ‘ æ
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BAA[f];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=BAA[e];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=0x40;
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=1;
	   P0=BAA[d];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=0;
	   P0=BAA[c];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=0, LSA=1;
	   P0=0x40;
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=1, LSA=0;
	   P0=BAA[b];
	   delay(50);
	   P0=0x00;

	   LSC=1, LSB=1, LSA=1;
	   P0=BAA[a];
	   delay(50);
	   P0=0x00;
}

void main()
{
  DS1302_Init();
  while(1)
  {
		DS1302_Shi();
   		Shuju();
		Acc();
  }
}