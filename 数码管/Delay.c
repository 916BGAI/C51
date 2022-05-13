#include "Delay.h"

void Delay(unsigned int x)		//@11.0592MHz
{
	unsigned char i, j;
	for(x; x--; x>0)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
	
}