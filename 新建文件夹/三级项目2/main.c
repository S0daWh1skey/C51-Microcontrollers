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
char dis_ctnt[8]={'0', '0', '-', '0', '0', '-', '0', '0'};//Ҫ��ʾ��ʱ������ 
char dis_ctnt2[16];

void set_ctnt(unsigned char *t, unsigned char i) {
	dis_ctnt[i*3]='0'+t[i]/10;//������ʽ��ʱ��ֽ�ɶ�Ӧ�ַ���д����ʾ�Ļ��������� 
	dis_ctnt[i*3+1]='0'+t[i]%10;
	LCD_Write_Char(4+i*3, 0, dis_ctnt[i*3]);//��ʾ����Ļ�� 
	LCD_Write_Char(5+i*3, 0, dis_ctnt[i*3+1]);
}

void update_temp() {
	temperature=(float)ReadTemperature()*0.0625;//��ȡ�¶ȣ����浽������ 
	sprintf(dis_ctnt2,"Temp  % 7.3f",temperature);//��ӡ�¶�ֵ
	LCD_Write_String(0,1,dis_ctnt2);//��ʾ�ڶ���
}

void update_time(unsigned char *t, char num) reentrant {
	if(num<0) return ;
	if(++(*t)>time_limit[num]) {
		(*t)=0;
		update_time(t-1, num-1);
	}
	if(!edit_flg) set_ctnt(time, num);
}

//�ǵݹ鷽��
void update_time2() {
	unsigned char i;
	for(i=2; i>=0; i--) {
		if(++time[i]>time_limit[i]) {
			time[i]=0;
			if(!edit_flg) set_ctnt(time, i);//���ֱ�����1�Ļ������ڱ༭�� 
		} else {
			if(!edit_flg) set_ctnt(time, i);
			break;
		}
	}
}

void init_Timer0() {
	TMOD|=0x01;//�趨�˹���ģʽ1������ܼ�65536���� 
	EA=1;//���жϿ��ش� 
	ET0=1;//��ʱ��0�жϿ��ؿ� 
	TR0=1;//��ʱ��0�� 
}

void Timer0() interrupt 1 {
	TH0=(65536-1536)/256;//�߰�λ������ʱ���ô�һ��ָ��������ʼ 
	TL0=(65536-1536)%256;//�Ͱ�λ 
	cnt++;
	if(cnt>=600) {//cnt����600�൱�ڹ�ȥһ�� 
		cnt=0;//��600��CNT��Ϊ0 
		update_temp();//�����¶� 
		update_time(time+2, 2);
		//update_time2();
	}
	if(spk_flg) SPK=!SPK;// ���ȿ��أ�Ҫ=1�Ļ������� 
}

unsigned char is_press() {//��תɨ�� ���ȸ������и�ֵΪ1����Ⲣ�����е�ֵ��Ȼ����е�ֵ��ֵ����
//�ټ�Ⲣ�����е�ֵ��Ȼ�������ֵ��Ͼ��ǵ�ǰ��ֵ 
	unsigned key_val=0;
	PORT_KEY=0x0f;
	if(PORT_KEY!=0x0f) {
		DelayMs(10);
		if(PORT_KEY!=0x0f) {
			key_val=PORT_KEY&0x0f;//�ѽӿڵ���λȡ��������Ⲣ�����е�ֵ 
			PORT_KEY=key_val|0xf0; 
			key_val+=PORT_KEY&0xf0;

			PORT_KEY=0x0f;
			while(PORT_KEY!=0x0f) ;//����Ƿ񳤰� 
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
			tmp=tmp*10+key;//������������ֵΪʮλ�� 
			t[i]=tmp;
			set_ctnt(t, i);
			if(j==0) LCD_Write_Char(4+i*3, 0, '_');//��ʮλ��0����»��� 
		}
		if(tmp<0 || tmp>time_limit[i]) {
			t[i]=0;
			dis_ctnt[i*3]=dis_ctnt[i*3+1]='0';
			LCD_Write_Char(4+i*3, 0, '_');
			LCD_Write_Char(5+i*3, 0, '_');
			--i;//backfitting���� 
		}
	}
}

void main() {
	LCD_Init(); //��ʼ����ʾ�� 
	LCD_Clear();//���� 
	LCD_Write_String(4, 0, dis_ctnt);//��LCD��д�ַ����������е�0�У��ַ����� 
	init_Timer0();//��ʼ����ʱ��0 
	while(1) {
		if(time[2]==alm_clk[2])//�Ƚϵ�ǰʱ���Ƿ�������ʱ����ͬ 
		  if(time[1]==alm_clk[1])
			if(time[0]==alm_clk[0])
				spk_flg=1;//��ͬ���� 
		switch (get_input()) {
			case 10: //10�ż����༭ʱ�� 
				memset(dis_ctnt, '_', sizeof(dis_ctnt));//����λȫ���»��� 
				dis_ctnt[2]=dis_ctnt[5]='-'; 
				LCD_Write_String(4, 0, dis_ctnt);//��ʾ����ʾ��ĵ� 
				edit_flg=1;//���ڱ༭״̬���༭��־λ��1 
				edit_time(time);//���ñ༭ʱ��ĺ��� 
				cnt=0;
				edit_flg=0;
				break;
			case 11://11�ż����������� 
				memset(dis_ctnt, '_', sizeof(dis_ctnt));
				dis_ctnt[2]=dis_ctnt[5]='-';
				LCD_Write_String(4, 0, dis_ctnt);
				edit_flg=1;
				edit_time(alm_clk);
				edit_flg=0;
				{set_ctnt(time, 2); set_ctnt(time, 1); set_ctnt(time, 0);}//��������Ļ����ʾʱ�� 
				break;
			case 12://������ͣ���� 
				spk_flg=0;
				SPK=0;
				break;
		} 
	}
}

