/*Trig接P2^0,Echo接P2^1*/

#include <reg52.h>
#include <intrins.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

sbit RX=P2^1;
sbit TX=P2^0;
bit flag=0;

typedef unsigned int u16;
typedef unsigned char u8;

//              0    1    2    3    4    5    6    7    8    9    A    b    c    d    E    f    -
u8 code AA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40,0x80};
u8 BB[5]={0,0,0,17,0};
u16 t1=0;
u16 t2=0;
u16 s=0;

void delay(u16 i)
{
 	while(i--);
}

void Init()   //定时器初始化
{
 	TMOD=0x11;   //设T0为方式1
	TH0=0;
	TL0=0;
	TH1=0xf8;   //2ms定时
	TL1=0x30;
	ET0=1;   //允许T0中断
	ET1=1;	 //允许T1中断
	TR1=1;	 //打开定时器T1中断
	EA=1;	 //打开总中断
}

void shi()		//超声波
{
 	t1=TH0*256+TL0;   //超声波传递时间
	TH0=0;
	TL0=0;
	s=(u16)(t1*0.17);   //距离 单位 mm
}

void shu()
{
	if(s>4000||flag==1)
	{
	 	flag=0;
		BB[0]=16;	// -
		BB[1]=16;	// -
		BB[2]=16;	// -
		BB[4]=16;	// -
	}
	else
	{
	 	 BB[0]=s%10;
		 BB[1]=s/10%10;
		 BB[2]=s/100%10;
		 BB[4]=s/1000%10;
	}
}

void Acc()
{
   u8 i;
   for(i=0;i<5;i++)
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
	  P0=AA[BB[i]];
	  delay(10);
	  P0=0x00;
   }
}

void ding1() interrupt 1   //距离过远，T0计时器溢出
{
 	flag=1;   //超出测量范围
}

void ding2() interrupt 3   //2ms溢出一次
{
 	TH1=0xf8;   //延时2ms
	TL1=0x30;	
	Acc();
	t2++;   //延时400次     
	if(t2>=400)   //800ms启动一次，防止回音干扰
	{
	 	t2=0;
		TX=1;
		_nop_();_nop_();	  // 20us 的高平电压，触发测距
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		_nop_();_nop_();
		TX=0;
	}
}

void main()
{
 	Init();
	while(1)
	{
	 	while(!RX);
		TR0=1;   //打开定时器T0中断
		while(RX);
		TR0=0;   //关闭定时器T1中断
		shi();
		shu();
		Acc();
	}
}
