#include<reg52.h>
#include"display.h"
#include"timer.h"
/*------------------------------------------------
                    ��ʱ����ʼ���ӳ���
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  
 EA=1;            
 ET0=1;           //��ʱ���жϴ�
 TR0=1;           //��ʱ�����ش�
}
/*------------------------------------------------
                 ��ʱ���ж��ӳ���
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
 if(num==500)        //����1s
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
