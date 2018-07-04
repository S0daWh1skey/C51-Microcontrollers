#include"1602.h"
#include"delay.h"
#include<reg52.h>
#include<intrins.h>
bit LCD_Check_Busy(void)
{
	DataPort=0xff;
	RS=0;
	RW=1;
	EN=0;
	_nop_();
	EN=1;
	return (bit)(DataPort & 0x80);
}
void LCD_Write_Com(unsigned char com)
{
	while(LCD_Check_Busy());//忙则等待
	DelayMs(5);
	RS=0;
	RW=0;
	EN=1;
	DataPort=com;
	_nop_();
	EN=0;
}
void LCD_Clear(void)
{
	LCD_Write_Com(0x01);
	DelayMs(5);
}
void LCD_Write_Data(unsigned char Data)
{
	while(LCD_Check_Busy());//忙则等待
	DelayMs(5);
	RS=1;
	RW=0;
	EN=1;
	DataPort=Data;
	_nop_();
	EN=0;
}
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data)
{
	if(y==0)
	{
		LCD_Write_Com(0x80+x);
	}
	else
	{
		LCD_Write_Com(0xc0+x);
	}
	LCD_Write_Data(Data);
}
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s)
{
	if(y==0)
	{
		LCD_Write_Com(0x80+x);
	}
	else
	{
		LCD_Write_Com(0xc0+x);
	}
	while(*s)
	{
		LCD_Write_Data(*s);
		s++;
	}
}
void LCD_Init(void)
{
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	LCD_Write_Com(0x08);
	LCD_Write_Com(0x01);
	LCD_Write_Com(0x06);
	DelayMs(5);
	LCD_Write_Com(0x0C);
}