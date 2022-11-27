/*REC接P0^5,P~E接P0^7,P~L接P0^6*/
/*******************************************
k1录音开关，
k2播放一次,除非播放完或关闭电源否则无法停止
k3播放一次，在按停止播放
********************************************/

#include <reg52.h>

sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit kai=P0^5;
sbit yi=P0^7;
sbit er=P0^6;
sbit TF=P3^4;

void delay(unsigned int i)
{
 	while(i--);
}

void main()
{
	TF=0;
	kai=0;
	yi=0;
	er=0;
	while(1)
	{
	 	if(k1==0)
		{
			delay(1000);
		 	if(k1==0)
			{
			 	kai=~kai;
			}
			while(k1==0);	
		}
		if(k2==0)
		{
			delay(1000);
		 	if(k2==0)
			{
			 	yi=1;
				delay(1000);
				yi=0;
			}
			while(k2==0);	
		}
		if(k3==0)
		{
			delay(1000);
		 	if(k3==0)
			{
			 	er=~er;
			}
			while(k3==0);	
		}
	}
}