#include <reg52.h>
#include <stdio.h>
#include <HC_SR04.h>
#include <Serial.h>
#include <Lcd1602.h>
sbit key_s3 = P3^2;//按键S3
char code table[]="btx1906010314";
char code table1[]="cm";
char code table2[]="-,---\0";
	uchar i=0;
		unsigned char flag=0;
void delay(unsigned long time)//延时函数
{
   int i;
   int j;
   for(i=0;i<100;i++)
      for(j=0;j<time;j++);
}


void lcd_start()
{
	lcd_init();
		write_com(0x80);//设置地址，在第一行第一列显示学号：0x80是第一行的起始地址
	while(table[i]!='\0')
	{
		write_date(table[i]);
		i++;
		delayms(5);
	}
	i=0;
	write_com(0x80+0x40+6);//设置地址，在第二行第7位显示cm，0x80+0x40是第二行的起始地址
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
				while(!key_s3);//松手检测
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

int main()//主函数
{
  char buf[20]={'\0'};//用来在串口调试助手显示的字符组
  float dis=0;
  serial_init();//串口初始化
	lcd_start();//完成LCD初始化 并显示学号姓名
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
		dis=getDistance();//获取距离;
		if(dis>200)
		{
			error();//显示“-.---”
		}
		else
		{
		write_com(0x80+0x40);
		display(dis);
		sprintf(buf,"getdistance=%fcm\r\n",dis);//距离转为字符串
		printstr(buf);//串口发送字符串
    }

		delayms(60);
 }
}




