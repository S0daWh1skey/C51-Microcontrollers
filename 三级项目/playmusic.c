#include<reg52.h>
#include"playmusic.h"
#include"delay.h"
//����������
unsigned char SONG_TONE[]={212,212,190,212,159,169,212,212,190,212,142,159,212,212,106,126,159,169,190,119,119,126,159,142,159,0};
unsigned char SONG_LONG[]={9,3,12,12,12,24,9,3,12,12,12,24,9,3,12,12,12,12,12,9,3,12,12,12,24,0};
void PlayMusic()
{
unsigned int i=0,j,k;
//if(Cancel_Alarm_flag==1){break;}
//Time_seted_flag=0;
while(SONG_LONG[i]!=0||SONG_TONE[i]!=0)
{ //���Ÿ���������SONG_LONG Ϊ���ӳ���
    for(j=0;j<SONG_LONG[i]*20;j++)
{
    beep=~beep;
//SONG_TONE ��ʱ�������ÿ��������Ƶ��
    for(k=0;k<SONG_TONE[i]/3;k++);
}
    DelayMs(10);
    i++;
}

}
