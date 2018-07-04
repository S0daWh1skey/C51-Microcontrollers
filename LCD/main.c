#include<reg52.h>
#include<intrins.h>
sbit RS = P2^4;
sbit RW = P2^5;
sbit EN = P2^6;

#define RS_CLR RS=0
#define RS_SET RS=1

#define RW_CLR RW=0
#define RW_SET RW=1

#define EN_CLR EN=0
#define EN_SET EN=1

#define DataPort P0

void DelayUs2x(unsigned int t)
{   
 while(--t);
}

void DelayMs(unsigned int t)
{
     
 while(t--)
 {
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

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
	//while(LCD_Check_Busy());//忙则等待
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
	//while(LCD_Check_Busy());//忙则等待
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
	LCD_Write_Com(0x38);//显示模式设置
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	DelayMs(5);
	LCD_Write_Com(0x38);
	LCD_Write_Com(0x08);//显示关闭
	LCD_Write_Com(0x01);//显示清屏
	LCD_Write_Com(0x06);//显示光标移动设置
	DelayMs(5);
	LCD_Write_Com(0x0C);//显示开及光标设置
}

void main(void){
/*LCD_Init();//初始化
LCD_Clear();//清屏
while(1){
LCD_Write_Char(3,0,'i');
LCD_Write_Char(5,0,'l');
LCD_Write_Char(6,0,'o');
LCD_Write_Char(7,0,'v');
LCD_Write_Char(8,0,'e');
LCD_Write_Char(10,0,'y');
LCD_Write_Char(11,0,'o');
LCD_Write_Char(12,0,'u');
LCD_Write_String(1,1,"aaaasdfghjkllll;");
//LCD_Write_String(1,1,"キミノコ トガスキダ ");
while(1){
	DelayMs(500);
	LCD_Write_Com(0x18);
}
}*/
unsigned char i,*p;
LCD_Init();
while(1){
	i=1;
	p="www.doflye.net";
	LCD_Clear();
	LCD_Write_String(3,0,"Welcome to");
	while(*p){
		LCD_Write_Char(i,1,*p);
		i++;
		p++;
		DelayMs(50);
	}
	DelayMs(50);
}
}

