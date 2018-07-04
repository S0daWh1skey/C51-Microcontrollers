#include<reg52.h> 
#include"delay.h"
#include"display.h"
#include"playmusic.h"
#include"keyscan.h"
#include"timer.h"
#include"18b20.h"
unsigned char num;
unsigned char hour,minute,second;
unsigned char Ahour,Aminute,Asecond;
bit UpdateTimeFlag;
unsigned char code dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
unsigned char TempData[8]; 
bit Time_seted_flag=0;
bit Temp_show_flag=0;
bit Alarm_seted_flag=0;
bit Temp_showed_flag=0;
bit Alarm_closed_flag=0;
int temp; 
int temphour;	
void main (void)
{
Init_Timer0();
while (1)         
{
num=KeyScan();
switch(num)
{
   	    case 1:hour++;if(hour==24)hour=0;     
             break;
		case 3:minute++;if(minute==60)minute=0;     
	         break;
		case 5:second++;if(second==60)second=0;     
	         break;
		case 7:Time_seted_flag=1; 			
			break;
		case 8:Alarm_seted_flag=1;
			break;
		case 2:Temp_show_flag=1; 
			 break;
		case 4:Alarm_closed_flag=1;
   			break;
		default:break;
}

if(Alarm_seted_flag==1){
	Ahour=hour;      
	Aminute=minute;
	Asecond=second;
	hour=minute=second=0;
	Time_seted_flag=0;
	Alarm_seted_flag=0;
}

if(UpdateTimeFlag==1)
{
 UpdateTimeFlag=0;
 TempData[0]=dofly_DuanMa[hour/10]; 
 TempData[1]=dofly_DuanMa[hour%10]; 
 TempData[2]=0x40;					    	       
 TempData[3]=dofly_DuanMa[minute/10];
 TempData[4]=dofly_DuanMa[minute%10];
 TempData[5]=0x40;
 TempData[6]=dofly_DuanMa[second/10];
 TempData[7]=dofly_DuanMa[second%10];	 
}	

if(Temp_show_flag==1&&Temp_showed_flag==0){ 
temp=0;
temp=ReadTemperature();  
temphour=hour; 
hour=temp*0.625; 
Temp_showed_flag=1;	
Temp_show_flag=0;	
}

if(Temp_showed_flag==1&&Temp_show_flag==1){
	hour=temphour;
	Temp_show_flag=0;	
	Temp_showed_flag=0;
}
	
if(Ahour==hour&&Aminute==minute&&Asecond==second){ 
	if(hour!=0||second!=0||minute!=0){ 
    PlayMusic();  
	DelayMs(200);
	if(Alarm_closed_flag==0){ 
	Ahour=hour; 
	Aminute=minute;
	Asecond=second;  
	}
		}
	}
}
}
