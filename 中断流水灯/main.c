#include<reg51.h>
#define LED P2
sbit KEY=P3^3;
bit waterflag=0;//������ˮ�Ʒ���
bit int1flag=0;//�Ƿ����жϱ�־
void initInt1(){
	IT1=1;//���ñ��ؼ�ⷽʽ
	EA=1;
	EX1=1;//����int1���ж�
	//PX1=1��//�������ȼ���ͨ������Ҫ
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
void int1Service(void) interrupt 2{//�ⲿ�ж�1
	delay(200);
	if(KEY==0){
		int1flag=1;
		EX1=0;
}
}

main(){
	initInt1();//�жϵĳ�ʼ��
	while(1){
		waterled();
		if(int1flag){
			while(KEY==0){//�ȴ������ɿ�
				waterled();
				}
			waterflag=~waterflag;//�а��������һ����ˮ��
			int1flag=0;
			EX1=1;	
			}
	}
}















