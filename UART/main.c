#include <REGX52.H>
#include <stdio.h>
#include "Delay.h"

#define LED P2

unsigned char flag = 0,i,flag_t,s[50]="",j=0,flag_n=0;

unsigned char flag_l = 2;

void Uart_Init()
{
	SCON = 0x50;
	TMOD = 0x20;
	PCON = 0x00;
	TL1 = 0xFD;
	TH1 = 0xFD;
	ET1 = 0;
	TR1 = 1;
	ES = 1;
    EA = 1;
}

void main()
{
	Uart_Init();

	while(1)
	{
		if(flag==1)
		{
			if(flag_n!=0)        //使第二个及以后I get xx 换行，不与You transfer在一行（单纯为了格式好看）  
			{
				TI=1;
				printf("\n");
				while(!TI);
				TI=0;
			}  
			
			for(i=0;s[i]!='\n'&&i<50;i++)
			{  
				SBUF=s[i];
				while(!TI);
				TI=0;
			}  
				flag=0;
		}  
		
		if(flag_t==1)                          //发送完毕之后，在电脑端输出。  
		{  
			if(flag_l == 1)
			{
				TI=1;
				printf("\n你点亮了LED");
				while(!TI);
				TI=0;
			}
			
			else if(flag_l == 0)
			{
				TI=1;
				printf("\n你熄灭了LED");
				while(!TI);
				TI=0;
			}
			
			flag_t=0;  
		}     
	}
}

void UART_Routine(void)		interrupt 4
{
	if(RI)
    {
		RI=0;
		
        if(flag==0&&j!=0)//1.循环赋值为'\0'(字符串结尾标志符),j=0，为了第二次传递字符串是又是从头输出  
        {            //2.flag为0和j不为0时，保证是第二次及以后，传输字符串（控制输出格式）  
            flag_n = 1;              
            for(j=0;s[j]!='\n'&&j<50;j++)  
            s[j]='\0';  
            j=0;  
        }  
		
        s[j]=SBUF;  
        flag=1;  
//		if(((s[0]=='1')&&(s[j] == '#'))||j==49)     //以'#'作为传送字符串的结尾符，我定义的字符数组最长为50所以49也应该结束。
//		{
//			flag_t=1;
//			LED = 0x00;
//			
//		}
//        else if(s[0] == '0')
//		{
//			flag_t=1;
//			LED = 0xff;
//		}
//		else
//			j++;
        if(s[j]=='\n'||j==49)     //以'#'作为传送字符串的结尾符，我定义的字符数组最长为50所以49也应该结束。
        {
			if(s[0]=='1')
			{
				LED = 0x00;
				flag_l = 1;
			}
			else if(s[0]=='0')
			{
				LED = 0xff;
				flag_l = 0;
			}
			
			flag_t=1;
		}   
        else  
            j++;  
		
    }  

    if(TI)     //发送数据
    {
    }
}