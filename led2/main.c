#include <reg52.h>
void delayms(unsigned int i)
{
  unsigned int j;
  for(;i>0;i--)
     for(j=100;j>0;j--);
}
void main()
{
   while(1)
   {
     P1=0x00;
     delayms(1000);
     P1=0xff;
     delayms(1000);
   }
}
