#include<reg51.h>
#define LED P2
sbit KEY=P3^3;
bit waterflag=0;//控制流水灯方向
bit int1flag=0;//是否有中断标志
void initInt1(){
	IT1=1;//设置边沿检测方式
	EA=1;
	EX1=1;//开放int1的中断
	//PX1=1；//设置优先级，通常不需要
}

void delay(unsigned char i){
	for(;i>0;i--);
}

void delay1(){
	unsigned int i;
	for(i=0;i<30000;i++);
}

void waterled(){
	static unsigned char tmp=0xfe;//11111110
	LED=tmp;
	delay1();
	if(!waterflag){
		tmp=(tmp<<1)|0x1;
		if(tmp==0xff)
			tmp=0xfe;
	}else{
		tmp=(tmp>>1)|0x80;
		if(tmp==0xff)
			tmp=0x7f;
	}
}
void int1Service(void) interrupt 2{//外部中断1
	delay(200);
	if(KEY==0){
		int1flag=1;
		EX1=0;
}
}

main(){
	initInt1();//中断的初始化
	while(1){
		waterled();
		if(int1flag){
			while(KEY==0){//等待按键松开
				waterled();
				}
			waterflag=~waterflag;//有按键后更改一下流水灯
			int1flag=0;
			EX1=1;	
			}
	}
}















