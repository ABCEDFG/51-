/*���� ����ܴ� 0 ��ʼ����*/
/*��Χ0~9999 9999 */

#include <reg52.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit ALSC=P2^4;

typedef unsigned int u16;
typedef unsigned char u8;

u8 code BAA[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};

u8 a,b,c,d,e,f,g,h;
u16 p,o,z;

void delay(u16 i)
{
   while(i--);
}

void Shu()	   //���ִ���
{
    o++;	   //0~9999
	a=o%10;
	b=o/10%10;
	c=o/100%10;
	d=o/1000%10;
	if(o>=9999)	 //��4λz  ��ͻ��65535������
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

void Acc()	//�������ʾ
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