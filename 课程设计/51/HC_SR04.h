sbit Echo=P3^3;
sbit Trig=P1^4;

void delay10us()//��׼��ʱ10us���� ��ʱ��0
{
	TMOD=0x01;//������ʽ1
	TH0=0xff;
	TL0=0xf6;
	TR0=1;
	while(!TF0);//��ʱ����ѯ����
	TF0=0;
}


void start_HC_SR04()//����������ģ��
{
  Trig=0;
  Trig=1;
  delay10us();
  Trig=0;
}

float getDistance()//��ȡ����ĺ���
{
   float distance;
	 unsigned int time;
   time=TH0<<8|TL0;	 
	 distance=(float)time*(0.0184);//���㷽��s=340t/2=340*t(10*10^(-3))=0.017
	 return distance;
}


void endTime()//ֹͣ��ʱ
{
   TR0=0;
}


void startTime()//��ʼ��ʱ
{
   TH0=0;
   TL0=0;
   TR0=1;
}