typedef unsigned char uchar;
typedef unsigned int uint;
#include<intrins.h>
sbit lcdrs=P3^5;//数据命令选择端，为0时写指令，为1时写数据
sbit lcdrw=P3^6;//读、写命令选择端，为0时写数据，为1时读数据，读状态时置1，其他时间都是0；
sbit lcden=P3^4;//使能端

sbit STA7=P0^7;//D0~D7数据口对应P0^0~P0^7，当读液晶的数据时，STA7对应P0^7，STA7为1时表示液晶忙，无法接收数据

void delayms(unsigned char x)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
	{
		for(j=0;j<110;j++);
	}
}
void wait()//等待液晶空闲
{
	P0=0xff;
	do
	{
		lcdrs=0;//读状态操作时序
		lcdrw=1;
		lcden=0;
		lcden=1;
	}
	while(STA7==1);
	lcden=0;
}

 
void write_com(uchar com)//写命令程序
{
	delayms(5);
	lcdrs=0;
	lcdrw=0;
	lcden=1;
	P0=com;
	_nop_();
	lcden=0;
}
 
void write_date(uchar date)//写数据程序
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

/*显示函数*/
void display(float dis)
{
	uint bai,shi,ge,p1,p2;
	bai=dis/100;
	shi=(dis-bai*100)/10;
	ge=dis-bai*100-shi*10;
	p1=(dis*10)-bai*1000-shi*100-ge*10;
	p2=(dis*100)-bai*10000-shi*1000-ge*100-p1*10;
	write_date(0x30+bai);//将数字转换为字符+0x30
	write_date(0x30+shi);
	write_date(0x30+ge);
	write_date('.');
	write_date(0x30+p1);
	write_date(0x30+p2);
 
}


void clear()//清屏
{
	write_com(0x01);
	delayms(5);
}



