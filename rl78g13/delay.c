#include "delay.h"

void delay_us(uint16_t us)
{
	uint16_t i,j;
	for(i=0;i<us;i++)
		for(j=0;j<2;j++);
}

void delay_ms(uint16_t ms)
{
	uint16_t i,j;
	for(i=0;i<ms;i++)
		for(j=0;j<3555;j++);
}