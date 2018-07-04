#include <reg51.h>
#define uint unsigned int 
#define uchar unsigned char
sbit beep = P2^4;
uchar code SONG_TONE[]={212,212,190,212,159,169,212,212,190,212,142,159,
212,212,106,126,159,169,190,119,119,126,159,142,159,0};

uchar code SONG_LONG[]={9,3,12,12,12,24,9,3,12,12,12,24,
9,3,12,12,12,12,12,9,3,12,12,12,24,0};

//延时
void DelayMS(uint x)
{
uchar t;
while(x--) for(t=0;t<120;t++);
}

void PlayMusic()
{
uint i=0,j,k;
while(SONG_LONG[i]!=0||SONG_TONE[i]!=0)
{ //播放各个音符，SONG_LONG 为拍子长度
    for(j=0;j<SONG_LONG[i]*20;j++)
{
    beep=~beep;
//SONG_TONE 延时表决定了每个音符的频率
    for(k=0;k<SONG_TONE[i]/3;k++);
}
    DelayMS(10);
    i++;
}
}


void main()
{

beep=0;
while(1)
{
PlayMusic(); //播放生日快乐
DelayMS(500); //播放完后暂停一段时间
}
}