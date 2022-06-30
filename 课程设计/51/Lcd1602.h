typedef unsigned char uchar;
typedef unsigned int uint;
#include<intrins.h>
sbit lcdrs=P3^5;//��������ѡ��ˣ�Ϊ0ʱдָ�Ϊ1ʱд����
sbit lcdrw=P3^6;//����д����ѡ��ˣ�Ϊ0ʱд���ݣ�Ϊ1ʱ�����ݣ���״̬ʱ��1������ʱ�䶼��0��
sbit lcden=P3^4;//ʹ�ܶ�

sbit STA7=P0^7;//D0~D7���ݿڶ�ӦP0^0~P0^7������Һ��������ʱ��STA7��ӦP0^7��STA7Ϊ1ʱ��ʾҺ��æ���޷���������

void delayms(unsigned char x)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<110;j++);
	}
}
void wait()//�ȴ�Һ������
{
	P0=0xff;
	do
	{
		lcdrs=0;//��״̬����ʱ��
		lcdrw=1;
		lcden=0;
		lcden=1;
	}
	while(STA7==1);
	lcden=0;
}

 
void write_com(uchar com)//д�������
{
	delayms(5);
	lcdrs=0;
	lcdrw=0;
	lcden=1;
	P0=com;
	_nop_();
	lcden=0;
}
 
void write_date(uchar date)//д���ݳ���
{
	wait();
	lcdrs=1;
	P0=date;
	lcdrw=0;
	delayms(5);
	lcden=1;
	delayms(5);
	lcden=0;
}

void lcd_init()
{
	wait();
	lcden=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}

/*��ʾ����*/
void display(float dis)
{
	uint bai,shi,ge,p1,p2;
	bai=dis/100;
	shi=(dis-bai*100)/10;
	ge=dis-bai*100-shi*10;
	p1=(dis*10)-bai*1000-shi*100-ge*10;
	p2=(dis*100)-bai*10000-shi*1000-ge*100-p1*10;
	write_date(0x30+bai);//������ת��Ϊ�ַ�+0x30
	write_date(0x30+shi);
	write_date(0x30+ge);
	write_date('.');
	write_date(0x30+p1);
	write_date(0x30+p2);
 
}


void clear()//����
{
	write_com(0x01);
	delayms(5);
}



