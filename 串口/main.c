#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
main()
{
	uchar temp;
	uint i;
	SCON = 0x00;	//设置串口工作方式：方式0
	temp = 0x01;	//设置显示初值：0000 0001,7个亮1个灭
	while(1)
	{
	SBUF = temp;	//将数据写入SBUF->串口开始发送操作
	while(!TI);	//等待串口输出完毕，如果输出完，硬件会自动使TI=1
	TI = 0;		//清除发送标志，等待下一次发送结束
	for(i=0; i<20000;i++);//延时

	temp *=2;	//修改数据，使下一个灯亮（左移1位）
	if(temp == 0x00)
		temp = 0x01;//如果数据全0，恢复为初始数据			}
}
}
