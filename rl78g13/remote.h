#ifndef __RED_H
#define __RED_H

#include "r_cg_macrodriver.h"

//红外遥控识别码(ID),每款遥控器的该值基本都不一样,但也有一样的.
//我们选用的遥控器识别码为0
#define REMOTE_ID 0 
#define RDATA P0.3	 //红外数据输入脚（使用定时器2时）

extern uint8_t RmtFin;
extern uint32_t RmtRec;	//红外接收到的数据

uint8_t Remote_Scan(void);
uint8_t Read_RemoteValue(void);

#endif