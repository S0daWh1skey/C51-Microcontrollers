#include<reg52.h>
#include<intrins.h>
#include"delay.h"
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