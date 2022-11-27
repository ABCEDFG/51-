#include <reg51.h>

sbit b1=P3^2;
sbit a1=P3^3;

sbit a2=P5^4;
sbit b2=P5^5;

void main()
{
 	while(1)
	{
 		a1=1;   //ÓÒÂÖ
		b1=0;
		a2=1;   //×óÂÖ
		b2=0;	
	}
}