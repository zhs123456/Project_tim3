#include "delay.h"

void delay_ms(u16 ms)
{
	u16 j;
	u32 i;
	for(j=0;j<ms;j++)
	{
		for(i=0;i<7200;i++);
	}
}



void delay_s(u8 s)
{
	u8 j;
	u32 i;
	for(j=0;j<s;j++)
	{
		for(i=0;i<7200000;i++);
	}
}





