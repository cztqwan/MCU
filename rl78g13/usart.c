#include "usart.h"

//需要在回调函数里置1
uint8_t USART0_FLAG_SEND=0;		//串口0发送完成标记
uint8_t USART1_FLAG_SEND=0;		//串口1发送完成标记
uint8_t USART2_FLAG_SEND=0;		//串口2发送完成标记

void Wait_SendFinish0()
{
	while(USART0_FLAG_SEND==0);
	USART0_FLAG_SEND=0;	
}

void Wait_SendFinish1()
{
	while(USART1_FLAG_SEND==0);
	USART1_FLAG_SEND=0;	
}

void Wait_SendFinish2()
{
	while(USART2_FLAG_SEND==0);
	USART2_FLAG_SEND=0;	
}
