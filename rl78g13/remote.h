#ifndef __RED_H
#define __RED_H

#include "r_cg_macrodriver.h"

//����ң��ʶ����(ID),ÿ��ң�����ĸ�ֵ��������һ��,��Ҳ��һ����.
//����ѡ�õ�ң����ʶ����Ϊ0
#define REMOTE_ID 0 
#define RDATA P0.3	 //������������ţ�ʹ�ö�ʱ��2ʱ��

extern uint8_t RmtFin;
extern uint32_t RmtRec;	//������յ�������

uint8_t Remote_Scan(void);
uint8_t Read_RemoteValue(void);

#endif