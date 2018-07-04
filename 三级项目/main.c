#include<reg52.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���
#include"delay.h"
#include"display.h"
#include"playmusic.h"
#include"keyscan.h"
#include"timer.h"
#include"18b20.h"
unsigned char num;//��ü��̰���������
unsigned char hour,minute,second;//����ʱ����
unsigned char Ahour,Aminute,Asecond;//�������ӵ�ʱ����
bit UpdateTimeFlag;//�������ʱ���־
unsigned char code dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};// ��ʾ����ֵ0~9
unsigned char code dofly_WeiMa[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//�ֱ��Ӧ��Ӧ������ܵ���,��λ��
unsigned char TempData[8]; //�洢��ʾֵ��ȫ�ֱ���
bit Time_seted_flag=0; //ʱ�����ñ�־λ
bit Temp_show_flag=0; //�¶���ʾ��־λ
bit Alarm_seted_flag=0;//�������ñ�־λ
bit Temp_showed_flag=0;//�Ѿ���ʾ�¶ȱ�־λ
bit Alarm_closed_flag=0;
int temp; //�¶�
int temphour;	//��ʱ���浱ǰСʱ
/*------------------------------------------------
                    ������
------------------------------------------------*/
void main (void)
{
//unsigned char num;                  
Init_Timer0();//���ö�ʱ����ʼ������
while (1)         //��ѭ��
{
num=KeyScan();//��ȡ��������
switch(num)//switch���� ���Ʋ�ͬ����
{
   	    case 1:hour++;if(hour==24)hour=0;     //����ʱ�� Сʱ ��1
             break;
		case 3:minute++;if(minute==60)minute=0;     //���Ӽ�1
	         break;
		case 5:second++;if(second==60)second=0;     //���Ӽ�1
	         break;
		case 7:Time_seted_flag=1; //����ʱ��
			break;
		case 8:Alarm_seted_flag=1;//�������� ��������
			break;
		case 2:Temp_show_flag=1; //��ʾ�¶�
			 break;
		case 4:Alarm_closed_flag=1;//���ӹرձ�־λ
			break;
		default:break;
}

if(Alarm_seted_flag==1){
	Ahour=hour;      //����ʾ������ʾ��ʱ�䴢�浽���ӱ�����
	Aminute=minute;
	Asecond=second;
	hour=minute=second=0;//����ʾ����Ϊ��ʼ״̬00-00-00
	Time_seted_flag=0;//��ʾʱ��û����
	Alarm_seted_flag=0;//����δ���� ���������´�ѭ���м���ִ�������֧��
}

if(UpdateTimeFlag==1)//ʱ����±�־λ=1 ��ʼ����ʾ������ʱ��
{
 UpdateTimeFlag=0;//���±�־λ���� �Ա����½���
 TempData[0]=dofly_DuanMa[hour/10]; //ʱ �õ���λ����ǰһλ			//���ݵ�ת���������ǲ��������0~9����ʾ,�����ݷֿ�
 TempData[1]=dofly_DuanMa[hour%10]; //�õ���λ���ĺ�һλ
 TempData[2]=0x40;					    	        //����"-"
 TempData[3]=dofly_DuanMa[minute/10];//��
 TempData[4]=dofly_DuanMa[minute%10];
 TempData[5]=0x40;//��ʾΪ "-"
 TempData[6]=dofly_DuanMa[second/10];//��
 TempData[7]=dofly_DuanMa[second%10];	 
}	//�����ڰ˶�����ܵ�������

if(Temp_show_flag==1&&Temp_showed_flag==0){  //�¶���ʾ��־λ��1 �¶��Ѿ���ʾ��־λ��0
//hour=11;
temp=0;
temp=ReadTemperature();  //ʹ��18b20 ��ȡ�¶�
temphour=hour; //����ǰ��Сʱ���浽��ʱСʱ������
temp=0;
temp=ReadTemperature();
hour=temp*0.625; //����ȡ���¶�ת��Ϊ��λ�������϶�
Temp_showed_flag=1;	//��ʾ�Ѿ���ʾ�¶�
Temp_show_flag=0;	//�´�ѭ��������˷�֧
}
if(Temp_showed_flag==1&&Temp_show_flag==1){ //����ٴΰ�����ʾ�¶Ȱ���
	hour=temphour;//����������ʱ�����е�Сʱֵ��ʾ
	Temp_show_flag=0;//�¶���ʾ��־λ���س�ʼ��
	Temp_showed_flag=0;//�¶��Ѿ���ʾ��־λ���س�ʼ��
}
	//DelayMs(200);
if(Ahour==hour&&Aminute==minute&&Asecond==second){ //����ʱ���뵱ǰʱ�����
	//hour=minute=second=0;
	if(hour!=0||second!=0||minute!=0){ //�Ҷ�������0
	//hour=minute=second=0;
	//alarm();
    PlayMusic();  //���ӿ�ʼ
	DelayMs(5000);
	if(Time_seted_flag==1&&Alarm_closed_flag==0){ //����δ�ر�
	Ahour=hour; //��������ʱ��
	Aminute=minute;
	Asecond=second;  //���ӻ������
	}
		}
	}
}
}
