#include <reg52.h>
#include <intrins.h>
#include <string.h>
#include <stdio.h>
#include "1602.h"
#include "delay.h"
#include "18b20.h"

#define PORT_KEY P3
#define PORT_DATA P0

sbit SPK=P2^2;

unsigned char edit_flg=0;
unsigned char spk_flg=0;
unsigned int cnt=0;
unsigned char time[3]={0};
unsigned char alm_clk[3]={23, 59, 59};
unsigned char time_limit[3]={23, 59, 59};
float temperature;
char dis_ctnt[8]={'0', '0', '-', '0', '0', '-', '0', '0'};//要显示的时间数组 
char dis_ctnt2[16];

void set_ctnt(unsigned char *t, unsigned char i) {
	dis_ctnt[i*3]='0'+t[i]/10;//整数格式的时间分解成对应字符并写道显示的缓存数组里 
	dis_ctnt[i*3+1]='0'+t[i]%10;
	LCD_Write_Char(4+i*3, 0, dis_ctnt[i*3]);//显示到屏幕上 
	LCD_Write_Char(5+i*3, 0, dis_ctnt[i*3+1]);
}

void update_temp() {
	temperature=(float)ReadTemperature()*0.0625;//读取温度，保存到变量里 
	sprintf(dis_ctnt2,"Temp  % 7.3f",temperature);//打印温度值
	LCD_Write_String(0,1,dis_ctnt2);//显示第二行
}

void update_time(unsigned char *t, char num) reentrant {
	if(num<0) return ;
	if(++(*t)>time_limit[num]) {
		(*t)=0;
		update_time(t-1, num-1);
	}
	if(!edit_flg) set_ctnt(time, num);
}

//非递归方法
void update_time2() {
	unsigned char i;
	for(i=2; i>=0; i--) {
		if(++time[i]>time_limit[i]) {
			time[i]=0;
			if(!edit_flg) set_ctnt(time, i);//发现变量是1的话，正在编辑。 
		} else {
			if(!edit_flg) set_ctnt(time, i);
			break;
		}
	}
}

void init_Timer0() {
	TMOD|=0x01;//设定了工作模式1，最多能记65536个数 
	EA=1;//总中断开关打开 
	ET0=1;//定时器0中断开关开 
	TR0=1;//定时器0打开 
}

void Timer0() interrupt 1 {
	TH0=(65536-1536)/256;//高八位，重来时候让从一个指定的数开始 
	TL0=(65536-1536)%256;//低八位 
	cnt++;
	if(cnt>=600) {//cnt等于600相当于过去一秒 
		cnt=0;//到600后，CNT即为0 
		update_temp();//更新温度 
		update_time(time+2, 2);
		//update_time2();
	}
	if(spk_flg) SPK=!SPK;// 喇叭开关，要=1的话，就响 
}

unsigned char is_press() {//反转扫描 ，先给所有列赋值为1，检测并保存行的值，然后把行的值赋值给行
//再检测并保存列的值，然后把行列值组合就是当前键值 
	unsigned key_val=0;
	PORT_KEY=0x0f;
	if(PORT_KEY!=0x0f) {
		DelayMs(10);
		if(PORT_KEY!=0x0f) {
			key_val=PORT_KEY&0x0f;//把接口低四位取出来，检测并保存行的值 
			PORT_KEY=key_val|0xf0; 
			key_val+=PORT_KEY&0xf0;

			PORT_KEY=0x0f;
			while(PORT_KEY!=0x0f) ;//检测是否长按 
			return key_val;
		}
	}
	return 0xff;
}

unsigned char get_input() {
	switch (is_press()) {
		case 0x7e: return 1;
		case 0x7d: return 2;
		case 0x7b: return 3;
		case 0xbe: return 4;
		case 0xbd: return 5;
		case 0xbb: return 6;
		case 0xde: return 7;
		case 0xdd: return 8;
		case 0xdb: return 9;
		case 0xee: return 0;

		case 0x77: return 10;
		case 0xb7: return 11;
		case 0xd7: return 12;
		case 0xe7: return 13;
		case 0xeb: return 14;
		case 0xed: return 15;
		
		default: return 0xff;
	}
}

void edit_time(unsigned char *t) {
	unsigned char key=0;
	unsigned char tmp;
	char i, j;
	for(i=0; i<3; ++i) {
		tmp=0;
		for(j=0; j<2; ++j) {
			do {
				key=get_input();
			} while(key>9);
			tmp=tmp*10+key;//组合输入的两个值为十位数 
			t[i]=tmp;
			set_ctnt(t, i);
			if(j==0) LCD_Write_Char(4+i*3, 0, '_');//把十位上0变成下划线 
		}
		if(tmp<0 || tmp>time_limit[i]) {
			t[i]=0;
			dis_ctnt[i*3]=dis_ctnt[i*3+1]='0';
			LCD_Write_Char(4+i*3, 0, '_');
			LCD_Write_Char(5+i*3, 0, '_');
			--i;//backfitting回溯 
		}
	}
}

void main() {
	LCD_Init(); //初始化显示屏 
	LCD_Clear();//清屏 
	LCD_Write_String(4, 0, dis_ctnt);//往LCD里写字符串，第四列第0行，字符串。 
	init_Timer0();//初始化定时器0 
	while(1) {
		if(time[2]==alm_clk[2])//比较当前时间是否与闹钟时间相同 
		  if(time[1]==alm_clk[1])
			if(time[0]==alm_clk[0])
				spk_flg=1;//相同就响 
		switch (get_input()) {
			case 10: //10号键，编辑时间 
				memset(dis_ctnt, '_', sizeof(dis_ctnt));//数字位全变下划线 
				dis_ctnt[2]=dis_ctnt[5]='-'; 
				LCD_Write_String(4, 0, dis_ctnt);//显示屏显示后改的 
				edit_flg=1;//处于编辑状态，编辑标志位置1 
				edit_time(time);//调用编辑时间的函数 
				cnt=0;
				edit_flg=0;
				break;
			case 11://11号键，设置闹钟 
				memset(dis_ctnt, '_', sizeof(dis_ctnt));
				dis_ctnt[2]=dis_ctnt[5]='-';
				LCD_Write_String(4, 0, dis_ctnt);
				edit_flg=1;
				edit_time(alm_clk);
				edit_flg=0;
				{set_ctnt(time, 2); set_ctnt(time, 1); set_ctnt(time, 0);}//重新在屏幕上显示时间 
				break;
			case 12://让喇叭停下来 
				spk_flg=0;
				SPK=0;
				break;
		} 
	}
}

