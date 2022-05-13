#include <reg52.h>

unsigned char code Table[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char count,number;
unsigned char number1,number2;
unsigned char Init_Flag = 0;
unsigned char Stop_Flag = 0;
	
sbit P2_2 = P2^2;
sbit P2_3 = P2^3;
sbit P2_4 = P2^4;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;

void Delay4ms()
{
	unsigned char i, j;

	i = 8;
	j = 40;
	do
	{
		while (--j);
	} while (--i);
}

void Timer0Init(void)
{
	EA = 1;
	TMOD = 0x01;
	TL0 = 0xCD;
	TH0 = 0xF8;
	TF0 = 0;
	ET0 = 1;
	TR0 = 1;
}

void Timer1Init(void)	//50000微秒
{
	EA = 1;
	TMOD &= 0x0F;
	TMOD |= 0x10;
	PT1 = 1;
	TL1 = 0x00;
	TH1 = 0x4C;
	TF1 = 0;
	ET1 = 1;
	TR1 = 1;
}

void EX0Init(void)
{
	IT0 = 1;	//边沿触发
	EX0 = 1;	//允许外部中断0中断
}

void EX1Init(void)
{
	IT1 = 1;	//边沿触发
	EX1 = 1;	//允许外部中断0中断
}

void main()
{	
	Start:
	count = 20;
	number = 0;
	EX0Init();
	EX1Init();
	Timer0Init();
	Timer1Init();
	
	while(1)
	{
		if(Init_Flag == 1)
		{
			Init_Flag = 0;
			goto Start;
		}
		if(Stop_Flag == 1)
		{
			Stop_Flag = 0;
			if(TR1 == 0)
			{
				TR1 = 1;
			}
			else if(TR1 == 1)
			{
				TR1 = 0;
			}	
		}
	}
}

void InterruptTimer0() interrupt 1
{	
	static unsigned char i = 0;
	
	number1 = number / 10;
	number2 = number % 10;
	
	TL0 = 0xCD;		
	TH0 = 0xF8;	
	
	P0 = 0x00;
	
	switch(i)
	{
		case 0:P2_4=1;P2_3=1;P2_2=1;i++; P0=Table[number1]; break;
		case 1:P2_4=1;P2_3=1;P2_2=0;i=0; P0=Table[number2]; break;
		default: break;
	}
}

void InterruptTimer1() interrupt 3
{
	if(count != 0)
	{
		count--;
	}
	else
	{
		TF1 = 0;
		TL1 = 0x00;
		TH1 = 0x4C;
		count = 20;
		
		number++;
		
		if(number == 100)
		{
			number =0;
		}
	}
}

void Int0_Routine() interrupt 0
{
	Delay4ms();
	if(P3_2 == 0)
	{
		Init_Flag = 1;
	}
}

void Int1_Routine() interrupt 2
{
	Delay4ms();
	if(P3_3 == 0)
	{
		Stop_Flag = 1;
	}
}