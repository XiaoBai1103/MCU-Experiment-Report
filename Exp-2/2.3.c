/* 
 * Created:   Mar 29,2022
 * Processor: AT89C51
 * Compiler:  Keil for 8051
 * function:  编程实现, 上电时 LED 灯全亮。按下 K1 时, LED 上移一位；按下 K2, LED 下移一位。
 */
void DelayMS(uint x) 
{ 
 uchar i; 
 while(x--) 
 { 
 for(i=0;i<120;i++); 
 } 
} 
void main() 
{ 
 uchar i; 
 P0=0xFE; 
   DelayMS(150); 
 while(1) 
 { 
   for(i=0;i<7;i++) 
   { 
      P0=_crol_(P0,1); 
      DelayMS(150); 
   } 
   for(i=0;i<7;i++) 
   { 
      P0=_cror_(P0,1); 
      DelayMS(150); 
   } 
 } 
}