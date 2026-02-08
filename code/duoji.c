/*
			模拟舵机控制原理：0~180°
				0.5ms-----0度
				1.0ms-----45度
				1.5ms-----90度
				2.0ms-----135度
				2.5ms-----180度
*/

#include <REGX52.H>
#include "Timer0.h"
#include "delay.h"

sbit SG_PWM=P2^0;							//信号控制引脚						 红——VCC 棕——GND 黄——信号线
unsigned char c=0;					     //计次  赋初值为0
unsigned char PWM_count=0;                  //0--0度，2--45度，4--90度，6--135度，8--180度

void Unlock()
{
  P2=0x00;
	Timer0_Init();
	PWM_count=1;
	Delay(1000);
	Timer0_close();
}
void Lock()
{
	P2=0x00;
	Timer0_Init();
	PWM_count=3;
	Delay(1000);
	P2=0x00;
	Timer0_close();
	
}

void Timer0() interrupt 1      //特别注意此处，0--外部中断0，1--定时器中断0，2--外部中断1，3--定时器中断1，4--串行口中断1
{
  
  TL0 = 0x33;		
  TH0 = 0xFE;			 	//重新赋计数初值为0.5ms
  
  c++;					//计次，每500us  count+1
	c%=40;				//周期为20ms
	
  if(c<PWM_count)
  {									
    SG_PWM=1;
  }
  else
  {
    SG_PWM=0;
  }
}
