#include "usart.h"

//��Ҫ�ڻص���������1
uint8_t USART0_FLAG_SEND=0;		//����0������ɱ��
uint8_t USART1_FLAG_SEND=0;		//����1������ɱ��
uint8_t USART2_FLAG_SEND=0;		//����2������ɱ��

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
