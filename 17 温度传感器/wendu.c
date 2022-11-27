#include <wendu.h>

void Delay1ms(void)   //误差 0us
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
 	while(i--);		//延时642us
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
		n++;  	//延时 大约6us
		shu= x & 0x01;
		n=6;
		while(n--);		//延时 大约68us
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
		n++;	//延时 大约6us
		shu=1;
		n++;  	//延时 大约6us
		n++; 	//延时 大约6us
		y=shu;
		x=(x>>1) | (y<<7);	  //从最高位开始读取
		n=4;
		while(n--);	  //延时 大于45us
	}
	return x;
}

void DS18B20_Zhuan()	//温度转换
{
 	DS18B20_Init();
	Delay1ms();
	DS18B20_Write(0xcc);
	DS18B20_Write(0x44);
}

void DS18B20_du()	  	//读取温度数据
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
	l=DS18B20_Read();	//低字节数据
	h=DS18B20_Read();	//高字节数据
	x=h;
	x<<=8;
	x|=l;
	return x;
}