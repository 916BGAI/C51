#include <reg51.h>

sbit P1_0 = P1 ^ 0;

unsigned char n = 10;

void main(void)
{
    TMOD = 0x01;
    P1_0 = 0;
    TH0 = (65536 - 50000 / 256);
    TL0 = (65536 - 50000 % 256);
    EA = 1;
    ET0 = 1;
    TR0 = 1;

    while(1);
}

void timer0(void)interrupt 1 using 1
{
    if(n != 0)
    {
        n--;
    }
    else
    {
        P1_0 = !P1_0;
        TH0 = (65536 - 50000 / 256);
        TL0 = (65536 - 50000 % 256);
        n = 10;
    }

}
