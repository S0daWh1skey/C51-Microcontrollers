
static unsigned char i=0;
void Display(unsigned char FirstBit,unsigned char Num);//数码管显示函数
#define DataPort P0 //定义数据端口 程序中遇到DataPort 则用P0 替换
sbit LATCH1=P2^2;//定义锁存使能端口 段锁存
sbit LATCH2=P2^3;//                 位锁存
unsigned char code dofly_WeiMa[];//分别对应相应的数码管点亮,即位码
extern unsigned char TempData[8]; //存储显示值的全局变量
