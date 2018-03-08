#ifndef __LCD_H
#define __LCD_H

#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"

//***************************************************************
//LCD初始化底层宏定义
//***************************************************************
//IO连接
#define LCD_LED		P5.0	//背光33  56
#define LCD_CS		P5.1	//片选34  55
#define LCD_REST	P5.2	//复位35  54
#define LCD_DC		P5.3	//数据/命令切换36  53
#define LCD_SDI		P5.4	//数据37  52
#define LCD_SCK		P5.5	//时钟38  51

//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色

//GUI颜色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
//#define LIGHTGRAY        0XEF5B //浅灰色(PANNEL)
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

typedef struct
{
	uint16_t width;
	uint16_t height;
	uint8_t direction;
}_lcd_dev;

extern uint16_t POINT_COLOR;//默认红色    
extern uint16_t BACK_COLOR; //背景颜色.默认为白色

//LCD上层函数

void LCD_Init(void);//初始化
void LCD_Clear(uint16_t color);	//清屏
void LCD_DisplayOn(void);		//开显示
void LCD_DisplayOff(void);		//关显示
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);	//设置光标位置
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);//填充矩形
void LCD_DrawPoint(uint16_t x,uint16_t y);//在指定的地方画点

//LCD底层函数
void Lcd_init_conf(void);
void LCD_WriteRAM_Prepare(void);
void Set_direction(uint8_t option);
void LCD_open_windows(uint16_t x,uint16_t y,uint16_t len,uint16_t wid);

#endif