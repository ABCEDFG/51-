#include<reg52.h>
#include<lcd1602.h>

typedef unsigned int u16;
typedef unsigned char u8;

u8 A[]={"hello wrold"};

void main()
{
 	u8 i;
	LCD1602Init();
	while(A[i]!='\0')	//��ʾ�����е��ַ�
	{
	 	Write2(A[i++]);
	}
	while(1);
}