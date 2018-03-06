#ifndef __LCD_SPI_H
#define __LCD_SPI_H

#include "stm32f10x.h"

//***************************************************************
//LCD初始化底层宏定义
//***************************************************************
//IO连接
#define LCD_CS_L	GPIO_ResetBits(GPIOA, GPIO_Pin_1)	//片选
#define LCD_CS_H	GPIO_SetBits(GPIOA, GPIO_Pin_1)		//片选
#define LCD_REST_L	GPIO_ResetBits(GPIOA, GPIO_Pin_2)	//复位
#define LCD_REST_H	GPIO_SetBits(GPIOA, GPIO_Pin_2)		//复位
#define LCD_DC_L	GPIO_ResetBits(GPIOA, GPIO_Pin_3)	//数据/命令切换
#define LCD_DC_H	GPIO_SetBits(GPIOA, GPIO_Pin_3)		//数据/命令切换
#define LCD_SDI_L	GPIO_ResetBits(GPIOA, GPIO_Pin_4)	//数据
#define LCD_SDI_H	GPIO_SetBits(GPIOA, GPIO_Pin_4)		//数据
#define LCD_SCK_L	GPIO_ResetBits(GPIOA, GPIO_Pin_5)	//时钟
#define LCD_SCK_H	GPIO_SetBits(GPIOA, GPIO_Pin_5)		//时钟

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

#define L2R_U2D  0
#define L2R_D2U  1
#define R2L_U2D  2
#define R2L_D2U  3

#define U2D_L2R  4
#define U2D_R2L  5
#define D2U_L2R  6
#define D2U_R2L  7

typedef struct
{
	uint16_t id;
	uint16_t width;
	uint16_t height;
	uint8_t direction;
}_lcd_dev;

typedef struct _HEADCOLOR
{
   unsigned char scan;
   unsigned char gray;
   unsigned short w;
   unsigned short h;
   unsigned char is565;
   unsigned char rgb;
}HEADCOLOR; 

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
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);
uint32_t LCD_Pow(uint8_t m,uint8_t n);
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);


void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode);	//显示一个汉字，支持12,,16,24,32
void Show_Str(u16 x,u16 y,u16 width,u16 height,u8* str,u8 size,u8 mode);//显示一串字符，支持12,16,24,32

uint16_t image_getcolor(uint8_t mode,uint8_t *str);
void image_show(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint8_t scan,uint8_t *p);
void image_display(uint16_t x,uint16_t y,uint8_t * imgx);	

//LCD底层函数
void LCD_GPIO_Config(void);
void LCD_Reset(void);
void Lcd_init_conf(void);
void LCD_WriteRAM_Prepare(void);
void Set_direction(uint8_t dir);
void LCD_Set_Window(uint16_t x,uint16_t y,uint16_t len,uint16_t wid);

#endif

