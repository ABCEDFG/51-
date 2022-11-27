#include<ds1302.h>
/*写入,输出地址,时间  年   月   周   日   时   分   秒	 */
u8 code READ[7]=	{0x8d,0x89,0x8b,0x87,0x85,0x83,0x81};
u8 code WRITE[7]=	{0x8c,0x88,0x8a,0x86,0x84,0x82,0x80};
u8 SHU[7]=			{0x19,0x04,0x01,0x13,0x19,0x00,0x00};

void DS1302_Write(u8 addr,u8 dat)
{
 	u8 i;
	CE=0;
	_nop_();
	CLK=0;
	_nop_();
	CE=1;
	_nop_();
	for(i=0;i<8;i++)	//写入8位地址码
	{
	 	SDA= addr & 0x01;	//数据从低位开始传输
		addr>>=1;
		CLK=1;
		_nop_();
		CLK=0;
		_nop_();
	}
	for(i=0;i<8;i++)	//写入数据	
	{
		SDA= dat & 0x01;
		dat>>=1;
		CLK=1;
		_nop_();
		CLK=0;
		_nop_();
	}
	CE=0;
	_nop_();		
}

u8 DS1302_Read(u8 addr)		//读取
{
 	u8 i,dat,dat1;
	CE=0;
	_nop_();
	CLK=0;
	_nop_();
	CE=1;
	_nop_();
	for(i=0;i<8;i++)	//写入读取地址	
	{
	 	SDA= addr & 0x01;
		addr>>=1;
		CLK=1;
		_nop_();
		CLK=0;
		_nop_();
	}
	_nop_();
	for(i=0;i<8;i++)	//读取数据
	{
	 	dat1=SDA;
		dat=(dat>>1) | (dat1<<7);
		CLK=1;
		_nop_();
		CLK=0;
		_nop_();
	}
	CE=0;
	_nop_();
	CLK=1;
	_nop_();
	SDA=0;
	_nop_();
	SDA=1;
	_nop_();
	return dat;
}

void DS1302_Init()
{
 	u8 i;
	DS1302_Write(0x8e,0x00);	//写保护寄存器、关闭写保护
	for(i=0;i<8;i++)	//写入初始时间
	{
	 	DS1302_Write(WRITE[i],SHU[i]); 
	}
	DS1302_Write(0x8e,0x80);	//写保护寄存器、打开写保护
}

void DS1302_Shi()
{
 	u8 i;
	for(i=0;i<8;i++)
	{
	 	SHU[i]=DS1302_Read(READ[i]);
	}
}








