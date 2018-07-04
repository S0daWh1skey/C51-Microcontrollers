#include<reg52.h>
#include"1602.h"
#include"delay.h"
#include"clock.h"
#include<intrins.h>

unsigned char date[11]={'1','9','9','9','-','1','2','-','3','1'};
unsigned char time[9]={'2','3',':','5','9',':','5','5'};
unsigned char alarm[9]={'0','0',':','0','0',':','0','0'};
unsigned char alarmflag=0,mode=0,flag=0;//闹钟开关，选择年月日时分秒，时钟模式/闹钟模式
unsigned char cnt=0;

void dating(void)
{
	unsigned int y,m,d;
	unsigned char month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	y=(date[0]-'0')*1000+(date[1]-'0')*100+(date[2]-'0')*10+(date[3]-'0');
	m=(date[5]-'0')*10+(date[6]-'0');
	d=(date[8]-'0')*10+(date[9]-'0')+1;
	if(y%400==0||y%100!=0&&y%4==0)
		month[2]=29;
	else month[2]=28;
	if(d>month[m])
	{
		m++;
		d=1;
	}
	if(m>12)
	{
		y++;
		m=1;
	}
	if(y>9999)y=0;
	date[0]=y/1000+'0';
	date[1]=y/100%10+'0';
	date[2]=y/10%10+'0';
	date[3]=y%10+'0';
	date[5]=m/10+'0';
	date[6]=m%10+'0';
	date[8]=d/10+'0';
	date[9]=d%10+'0';
}
void timing(void)
{
	unsigned int h,m,s;
	h=(time[0]-'0')*10+(time[1]-'0');
	m=(time[3]-'0')*10+(time[4]-'0');
	s=(time[6]-'0')*10+(time[7]-'0')+1;
	if(s>59)
	{
		s=0;
		m++;
	}
	if(m>59)
	{
		m=0;
		h++;
	}
	if(h>23)
	{
		h=0;
		dating();
	}
	time[0]=h/10+'0';
	time[1]=h%10+'0';
	time[3]=m/10+'0';
	time[4]=m%10+'0';
	time[6]=s/10+'0';
	time[7]=s%10+'0';
}
bit cmp(char *a,char *b)
{
	int i;
	for(i=0;i<8;i++)
		if(a[i]!=b[i])
			return 0;
	return 1;
}

void timer(void) interrupt 1
{
	cnt++;
	if(cnt==15)
	{
		cnt=0;
		timing();
	}
}

void init()
{
	cnt=0;
	TMOD=0x01;
	TL0=15536%256;
	TH0=15536/256;
	IT1=IT0=EA=EX1=EX0=ET0=TR0=1;
}

void main(void)
{
	unsigned char m,d,h,mi,s,month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	unsigned int y,add_sub=0,n=1000;
	P3=0xff;
	init();
	LCD_Init();	
	LCD_Clear();
	while(1)
	{
		if(alarmflag&&cmp(time,alarm))
		{
			while(n--)
			Beep=~Beep;
			n=1000;
		}
		Beep=0;
		LCD_Write_String(3,0,date);
		if(flag==0)
			LCD_Write_String(4,1,time);
		else if(flag==1)
			LCD_Write_String(4,1,alarm);
		LCD_Write_Char(0,0,(alarmflag+'0'));
		LCD_Write_Char(15,0,(mode+'0'));
		LCD_Write_Char(0,1,(flag+'0'));
		if(!KEY1)
		{
			while(!KEY1);
			if(flag)
			{
				mode++;
				if(mode>3)
					mode=0;
			}
			else 
			{
				mode++;
				if(mode>6)
					mode=0;
			}
		}
		if(!KEY2||!KEY3)
		{
			if(!KEY2)
			{
				while(!KEY2);
				add_sub=1;
			}
			else if(!KEY3)
			{
				while(!KEY3);
				add_sub=-1;
			}
			if(mode==1)
			{
				if(flag==0)
				{
					s=(time[6]-'0')*10+(time[7]-'0')+add_sub;
					if(s>59)s=0;
					time[6]=s/10+'0';
					time[7]=s%10+'0';
				}
				else 
				{
					s=(alarm[6]-'0')*10+(alarm[7]-'0')+add_sub;
					if(s>59)s=0;
					alarm[6]=s/10+'0';
					alarm[7]=s%10+'0';
				}
			}
			else if(mode==2)
			{
				if(flag==0)
				{
					mi=(time[3]-'0')*10+(time[4]-'0')+add_sub;
					if(mi>59)mi=0;
					time[3]=mi/10+'0';
					time[4]=mi%10+'0';
				}
				else
				{
					mi=(alarm[3]-'0')*10+(alarm[4]-'0')+add_sub;
					if(mi>59)mi=0;
					alarm[3]=mi/10+'0';
					alarm[4]=mi%10+'0';
				}
			}
			else if(mode==3)
			{
				if(flag==0)
				{
					h=(time[0]-'0')*10+(time[1]-'0')+add_sub;
					if(h>24)h=0;
					time[0]=h/10+'0';
					time[1]=h%10+'0';
				}
				else 
				{
					h=(alarm[0]-'0')*10+(alarm[1]-'0')+add_sub;
					if(h>24)h=0;
					alarm[0]=h/10+'0';
					alarm[1]=h%10+'0';
				}
			}
			else if(mode==4)
			{		
				y=(date[0]-'0')*1000+(date[1]-'0')*100+(date[2]-'0')*10+(date[3]-'0');
				m=(date[5]-'0')*10+(date[6]-'0');
				d=(date[8]-'0')*10+(date[9]-'0')+add_sub;
				if(y%400==0||y%100!=0&&y%4==0)
					month[2]=29;
				else month[2]=28;
				if(d>month[m])d=0;
				date[8]=d/10+'0';
				date[9]=d%10+'0';
			}
			else if(mode==5)
			{
				y=(date[0]-'0')*1000+(date[1]-'0')*100+(date[2]-'0')*10+(date[3]-'0');
				m=(date[5]-'0')*10+(date[6]-'0')+add_sub;
				if(m>12)m=0;
				date[5]=m/10+'0';
				date[6]=m%10+'0';
			}
			else if(mode==6)
			{
				y=(date[0]-'0')*1000+(date[1]-'0')*100+(date[2]-'0')*10+(date[3]-'0')+add_sub;
				if(y>9999)y=0;
				date[0]=y/1000+'0';
				date[1]=y/100%10+'0';
				date[2]=y/10%10+'0';
				date[3]=y%10+'0';
			}
		}
		if(!KEY4)
		{
			while(!KEY4);
			mode=0;
			if(flag)
				flag=0;
			else flag=1;
		}
		if(!KEY5)
		{
			while(!KEY5);
			if(alarmflag)
				alarmflag=0;
			else alarmflag=1;
		}
	}
}
//0123456789ABCDEF
//0**2017-01-01**0
//0***00:00:00****
//左上角闹钟开关
//右上角选择年月日时分秒
//左下角选择时钟/闹钟模式
