#include <REGX52.H>
#include "Delay.h"

#define LED P2

sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

void initEx0() 
{
  EA = 1;
  EX0 = 1;
  IT0 = 1;
}

void initEx1() 
{
  EA = 1;	
  EX1 = 1;
  IT1 = 1;
}

void main()
{
	initEx0();
	initEx1();
	
	LED = 0xFF;
	
	while(1)
	{
		
	}
}

void Int0_Routine(void)		interrupt 0
{
	Delay(20);
	while(KEY3 == 0);
	Delay(20);
	LED = 0x00;
}

void Int1_Routine(void)		interrupt 2
{
	Delay(20);
	while(KEY4 == 0);
	Delay(20);
	LED = 0xFF;
}