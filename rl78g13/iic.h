#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "r_cg_macrodriver.h"
 	   		   
//IO方向设置
#define MPU_SDA_IN()  {PM7=_00_PMn0_MODE_OUTPUT | _02_PMn1_MODE_INPUT | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;}
#define MPU_SDA_OUT() {PM7=_00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;}

//IO操作函数	 
#define MPU_IIC_SCL    P7.0	//SCL
#define MPU_IIC_SDA    P7.1	//SDA
#define MPU_READ_SDA   P7.1	//输入SDA

//IIC所有操作函数
void MPU_IIC_Delay(void);//MPU IIC延时函数
void MPU_IIC_Init(void);//初始化IIC的IO口
void MPU_IIC_Start(void);//发送IIC开始信号
void MPU_IIC_Stop(void);//发送IIC停止信号
void MPU_IIC_Send_Byte(uint8_t txd);//IIC发送一个字节
uint8_t MPU_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t MPU_IIC_Wait_Ack(void);//IIC等待ACK信号
void MPU_IIC_Ack(void);//IIC发送ACK信号
void MPU_IIC_NAck(void);//IIC不发送ACK信号

//void IMPU_IC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
//uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif