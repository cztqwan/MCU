#ifndef __MPUIIC_H
#define __MPUIIC_H

#include "r_cg_macrodriver.h"
 	   		   
//IO��������
#define MPU_SDA_IN()  {PM7=_00_PMn0_MODE_OUTPUT | _02_PMn1_MODE_INPUT | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;}
#define MPU_SDA_OUT() {PM7=_00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE | _20_PMn5_NOT_USE | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;}

//IO��������	 
#define MPU_IIC_SCL    P7.0	//SCL
#define MPU_IIC_SDA    P7.1	//SDA
#define MPU_READ_SDA   P7.1	//����SDA

//IIC���в�������
void MPU_IIC_Delay(void);//MPU IIC��ʱ����
void MPU_IIC_Init(void);//��ʼ��IIC��IO��
void MPU_IIC_Start(void);//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(uint8_t txd);//IIC����һ���ֽ�
uint8_t MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t MPU_IIC_Wait_Ack(void);//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);//IIC����ACK�ź�
void MPU_IIC_NAck(void);//IIC������ACK�ź�

//void IMPU_IC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
//uint8_t MPU_IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif