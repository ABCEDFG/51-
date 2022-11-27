#include<reg52.h>

typedef unsigned int u16;
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit SDA=P3^2; 	//������

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
	a=Ir[2]/16;  //��ȡ 16����
	b=Ir[2]%16;	 //��ȡ 16����
	c=16;	
}

void Acc()			 //�������ʾ
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

void IrInit() //��ʼ�������߽���
{
 	IT0=1;	 //�½��ش���
	EX0=1;	 //���ж�0����
	EA=1;	 //�����ж�
	SDA=1;	 //��ʼ���˿�
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
	delay(700);	//��ʱ7ms���������󲿷���ʼ��
	if(SDA==0)	//ȷ���Ƿ�����յ��źţ���ʼ�룩
	{
	 	t=1000;
		while((SDA==0) && (t>0))   //�ȴ���ʼ�루�͵�ƽ������
		{
		 	delay(1);
			t--;   //ǿ���˳�ѭ��
		}
		if(SDA==1)   //��ʼ��ߵ�ƽ
		{
		 	t=500;
			while((SDA==1) && (t>0))  //�ȴ���ʼ�루�ߵ�ƽ������
			{
				delay(1);
				t--;
			}
			for(i=0;i<4;i++)   //����4������
			{
			 	for(j=0;j<8;j++)   //����1������
				{
				 	t=60;
					while((SDA==0) && (t>0))   //�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
					{
					 	delay(1);   //��Լ��ʱ10us
						t--;
					}
					t=500;
					while((SDA==1) && (t>0))
					{
					 	delay(10);   //��Լ��ʱ0.1ms
						t--;
						x++;
						if(x>30)   //ʱ�������������Ч
						{
						 	return;
						}
					}
					Ir[i]>>=1;   //�Ӹߵ�ƽ��ʼ��ȡ
					if(x>7)   //�ߵ�ƽʱ�����800us
					{
					 	Ir[i]|=0x80;   //ȡ 1
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










