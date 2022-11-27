#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit SDA=P3^2; 	//红外线

u8 code BAA[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0X76};
u8 Ir[8];
u16 x;
u8 a,b,c;

void delay(u16 i)
{
 	while(i--);
}

void Shuju()		  
{
	a=Ir[2]/16;  //读取 16进制
	b=Ir[2]%16;	 //读取 16进制
	c=16;	
}

void Acc()			 //数码管显示
{
	   LSC=0, LSB=0, LSA=0;
	   P0=BAA[c];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=0, LSA=1;
	   P0=BAA[b];
	   delay(50);
	   P0=0x00;

	   LSC=0, LSB=1, LSA=0;
	   P0=BAA[a];
	   delay(50);
	   P0=0x00;
}

void IrInit() //初始化红外线接收
{
 	IT0=1;	 //下降沿触发
	EX0=1;	 //打开中断0允许
	EA=1;	 //打卡总中断
	SDA=1;	 //初始化端口
}

void main()
{
 	IrInit();
	while(1)
	{
	 	Shuju();
		Acc();
	}
}

void hong() interrupt 0
{
 	u8 i,j;
	u16 t;
	x=0;
	delay(700);	//延时7ms，以跳过大部分起始码
	if(SDA==0)	//确认是否真的收到信号（起始码）
	{
	 	t=1000;
		while((SDA==0) && (t>0))   //等待起始码（低电平）结束
		{
		 	delay(1);
			t--;   //强制退出循环
		}
		if(SDA==1)   //起始码高电平
		{
		 	t=500;
			while((SDA==1) && (t>0))  //等待起始码（高电平）结束
			{
				delay(1);
				t--;
			}
			for(i=0;i<4;i++)   //共有4组数据
			{
			 	for(j=0;j<8;j++)   //接受1组数据
				{
				 	t=60;
					while((SDA==0) && (t>0))   //等待信号前面的560us低电平过去
					{
					 	delay(1);   //大约延时10us
						t--;
					}
					t=500;
					while((SDA==1) && (t>0))
					{
					 	delay(10);   //大约延时0.1ms
						t--;
						x++;
						if(x>30)   //时间过长，数据无效
						{
						 	return;
						}
					}
					Ir[i]>>=1;   //从高电平开始读取
					if(x>7)   //高电平时间大于800us
					{
					 	Ir[i]|=0x80;   //取 1
					}
					x=0;
				}
			}	
		}
		if(Ir[2]!=Ir[3])
		{
		 	return;
		}
	}
}










