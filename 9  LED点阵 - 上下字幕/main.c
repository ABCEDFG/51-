/*k1����ֹͣ�򲥷Ŷ�����Ĭ��ֹͣ*/

#include<reg51.h>
#include<intrins.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit SRCLK=P3^6;
sbit RCLK=P3^5;
sbit SER=P3^4;
sbit k1=P3^1;
sbit k2=P3^0;

u8 ledwei[]={0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe};
u8 OO[]={0x08,0x18,0x08,0x08,0x08,0x08,0x3C,0x00,0x18,0x24,0x04,0x04,0x08,0x10,0x3C,0x00,
0x18,0x24,0x04,0x18,0x04,0x24,0x18,0x00,0x08,0x18,0x28,0x48,0x3C,0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 c,i,j,k,z,y;
void delay(u16 i)
{
 	while(i--);
}

void Key()
{
	if(k1==0)  //����  ����
	{
	 	delay(1000);
		if(k1==0)
		{
		 	z=~z;
		}
		while(k1==0);
	}

	if(k2==0)  //����  ����
	{
	 	delay(1000);
		if(k2==0)
		{
		 	y=~y;
		}
		while(k2==0);
	}
}

void Zhong(u8 a)  //��ѡ����
{
	u8 b;
	SRCLK=0;
	RCLK=0;
 	for(b=0;b<8;b++)
	{
	 	SER=a>>7;
		a<<=1;
		SRCLK=1;
		_nop_();
		_nop_();
		SRCLK=0;
	}
	RCLK=1;
	_nop_();
	_nop_();
	RCLK=0;
}

void led()	 //������ʾ
{
 	for(i=0;i<5;i++)  //����i<?? ���Ʋ����ٶ�
	{
 		for(c=0;c<8;c++)
		{
			P0=0x7f;
	 		P0=~OO[c+j];
			Zhong(~ledwei[c]);		 //j���ƻ����ƶ�
			delay(100);
			Zhong(0x00);
			Key();
		}			
	}
}

void main()
{
	u8 a,i;
    j=k=z=y=0;
    while(1)
    {
   		led();
		if(j%8==0||j==0)	//ͣ��һ��
		{
			for(i=0;i<10;i++)
			{
			 	led();
			}
		}
		if(z==0)		//z=0ʱֹͣ
		{
		 	while(!z)  
			{
			 	Key();
				led();
			}
		}
		if(y==0)	 // �� ��
		{
		 	j++;
		}
		else
		{
		 	j--;
		}
		if(j==32)
		{
		 	j=0;
		}	
	}
}