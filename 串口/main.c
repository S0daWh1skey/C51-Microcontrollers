#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
main()
{
	uchar temp;
	uint i;
	SCON = 0x00;	//���ô��ڹ�����ʽ����ʽ0
	temp = 0x01;	//������ʾ��ֵ��0000 0001,7����1����
	while(1)
	{
	SBUF = temp;	//������д��SBUF->���ڿ�ʼ���Ͳ���
	while(!TI);	//�ȴ����������ϣ��������꣬Ӳ�����Զ�ʹTI=1
	TI = 0;		//������ͱ�־���ȴ���һ�η��ͽ���
	for(i=0; i<20000;i++);//��ʱ

	temp *=2;	//�޸����ݣ�ʹ��һ������������1λ��
	if(temp == 0x00)
		temp = 0x01;//�������ȫ0���ָ�Ϊ��ʼ����			}
}
}
