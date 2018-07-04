/***********************************
neme 矩阵按键
连线 P1->24(矩阵按键)
	 P0_>J9(发光二极管)
***********************************/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define KEY P1
#define DataPort P0
sbit LATCH_D=P2^4;
sbit LATCH_W=P2^3;
uchar DuanMa[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7F,0x6F,0x77,0x7c,0x39,0x5e,0x79,0x71}; //0-F的字段码表
uchar Zixing[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7F,0x6F,0x77,0x7c,0x39,0x5e,0x79,0x71};
uchar code WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//位选码表
void delayms(uint n);
//函数声明
bit isKeyInput(void);
void WaitKeyRelease();
uchar KeySacn(void);
void delayms(uint n);
void Display(void);
void move(uchar n);
unsigned char Keycode;
//主函数
void main()
{
	
	while(1)
	{
		Display();

		if(isKeyInput()){
			delayms(10);
			if(isKeyInput()){
				Keycode=KeySacn();
				WaitKeyRelease();
				move(Keycode);
			}	
		}

	}
}	
//1.判断键是否按下 不用动
bit isKeyInput(void){
	KEY=0xf0;    //输出1111  0000
	if(KEY != 0xf0)
	return 1;
	else
	return 0;

}
//2 按键松开 不用动
void WaitKeyRelease(){
	while(1){
	KEY=0xf0;
	if(KEY==0xf0)
	break;
	}
}
void move(uchar m){
     uchar i;
	 if(m==16)
	 {
	for(i=0;i<8;i++){
     DuanMa[i]=0x40;
     }
	} 
     DuanMa[8]=Zixing[m];
     for(i=0;i<8;i++){
     DuanMa[i]=DuanMa[i+1];
     }  
}
//显示函数 不用动
void Display(void){
	uchar i;
	for(i=0;i<8;i++){
		DataPort=WeiMa[i];//送位码
		LATCH_W=1;//位选开
		LATCH_W=0;//位选关

		DataPort=DuanMa[i];//送字形码0~9
		LATCH_D=1;//段选开
		LATCH_D=0;//段选关
		delayms(1);//延时1ms 动态显示  

}
}


//3 键盘扫描 不用动
uchar KeySacn(void){
	//列:高4位，行：低4位
	uchar Keycode;

	//扫描第一行
	KEY=0xfe;   //1111 1110  //列
	if(KEY==0x7e)  Keycode=1;//0111 1110
	if(KEY==0xbe)  Keycode=2;//1011 1110
	if(KEY==0xde)  Keycode=3;//1101 1110
	if(KEY==0xee)  Keycode=4;//1110 1110	

	//扫描第二行
	KEY=0xfd;   //1111 1101
	if(KEY==0x7d)  Keycode=5;//0111 1101
	if(KEY==0xbd)  Keycode=8;//1011 1101
	if(KEY==0xdd)  Keycode=11;//1101 1101
	if(KEY==0xed)  Keycode=14;//1110 1101	

	//扫描第三行
	KEY=0xfb;   //1111 1011
	if(KEY==0x7b)  Keycode=6;//0111 1011
	if(KEY==0xbb)  Keycode=9;//1011 1011
	if(KEY==0xdb)  Keycode=12;//1101 1011
	if(KEY==0xeb)  Keycode=15;//1110 1011	

	//扫描第四行
	KEY=0xf7;   //1111 0111
	if(KEY==0x77)  Keycode=7;//0111 0111
	if(KEY==0xb7)  Keycode=10;//1011 0111
	if(KEY==0xd7)  Keycode=13;//1101 0111
	if(KEY==0xe7)  Keycode=16;//1110 0111	

	return Keycode;
}
//延时函数 不用动
void delayms(uint n)
{
	uint i,j;
	for(i=0;i<n;i++)
		for(j=110;j>0;j--);
	}