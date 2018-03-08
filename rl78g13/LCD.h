#ifndef __LCD_H
#define __LCD_H

#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

//***************************************************************
//LCD��ʼ���ײ�궨��
//***************************************************************
//IO����
#define LCD_LED		P5.0	//����33  56
#define LCD_CS		P5.1	//Ƭѡ34  55
#define LCD_REST	P5.2	//��λ35  54
#define LCD_DC		P5.3	//����/�����л�36  53
#define LCD_SDI		P5.4	//����37  52
#define LCD_SCK		P5.5	//ʱ��38  51

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ

//GUI��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

typedef struct
{
	uint16_t width;
	uint16_t height;
	uint8_t direction;
}_lcd_dev;

extern uint16_t POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern uint16_t BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

//LCD�ϲ㺯��

void LCD_Init(void);//��ʼ��
void LCD_Clear(uint16_t color);	//����
void LCD_DisplayOn(void);		//����ʾ
void LCD_DisplayOff(void);		//����ʾ
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);	//���ù��λ��
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);//������
void LCD_DrawPoint(uint16_t x,uint16_t y);//��ָ���ĵط�����

//LCD�ײ㺯��
void Lcd_init_conf(void);
void LCD_WriteRAM_Prepare(void);
void Set_direction(uint8_t option);
void LCD_open_windows(uint16_t x,uint16_t y,uint16_t len,uint16_t wid);

#endif