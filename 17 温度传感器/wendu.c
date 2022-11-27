#include <wendu.h>

void Delay1ms(void)   //��� 0us
{
    unsigned char a,b;
    for(b=199;b>0;b--)
        for(a=1;a>0;a--);
}

u8 DS18B20_Init()
{
	u8 i;
	i=70;
	shu=0;
 	while(i--);		//��ʱ642us
	shu=1;
	i=0;
	while(shu)
	{
	 	Delay1ms();
		i++; 	
		if(i>5)
		{
		 	return 0;
		}	
	}
	return 1;
}

void DS18B20_Write(u8 x)
{
	u8 i,n;
	n=0;
	for(i=0;i<8;i++)
	{
	 	shu=0;
		n++;  	//��ʱ ��Լ6us
		shu= x & 0x01;
		n=6;
		while(n--);		//��ʱ ��Լ68us
		shu=1;
		x>>=1;
	}
}

u8 DS18B20_Read()
{
	u8 i,n;
	u8 x,y;
	n=0;
	for(i=0;i<8;i++)
	{
	 	shu=0;
		n++;	//��ʱ ��Լ6us
		shu=1;
		n++;  	//��ʱ ��Լ6us
		n++; 	//��ʱ ��Լ6us
		y=shu;
		x=(x>>1) | (y<<7);	  //�����λ��ʼ��ȡ
		n=4;
		while(n--);	  //��ʱ ����45us
	}
	return x;
}

void DS18B20_Zhuan()	//�¶�ת��
{
 	DS18B20_Init();
	Delay1ms();
	DS18B20_Write(0xcc);
	DS18B20_Write(0x44);
}

void DS18B20_du()	  	//��ȡ�¶�����
{
 	DS18B20_Init();
	Delay1ms();
	DS18B20_Write(0xcc);
	DS18B20_Write(0xbe);
}

int DS18B20_Wendu()
{
 	u8 h,l;
	int x=0;
	DS18B20_Zhuan();
	DS18B20_du();
	l=DS18B20_Read();	//���ֽ�����
	h=DS18B20_Read();	//���ֽ�����
	x=h;
	x<<=8;
	x|=l;
	return x;
}