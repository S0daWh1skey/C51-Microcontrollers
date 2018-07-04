/*#include <reg51.h>
typedef unsigned int uint;
typedef unsigned char uchar;
#define ms 100
void delayms(uint s)
{
	int t;
	while(s--)
		for(t = 0;t != ms;t++);
}
void main (){
  uchar code table[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
  uint i;
  while (1)
  {
      for (i=0;i<10;i++)
	  {
        P1=table[i];
        delayms(1000);
      }
  }
}
*/

/*#include <reg52.h>  
#define LONG 50000  
#define SHORT 10000  
  
//先定义字形码，table数组中装下了自形0到9  
unsigned int table[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};  
  
//延时函数  
void delay(int i) {  
    while(i--) {  
    }  
}  
  
void main() {  
    int i = 0;  
    while(1) {  
        for(i = 0; i < 10; i++) {  
            P0 = table[i];  
            delay(LONG);  
        }  
    }  
}  
*/

#include<reg51.h>
void delayms(uint);
typedef unsigned int uint;
typedef unsigned char uchar;
uchar code a[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x7f};	
void main(){
while(1){
		uchar x;
		for(x=0;x<10;x++){
		P1=a[x];
		delayms(500);	
		}	
	}
}
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
	for(j=110;j>0;j--);
}

