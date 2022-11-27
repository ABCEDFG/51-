#include <i2c.h>

void delay10us(void)   //��ʱ 10us
{
    u8 a,b;
    for(b=1;b>0;b--)
        for(a=1;a>0;a--);
}

void IIC_Start() //��ʼ��֮�� SDA=SCL=0
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

void IIC_Stop()	//������SDA=SCL=1
{
	SDA=0;
	delay10us();
 	SCL=1;
	delay10us();
	SDA=1;
	delay10us();
}

u8 IIC_Write(u8 dat) //д���ݻ�ָ��
{
 	u8 i,t;
	t=0;
	for(i=0;i<8;i++) //�������ݣ������λ��ʼ
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
	while(SDA) //�ȴ�Ӧ��
	{
	 	t++;
		if(t>200) //����ʧ�ܻ���ܽ�����  ���������û�õ�
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

u8 IIC_Read() //�鿴����
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

void At24c02_Write(u8 addr,u8 dat) //��������
{
 	IIC_Start();
	IIC_Write(0xa0);  //����д������ַ
	IIC_Write(addr);  //����Ҫд���ڴ��ַ
	IIC_Write(dat);	  //��������
	IIC_Stop();
}

u8 At24c02_Read(u8 addr) //�鿴���������
{
 	u8 x;
	IIC_Start();
	IIC_Write(0xa0);   //����д������ַ
	IIC_Write(addr);   //����Ҫ��ȡ�ĵ�ַ
	IIC_Start();
	IIC_Write(0xa1);   //���Ͷ�������ַ
	x=IIC_Read();	   //��ȡ����
	IIC_Stop();
	return x;
}

