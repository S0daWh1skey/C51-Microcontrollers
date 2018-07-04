#include<reg52.h>
sbit KEY1=P1^0;//选择年月日时分秒
sbit KEY2=P1^1;//+
sbit KEY3=P1^2;//-
sbit KEY4=P1^3;//闹钟模式/时钟模式
sbit KEY5=P1^4;//闹钟开关
sbit KEY6=P1^5;
sbit KEY7=P1^6;
sbit KEY8=P1^7;
sbit Beep=P2^0;
