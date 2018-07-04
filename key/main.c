/***********************************************
name:矩阵按键
连线：P1->J24(矩阵按键)
      P0->J9(发光二极管)
***********************************************/
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define Key P1
#define Led P0
//函数声明
uchar KeySacn(void);
void Wait_KeyRelease(void);
bit isKeyInput(void);
void delayms(uint n);
//主函数
void main()
{
	while(1)
	{
		uchar keycode;
		//1、判断按键按下
		if(isKeyInput())
{
			delayms(10);//
			if(isKeyInput())
	{
		keycode=KeySacn();
		Wait_KeyRelease();
		Led=~keycode;
		}
	}
}
	
}
//1、判断按键按下
bit isKeyInput(void)
{
	Key=0xf0;   //1111 0000
	if(Key!=0xf0)
		return 1;
	else
		return 0;	
}
//2、判断按键松开
void Wait_KeyRelease(void)
{
	while(1)
	{
		Key=0xf0;
		if(Key==0xf0)
			break;
	}
}
//3、键盘扫描
uchar KeySacn(void)
{
	//列:高4位，行：低4位
	uchar keycode;

	//扫描第一行
	Key=0xfe;   //1111 1110  //列
	if(Key==0x7e)  keycode=1;//0111 1110
	if(Key==0xbe)  keycode=2;//1011 1110
	if(Key==0xde)  keycode=3;//1101 1110
	if(Key==0xee)  keycode=4;//1110 1110	

	//扫描第二行
	Key=0xfd;   //1111 1101
	if(Key==0x7d)  keycode=5;//0111 1101
	if(Key==0xbd)  keycode=8;//1011 1101
	if(Key==0xdd)  keycode=11;//1101 1101
	if(Key==0xed)  keycode=14;//1110 1101	

	//扫描第三行
	Key=0xfb;   //1111 1011
	if(Key==0x7b)  keycode=6;//0111 1011
	if(Key==0xbb)  keycode=9;//1011 1011
	if(Key==0xdb)  keycode=12;//1101 1011
	if(Key==0xeb)  keycode=15;//1110 1011	

	//扫描第四行
	Key=0xf7;   //1111 0111
	if(Key==0x77)  keycode=7;//0111 0111
	if(Key==0xb7)  keycode=10;//1011 0111
	if(Key==0xd7)  keycode=13;//1101 0111
	if(Key==0xe7)  keycode=16;//1110 0111	

	return keycode;
}
//4、延时函数：ms
void delayms(uint n)
{
	uint i,j;
	for(i=0;i<n;i++)
		for(j=110;j>0;j--);
}
//1000=1s
