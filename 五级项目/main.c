#include<reg52.h>
#include <string.h>
#define BAUDRATE 9600
#define SYSCLK 11059200
//sbit LED = P2;
sbit BUZ = P0^0;
bit flag = 0;//�Ƿ����ַ�����־
unsigned char str[7];//�����ַ���
bit n=1;
void DelayMs(unsigned int xms);
void DelayUs2x(unsigned char t)
{   
 while(--t);
}

void DelayMs(unsigned char t)
{
     
 while(t--)
 {
     DelayUs2x(2);
	 DelayUs2x(2);
 }
}
void Buz_Contr(unsigned char i)
{
	if(i==0){	
		DelayMs(100); 
		BUZ=!BUZ;
	}
	else BUZ=1;
}
void SendStr(unsigned char *s)
{
    while(*s!='\0')
	{
		SBUF = *s;
		s++;
		while(!TI);
		TI = 0;
	}
}
void init()
{
   	TMOD=0X20;//���ö�ʱ��1��8λ�Զ���װ�ط�ʽ
   	PCON=0; //����PCON�Ĵ����е�SMOD=0,�������ʲ��ӱ�
   	TL1 = TH1 = 256 - SYSCLK /BAUDRATE / 32 / 12;
   	SCON=0X50;
		EA=1;
		ES=1;
		TR1=1;//������ʱ��1����
}
void uart_int(void)interrupt 4 
{
	static unsigned char i=0;
	unsigned char temp;
	if(RI == 1)
    {		
		RI = 0;
		temp = SBUF;
		if(i == 0)
		{
			if(temp == '#')
			{
				str[i++] = temp;
			}
		}
		else
		{
			str[i++] = temp;
			if(i>=5)
			{		
				str[i]='\0';
				flag = 1;
				i=0;
			}
		}		
    }
}
main()
{
	init();
	while(1)
	{
		if(flag == 1)
		{
			flag = 0;
			if(strcmp(str,"#LEDO")==0)
			{
					P1=0x00;
				}
			else if(strcmp(str,"#LEDF")==0)
			{	
					P1=0xff;				
				}
			else if(strcmp(str,"#BUZO")==0)
			{		
					SendStr("spk ON\n");
					n=0;
				}
			else if(strcmp(str,"#BUZF")==0)
			{
					SendStr("spk OFF\n");
					n=1;
				}
			}
			Buz_Contr(n);
			}
	}

