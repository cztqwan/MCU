#ifndef __USART_H
#define __USART_H

#include "r_cg_macrodriver.h"

//��Ҫ�ڻص���������1
extern uint8_t USART0_FLAG_SEND;		//����0������ɱ��
extern uint8_t USART1_FLAG_SEND;		//����1������ɱ��
extern uint8_t USART2_FLAG_SEND;		//����2������ɱ��

void Wait_SendFinish0();	//�ȴ����ڷ�����ɺ���
void Wait_SendFinish1();	//�ȴ����ڷ�����ɺ���
void Wait_SendFinish2();	//�ȴ����ڷ�����ɺ���

#endif