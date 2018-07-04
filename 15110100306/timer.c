#include<reg52.h>
#include"display.h"
#include"timer.h"
/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  
 EA=1;            
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
}
/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
 static unsigned int num,i; 
 TH0=(65536-2000)/256;//2ms
 TL0=(65536-2000)%256;
 
 Display(0,8);     
 i++;
 if(i==10)          //20ms
    {
	i=0;
	UpdateTimeFlag=1; 
	}
if(Time_seted_flag==1){
 num++;
 if(num==500)        //大致1s
   {
    num=0;
	second++;
	if(second==60)  	 {
	  second=0;	  
	  minute++;
	  if(minute==60)
	    {
		 minute=0;
		 hour++;
		 if(hour==24)
		   hour=0;
		}
	  }
	}
  }
}
