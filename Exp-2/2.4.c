/* 
 * Created:   Mar 29,2022
 * Processor: AT89C51
 * Compiler:  Keil for 8051
 * function:  更改电路：将图 1 中的 2 个按键开关改为单刀单掷开关（switch），实现：K2K1=10 时，
              出现实验 2 的效果；K2K1=01 时，出现实验 3 的效果；K2K1=00 时，实现闪烁效果；
              K2K1=11 时，灯全灭。
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