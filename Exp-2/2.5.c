/* 
 * Created:   Mar 29,2022
 * Processor: AT89C51
 * Compiler:  Keil for 8051
 * function:  自主设计电路，实现“按键--LED 灯”的显示效果。
 */
#include<reg51.h> 
#include<intrins.h> 
#define uchar unsigned char 
#define uint unsigned int 
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