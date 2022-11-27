#include <i2c.h>

void delay10us(void)   //延时 10us
{
    u8 a,b;
    for(b=1;b>0;b--)
        for(a=1;a>0;a--);
}

void IIC_Start() //起始，之后 SDA=SCL=0
{
 	SDA=1;
	delay10us();
	SCL=1;
	delay10us();
	SDA=0;
	delay10us();
	SCL=0;
	delay10us();
}

void IIC_Stop()	//结束，SDA=SCL=1
{
	SDA=0;
	delay10us();
 	SCL=1;
	delay10us();
	SDA=1;
	delay10us();
}

u8 IIC_Write(u8 dat) //写数据或指令
{
 	u8 i,t;
	t=0;
	for(i=0;i<8;i++) //发送数据，从最高位开始
	{
	 	SDA=dat>>7;
		dat=dat<<1;
		delay10us();
		SCL=1;
		delay10us();
		SCL=0;
		delay10us();
	}
	SDA=1;
	delay10us();
	SCL=1;
	while(SDA) //等代应答
	{
	 	t++;
		if(t>200) //发松失败或接受结束，  本程序好像没用到
		{
		 	SCL=0;
			delay10us();
			return 0;
		}
	}
	SCL=0;
	delay10us();
	return 1;
}

u8 IIC_Read() //查看数据
{
 	u8 dat,i;
	dat=0;
	SDA=1;
	delay10us();
	for(i=0;i<8;i++)
	{
		SCL=1;
		delay10us();
	 	dat<<=1;
		dat|=SDA;
		delay10us();
		SCL=0;
		delay10us();
	}
	return dat;
}

void At24c02_Write(u8 addr,u8 dat) //保存数据
{
 	IIC_Start();
	IIC_Write(0xa0);  //发送写器件地址
	IIC_Write(addr);  //发送要写入内存地址
	IIC_Write(dat);	  //发送数据
	IIC_Stop();
}

u8 At24c02_Read(u8 addr) //查看保存的数据
{
 	u8 x;
	IIC_Start();
	IIC_Write(0xa0);   //发送写器件地址
	IIC_Write(addr);   //发送要读取的地址
	IIC_Start();
	IIC_Write(0xa1);   //发送读器件地址
	x=IIC_Read();	   //读取数据
	IIC_Stop();
	return x;
}

