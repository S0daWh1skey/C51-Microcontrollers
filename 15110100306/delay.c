#include<reg52.h>
#include<intrins.h>
#include"delay.h"
void DelayUs2x(unsigned char t)
{   
 while(--t);
}
void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     //¥Û÷¬—” ±1mS
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}
