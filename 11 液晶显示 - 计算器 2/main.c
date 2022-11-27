/*���Լ���������Ȼ�����������㣬���Ҳ����Ȼ�������ַ�Χ0~65535*/
/*������ʾ  +  -  *  /  =                                      */
/* 4*4�������� */
/* 		1 2 3 +
   		4 5 6 -
   		7 8 9 *
   		c 0 = /    */

//Bug  *10ʱ�˸�-1��

#include<reg52.h>
#include<lcd1602.h>

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
	 
#define jian P1

typedef unsigned int u16;
typedef unsigned char u8;

u8 BB[8];
u8 n=0,z,m;
u16 y,x1,x2,j1;	  //  y ������ x1 x2 ��ֵ��  x1 x2 ��������

void yun();
void Key();
void xian(u16 x);
void Acc();
void suan();

void delay(u16 i)
{
 	while(i--);
}

void yun()   //z�������㷽ʽ
{
	u16 hu;	 //���Ա����ظ�ˢ��
	x1=y;
	delay(5000);
	y=0;
	xian(y);
 	while(jian==0x70||jian==0xb0||jian==0xd0||jian==0xe0);	 //��ֹ��������
	while(m!=1)								//����ڶ�������ֵ
	{
		xian(y);
		hu=y;
		while(hu==y&&m!=1)
		{
			Key();
		}
	}
	x2=y;
	switch(z)	 //����������
	{
	 	case(1): y=x1+x2; break;
		case(2): y=x1-x2; break;
		case(3): y=x1*x2; break;
		case(4): y=x1/x2; break;
	}
}

void Key()	 //0~9���� ��    ��suan()�����������ּ����㷽ʽ
{
	u8 b=0,x=0;
	m=0;	 // Ϊ 1 ʱ��=   Ϊ 2 ʱ������ 0    Ϊ 3 ʱ�� c 
    jian=0x0f;
    if(jian!=0x0f)
    {
   	 	delay(1000);
		if(jian!=0x0f)
		{
		 	switch(jian)
			{
			 	case(0x07):	x=1, m=4;   break;
				case(0x0b): x=2, m=3;   break;
				case(0x0d): x=3, m=2;   break;
				case(0x0e): suan(); goto AA;		 //��y��ֵ����x1������0
			}  
			jian=0xf0;
			switch(jian)
			{
			 	case(0x70): x=x,  y=y*10+x; break;
				case(0xb0): x=x+3,y=y*10+x; break;
				case(0xd0): x=x+6,y=y*10+x; break;
				case(0xe0): m=m-1;	Write2(61);					
							if(m==2)
							{
							 	y=y*10;	
							}
							if(m==3)
							{
							 	x1=x2=y=0;
							}
							
			} 
			AA: ;
			while((b<50)&&(jian!=0xf0))	 //��ֹ������
			{
			 	delay(1000);
				b++;
			}
		} 
    }
}

void suan()				//ѡ�����㷽ʽ
{
	z=0;					//�����������㷽ʽ1+  2-  3*  4/
	jian=0xf0;
	switch(jian)
	{	    //	   ���㷽ʽ  ��ʾ����
	 	case(0x70):  z=1,  Write2(43);  yun();  break;	 //  +
		case(0xb0):  z=2,  Write2(45);  yun();  break;	 //  -
		case(0xd0):  z=3,  Write2(42);  yun();  break;	 //  *
		case(0xe0):  z=4,  Write2(47);  yun();  break;	 //  /
	}	
}

void xian(u16 x)			   //���ִ�������ʾ��lcd����
{
	u8 i,j;
	u16 n,k;
	n=1;
	k=x;
	j=0;
	while(k!=0)	//���� x ��λ��
	{
	 	k=k/10;
		j++;
	}
	if(m!=1)  //������д���Ա�֤���ֲ��ظ�
	{
		for(i=1;i<j;i++)
		{
	 		Write1(0x10);
		}
	}
	for(i=0;i<j;i++)    //�� x �ĸ���λ������������ BB
	{
 		BB[i]=x/n%10;
		n*=10;
	}
	for(i=0;i<j;i++)	//��������ʾ����
	{
	 	Write2(BB[j-i-1]+'0');	
	}

}

void main()
{
	u16 hu;	//���Ա����ظ�ˢ��
 	y=j1=0;	//��ʼֵ
	LCD1602Init();
	while(1)
	{
	 	xian(y);
		hu=y;
		while(hu==y)
		{
		 	Key();
		}
	}
}