#include<reg52.h>
#include<intrins.h>
#include "1602.h"
#include "delay.h"
#include "18b20.h"
#include "stdio.h"
void main(void)
{
int temp;
float temperature;
char distemp[16];
LCD_Init();//場宎趙
LCD_Clear();//ьそ
LCD_Write_Char(3,0,'i');
LCD_Write_Char(5,0,'l');
LCD_Write_Char(6,0,'o');
LCD_Write_Char(7,0,'v');
LCD_Write_Char(8,0,'e');
LCD_Write_Char(10,0,'y');
LCD_Write_Char(11,0,'o');
LCD_Write_Char(12,0,'u');
while(1){
temp=ReadTemperature();
temperature=temp*0.0625;
sprintf(distemp,"Temp %7.3f",temperature);
LCD_Write_String(1,1,distemp);
DelayMs(50);
}//LCD_Write_String(1,1,"平立用戊 玄布旦平母 ");
}

