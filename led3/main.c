#include <reg51.h>    		
#define uint unsigned int 
#define uchar unsigned char
void delayms(uint);		
uchar a,b;          
void main()		      	
{
int n,m,x;
a=0xfe;
b=0x7f;					 
	while(1)		 	
	{
		for(m=9;m>1;m--){
        P1=b;
		delayms(50);
        b=(b>>1)|0x80;
        if(b==0xff){
                    b=0x7f;  break; }
		}       	

		for(n=9;n>1;n--){
        P1=a;
		delayms(50);            
        a=(a<<1)|1;
        if(a==0xff){
                 a=0xfe;   break;}    	
		}	  	
			
  	}
}

void delayms(uint xms)  
{
	uint i,j;
	for(i=xms;i>0;i--)		      
		for(j=110;j>0;j--);
}
