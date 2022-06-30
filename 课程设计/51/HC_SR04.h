sbit Echo=P3^3;
sbit Trig=P1^4;

void delay10us()//精准延时10us函数 定时器0
{
	TMOD=0x01;//工作方式1
	TH0=0xff;
	TL0=0xf6;
	TR0=1;
	while(!TF0);//定时器查询方法
	TF0=0;
}


void start_HC_SR04()//启动超声波模块
{
  Trig=0;
  Trig=1;
  delay10us();
  Trig=0;
}

float getDistance()//获取距离的函数
{
   float distance;
	 unsigned int time;
   time=TH0<<8|TL0;	 
	 distance=(float)time*(0.0184);//计算方法s=340t/2=340*t(10*10^(-3))=0.017
	 return distance;
}


void endTime()//停止记时
{
   TR0=0;
}


void startTime()//开始记时
{
   TH0=0;
   TL0=0;
   TR0=1;
}