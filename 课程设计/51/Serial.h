void serial_init()
{
	 SCON=0x50;
	 TMOD=0x20;
	 TH1=0xFD;
	 TL1=0xFD;//波特率9600
	 TR1=1;
	 EA=1;
	 ES=1;
}

void getSBUF(char c)//发1个字节
{
   SBUF=c;  
   while(TI!=1);
	 TI=0;
}

void printstr(char *pstr)//打印字符串函数 指向字符串首地址
{
   while(*pstr!='\0')
   {
   getSBUF(*pstr);
   pstr++;
   }
  
}