#include <reg52.h>
#include <stdio.h>
#include <HC_SR04.h>
#include <Serial.h>
#include <Lcd1602.h>
sbit key_s3 = P3^2;//����S3
char code table[]="btx1906010314";
char code table1[]="cm";
char code table2[]="-,---\0";
	uchar i=0;
		unsigned char flag=0;
void delay(unsigned long time)//��ʱ����
{
   int i;
   int j;
   for(i=0;i<100;i++)
      for(j=0;j<time;j++);
}


void lcd_start()
{
	lcd_init();
		write_com(0x80);//���õ�ַ���ڵ�һ�е�һ����ʾѧ�ţ�0x80�ǵ�һ�е���ʼ��ַ
	while(table[i]!='\0')
	{
		write_date(table[i]);
		i++;
		delayms(5);
	}
	i=0;
	write_com(0x80+0x40+6);//���õ�ַ���ڵڶ��е�7λ��ʾcm��0x80+0x40�ǵڶ��е���ʼ��ַ
	while(table1[i]!='\0')
	{
		write_date(table1[i]);
		i++;
		delayms(5);
	}
	i=0;
}

void button()
{
	if(key_s3 == 0)
		{
			delayms(20);
			if(key_s3 == 0)
			{
				flag = 1;
				while(!key_s3);//���ּ��
			}	
		}
}

void error()
{

	write_com(0x80+0x40);
	for(i=0;i<=4;i++)
	{
		write_date(table2[i]);
		delayms(5);
	}
	write_date(0x20);
	delayms(5);
}

int main()//������
{
  char buf[20]={'\0'};//�����ڴ��ڵ���������ʾ���ַ���
  float dis=0;
  serial_init();//���ڳ�ʼ��
	lcd_start();//���LCD��ʼ�� ����ʾѧ������
  while(1)
  {
    start_HC_SR04();
    while(Echo!=1);
			startTime();
    while(Echo!=0);
			endTime();
		button();		
		if(flag==1)
	{
		clear();
		flag = 0;
		while(flag==0){
			button();
		}
		break;
	}
		dis=getDistance();//��ȡ����;
		if(dis>200)
		{
			error();//��ʾ��-.---��
		}
		else
		{
		write_com(0x80+0x40);
		display(dis);
		sprintf(buf,"getdistance=%fcm\r\n",dis);//����תΪ�ַ���
		printstr(buf);//���ڷ����ַ���
    }

		delayms(60);
 }
}




