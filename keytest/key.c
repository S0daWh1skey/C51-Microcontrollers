#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
void delayms(uint xms);
sbit KEY_ADD=P3^0;
sbit KEY_DEC=P3^1;
#define DataPort P1
sbit LATCH_D=P2^2;
sbit LATCH_W=P2^3;
uchar code DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07};
uchar code WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
	for(j=110;j>0;j--);
}
void main(void)
{	
	uchar num=0;
	KEY_ADD=1;
	KEY_DEC=1;
	while(1)
	{	if(!KEY_ADD)
		{
			delayms(20);
		if(!KEY_ADD)
			{
			while(!KEY_ADD);
			if(num<9)
				num++;
			while(!KEY_DEC);
			if(num>0)
				num--;
	}
}
	DataPort=WeiMa[0];
	LATCH_W=1;
	LATCH_W=0;

	DataPort=DuanMa[num];
	LATCH_D=1;
	LATCH_D=0;
			//delayms(100);
		}
		//else
		//	LED=1;
}

