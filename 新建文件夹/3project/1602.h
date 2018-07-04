#include<reg52.h>
sbit RS=P2^4;
sbit RW=P2^5;
sbit EN=P2^6;
#define DataPort P0

bit LCD_Check_Busy(void);
void LCD_Write_Com(unsigned char com);
void LCD_Write_Data(unsigned char Data);
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data);
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s);
void LCD_Init(void);
void LCD_Clear(void);

