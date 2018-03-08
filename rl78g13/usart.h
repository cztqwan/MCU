#ifndef __USART_H
#define __USART_H

#include "r_cg_macrodriver.h"

//需要在回调函数里置1
extern uint8_t USART0_FLAG_SEND;		//串口0发送完成标记
extern uint8_t USART1_FLAG_SEND;		//串口1发送完成标记
extern uint8_t USART2_FLAG_SEND;		//串口2发送完成标记

void Wait_SendFinish0();	//等待串口发送完成函数
void Wait_SendFinish1();	//等待串口发送完成函数
void Wait_SendFinish2();	//等待串口发送完成函数

#endif