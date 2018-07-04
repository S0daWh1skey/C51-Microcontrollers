#include<reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#include"delay.h"
#include"display.h"
#include"playmusic.h"
#include"keyscan.h"
#include"timer.h"
#include"18b20.h"
unsigned char num;//获得键盘按键的数字
unsigned char hour,minute,second;//定义时分秒
unsigned char Ahour,Aminute,Asecond;//定义闹钟的时分秒
bit UpdateTimeFlag;//定义更新时间标志
unsigned char code dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// 显示段码值0~9
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//分别对应相应的数码管点亮,即位码
unsigned char TempData[8]; //存储显示值的全局变量
bit Time_seted_flag=0; //时间设置标志位
bit Temp_show_flag=0; //温度显示标志位
bit Alarm_seted_flag=0;//闹钟设置标志位
bit Temp_showed_flag=0;//已经显示温度标志位
bit Alarm_closed_flag=0;
int temp; //温度
int temphour;	//临时储存当前小时
/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main (void)
{
//unsigned char num;                  
Init_Timer0();//调用定时器初始化函数
while (1)         //主循环
{
num=KeyScan();//读取键盘数字
switch(num)//switch函数 控制不同功能
{
   	    case 1:hour++;if(hour==24)hour=0;     //正常时间 小时 加1
             break;
		case 3:minute++;if(minute==60)minute=0;     //分钟加1
	         break;
		case 5:second++;if(second==60)second=0;     //分钟加1
	         break;
		case 7:Time_seted_flag=1; //启动时钟
			break;
		case 8:Alarm_seted_flag=1;//储存闹钟 设置闹钟
			break;
		case 2:Temp_show_flag=1; //显示温度
			 break;
		case 4:Alarm_closed_flag=1;//闹钟关闭标志位
			break;
		default:break;
}

if(Alarm_seted_flag==1){
	Ahour=hour;      //将显示屏上显示的时间储存到闹钟变量里
	Aminute=minute;
	Asecond=second;
	hour=minute=second=0;//将显示屏变为初始状态00-00-00
	Time_seted_flag=0;//表示时间没设置
	Alarm_seted_flag=0;//闹钟未设置 （不会在下次循环中继续执行这个分支）
}

if(UpdateTimeFlag==1)//时间更新标志位=1 开始在显示屏更新时间
{
 UpdateTimeFlag=0;//更新标志位重置 以便重新进入
 TempData[0]=dofly_DuanMa[hour/10]; //时 得到两位数的前一位			//数据的转换，因我们采用数码管0~9的显示,将数据分开
 TempData[1]=dofly_DuanMa[hour%10]; //得到两位数的后一位
 TempData[2]=0x40;					    	        //加入"-"
 TempData[3]=dofly_DuanMa[minute/10];//分
 TempData[4]=dofly_DuanMa[minute%10];
 TempData[5]=0x40;//显示为 "-"
 TempData[6]=dofly_DuanMa[second/10];//秒
 TempData[7]=dofly_DuanMa[second%10];	 
}	//保存在八段数码管的数组里

if(Temp_show_flag==1&&Temp_showed_flag==0){  //温度显示标志位是1 温度已经显示标志位是0
//hour=11;
temp=0;
temp=ReadTemperature();  //使用18b20 读取温度
temphour=hour; //将当前的小时保存到临时小时变量里
temp=0;
temp=ReadTemperature();
hour=temp*0.625; //将读取的温度转换为两位数的摄氏度
Temp_showed_flag=1;	//表示已经显示温度
Temp_show_flag=0;	//下次循环不进入此分支
}
if(Temp_showed_flag==1&&Temp_show_flag==1){ //如果再次按下显示温度按键
	hour=temphour;//将保存于临时变量中的小时值显示
	Temp_show_flag=0;//温度显示标志位返回初始化
	Temp_showed_flag=0;//温度已经显示标志位返回初始化
}
	//DelayMs(200);
if(Ahour==hour&&Aminute==minute&&Asecond==second){ //闹钟时间与当前时间相等
	//hour=minute=second=0;
	if(hour!=0||second!=0||minute!=0){ //且都不等于0
	//hour=minute=second=0;
	//alarm();
    PlayMusic();  //闹钟开始
	DelayMs(5000);
	if(Time_seted_flag==1&&Alarm_closed_flag==0){ //闹钟未关闭
	Ahour=hour; //重置闹钟时间
	Aminute=minute;
	Asecond=second;  //闹钟会持续响
	}
		}
	}
}
}
