#include<reg51.h>
#define BAUDRATE 9600 //���岨����Ϊ9600
#define SYSCLK 11059200	 //ϵͳʱ��Ƶ��
#define uchar unsigned char
void Uart() ;
void uart_init();
void main(){
   	uchar temp;
  	uart_init();    
    do
	{
     	while(!RI);	//�ȴ����ڽ����������
        RI=0; // RI��0��Ϊ�´ν�����׼��
        temp=SBUF;//���������ݽ��յ�����temp��
        SBUF=temp;	//����һ�δ������ݷ���
        while(!TI);	//�ȴ����ݷ������
        TI=0; //TI��0��Ϊ�´η�����׼��
   	} while(1);
 }
void uart_init()
{
 TMOD=0X20;//���ö�ʱ��1��8λ�Զ���װ�ط�ʽ
 PCON=0; //����PCON�Ĵ����е�SMOD=0,�������ʲ��ӱ�
 TL1 = TH1 = 256 - SYSCLK /BAUDRATE / 32 / 12;
  SCON=0X50;
  TR1=1;//������ʱ��1����
}
