
static unsigned char i=0;
void Display(unsigned char FirstBit,unsigned char Num);//�������ʾ����
#define DataPort P0 //�������ݶ˿� ����������DataPort ����P0 �滻
sbit LATCH1=P2^2;//��������ʹ�ܶ˿� ������
sbit LATCH2=P2^3;//                 λ����
unsigned char code dofly_WeiMa[];//�ֱ��Ӧ��Ӧ������ܵ���,��λ��
extern unsigned char TempData[8]; //�洢��ʾֵ��ȫ�ֱ���
