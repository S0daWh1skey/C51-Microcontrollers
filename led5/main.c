#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define DataPort P1
sbit LATCH_D=P2^2;
sbit LATCH_W=P2^3;
uchar code DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c};
uchar code WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
	for(j=110;j>0;j--);
}

void main(){
	uchar i=0,num=0;
	uint j=0;
	while(1){
	for(i=0;i<8;i++){
	DataPort=WeiMa[i];
	LATCH_W=1;
	LATCH_W=0;

	DataPort=DuanMa[i+num];
	LATCH_D=1;
	LATCH_D=0;
	delayms(1);
	j++;
	if(1000==j){
	j=0;
	num++;
	if(9==num)
	num=0;
}
}
}
}		
