#include<reg51.h>
#define LED P2
sbit KEY=P3^3;
void EnableInt1(void)
{
	IT1=1;
	EA=1;
	EX1=1;
}
void Int(void)interrupt 2
{
	LED=~LED;
}
main()
{
	EnableInt1();
	LED=0;
	while(1);

}

