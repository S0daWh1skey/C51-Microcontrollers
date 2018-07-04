#include"delay.h"
void DelayMs(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
		for(j=100;j>0;j--);
}