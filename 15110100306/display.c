#include<reg52.h> 
#include"display.h"
void Display(unsigned char FirstBit,unsigned char Num)
{
     

	   DataPort=0;   
       LATCH1=1;     
       LATCH1=0;

       DataPort=dofly_WeiMa[i+FirstBit]; //取位码 
       LATCH2=1;     //位锁存
       LATCH2=0;

       DataPort=TempData[i]; //取显示数据，段码
       LATCH1=1;     //段锁存
       LATCH1=0;
       
	   i++;
       if(i==Num)
	      i=0;


}