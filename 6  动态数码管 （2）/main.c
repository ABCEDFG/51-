#include <reg52.h>

sbit LASA=P2^2;
sbit LASB=P2^3;
sbit LASC=P2^4;

typedef unsigned int u16;
typedef unsigned char u8;

 u8 code smgduan[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

void main()
{ while(1)
{
LASC=0;
LASB=0;
LASA=0;
P0=smgduan[0];
P0=0x00;

LASC=0;
LASB=0;
LASA=1;
P0=smgduan[1];
P0=0x00;

LASC=0;
LASB=1;
LASA=0;
P0=smgduan[2];
P0=0x00;

LASC=0;
LASB=1;
LASA=1;
P0=smgduan[3];
P0=0x00;

LASC=1;
LASB=0;
LASA=0;
P0=smgduan[4];
P0=0x00;

LASC=1;
LASB=0;
LASA=1;
P0=smgduan[5];
P0=0x00;

LASC=1;
LASB=1;
LASA=0;
P0=smgduan[6];
P0=0x00;

LASC=1;
LASB=1;
LASA=1;
P0=smgduan[7];
P0=0x00;

  }
}