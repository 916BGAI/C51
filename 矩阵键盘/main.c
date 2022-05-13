#include <reg51.h>

unsigned char code table[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E};

/**
void Delay(void)
{
    unsigned char i, j;

    for(i = 0; i < 20; i++)
        for(j = 0; j < 250; j++);
}
**/

void Display(unsigned char i)
{
    P2 = 0x7F;
    P0 = table[i];
}

void Keyscan(void)
{
    unsigned char m, n;
    P1 = 0xF0;
    m = P1;
    n &= 0xF0;
    P1 = 0x0F;
    n = P1;
    n &= 0x0F;
    m = m | n;

    switch(m)
    {
        case(0xEE):
            Display(3);
            break; //1110_1110

        case(0xDE):
            Display(2);
            break; //1101_1110

        case(0xBE):
            Display(1);
            break; //1011_1110

        case(0x7E):
            Display(0);
            break; //0111_1110

        case(0xED):
            Display(7);
            break; //1110_1101

        case(0xDD):
            Display(6);
            break; //1101_1101

        case(0xBD):
            Display(5);
            break; //1011_1101

        case(0x7D):
            Display(4);
            break; //0111_1101

        case(0xEB):
            Display(11);
            break; //1110_1011

        case(0xDB):
            Display(10);
            break; //1101_1011

        case(0xBB):
            Display(9);
            break; //1011_1011

        case(0x7B):
            Display(8);
            break; //0111_1011

        case(0xE7):
            Display(15);
            break; //1110_0111

        case(0xD7):
            Display(14);
            break; //1101_0111

        case(0xB7):
            Display(13);
            break; //1011_0111

        case(0x77):
            Display(12);
            break; //0111_0111
    }
}

void main()
{

    while(1)
    {
        Keyscan();
    }
}