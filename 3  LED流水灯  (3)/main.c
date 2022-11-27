#include <reg52.h>
#include <intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

#define led P2

void delay(u16 i)
{
  while(i--);
}

void main()
{
 u8 a=0;
 led=0xfe;
 delay(50000);
 while(a<7)
 {
   led=_crol_(led,1);
   delay(50000);
   a+=1;
 }
 while(a>1)
 {
   led=_cror_(led,1);
   delay(50000);
   a-=1;
 }
}