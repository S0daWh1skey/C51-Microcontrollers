#include<reg51.h>
#define BAUDRATE 9600 //定义波特率为9600
#define SYSCLK 11059200	 //系统时钟频率
#define uchar unsigned char
void Uart() ;
void uart_init();
void main(){
   	uchar temp;
  	uart_init();    
    do
	{
     	while(!RI);	//等待串口接收数据完毕
        RI=0; // RI清0，为下次接收做准备
        temp=SBUF;//将串口数据接收到变量temp中
        SBUF=temp;	//启动一次串口数据发送
        while(!TI);	//等待数据发送完毕
        TI=0; //TI清0，为下次发送做准备
   	} while(1);
 }
void uart_init()
{
 TMOD=0X20;//启用定时器1：8位自动重装载方式
 PCON=0; //设置PCON寄存器中的SMOD=0,即波特率不加倍
 TL1 = TH1 = 256 - SYSCLK /BAUDRATE / 32 / 12;
  SCON=0X50;
  TR1=1;//启动定时器1工作
}
