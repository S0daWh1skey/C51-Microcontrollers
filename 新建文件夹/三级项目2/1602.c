#include<reg52.h>
#include<intrins.h>
#include"1602.h"
#include"delay.h"



bit LCD_Check_Busy(void){
	DataPort=0xff;
	RS_CLR;
	RW_SET;
	EN_CLR;
	_nop_();
	EN_SET;
	return (bit)(DataPort & 0x80);
}

void LCD_Write_Com(unsigned char com){
	//while(LCD_Check_Busy());//æ��ȴ�
	DelayMs(5);
	RS_CLR;
	RW_CLR;
	EN_SET;
	DataPort=com;
	_nop_();
	EN_CLR;
}

void LCD_Clear(void){
	LCD_Write_Com(0x01);
	DelayMs(5);
}

void LCD_Write_Data(unsigned char Data){
	//while(LCD_Check_Busy());//æ��ȴ�
	DelayMs(5);
	RS_SET;
	RW_CLR;
	EN_SET;
	DataPort=Data;
	_nop_();
	EN_CLR;
}

void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data){
	if(y==0){
		LCD_Write_Com(0x80+x);
			}
	else{
		LCD_Write_Com(0xC0+x);
		}
	LCD_Write_Data(Data);	
}

void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s){
	if(y==0){
		LCD_Write_Com(0x80+x);
			}
	else{
		LCD_Write_Com(0xC0+x);
		}
	while(*s){
	LCD_Write_Data(*s);
	s++;
	}	
}

void LCD_Init(void){
	LCD_Write_Com(0x38);//��ʾģʽ����
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	LCD_Write_Com(0x08);//��ʾ�ر�
	LCD_Write_Com(0x01);//��ʾ����
	LCD_Write_Com(0x06);//��ʾ����ƶ�����
	DelayMs(5);
	LCD_Write_Com(0x0C);//��ʾ�����������
}
