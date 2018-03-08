#include "LCD.h"

uint8_t bitdata;
_lcd_dev lcddev;//参数结构体

void LCD_Writ_Bus(uint8_t da)
{	
	uint8_t i;
	bitdata=da;
	for(i=0;i<8;i++)
	{
		if(bitdata&0x80)
			LCD_SDI=1;
		else
			LCD_SDI=0;
		LCD_SCK=0;
		LCD_SCK=1;
		bitdata<<=1;
	}
}

//发送数据 8位参数
void LCD_WR_DATA8(uint8_t da)
{
    LCD_DC=1;
    LCD_Writ_Bus(da);
}

//发送数据 16位参数
void LCD_WR_DATA16(uint16_t da)
{
    LCD_WR_DATA8(da>>8);
    LCD_WR_DATA8(da);
}

//write reg
void LCD_WR_REG(uint8_t da)	 
{
    LCD_DC=0;
    LCD_Writ_Bus(da);
}

//write data to reg
void LCD_WR_REG_DATA(uint8_t reg,uint16_t da)
{
    LCD_WR_REG(reg);
    LCD_WR_DATA16(da);
}

/**********************************
 * 函数名：Lcd_init_conf
 * 描述  ：ILI9341 LCD寄存器初始配置
 * 输入  : 无
 * 输出  ：无
 * 举例  ：无
 * 注意  ：无
*************************************/
void Lcd_init_conf(void)
{
	LCD_CS=1;   
	LCD_REST=0;
	delay_ms(50);
	LCD_REST=1;
	delay_ms(50);
	LCD_CS=0;  //打开片选使能
	
	LCD_WR_REG(0xCF);//功耗控制B
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x81);
	LCD_WR_DATA8(0x30);
	
	LCD_WR_REG(0xED);//电源序列控制
	LCD_WR_DATA8(0x64);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x81);
	
	LCD_WR_REG(0xE8);//驱动时序控制A
	LCD_WR_DATA8(0x85);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x78);
	
	LCD_WR_REG(0xCB);//功耗控制
	LCD_WR_DATA8(0x39);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x34);
	LCD_WR_DATA8(0x02);
	
	LCD_WR_REG(0xF7);
	LCD_WR_DATA8(0x20);
	
	LCD_WR_REG(0xEA);//驱动时序控制B
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	
	LCD_WR_REG(0xB1);//帧速率控制
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x1B);
	
	LCD_WR_REG(0xB6);//显示功能控制
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0xA2);
	
	LCD_WR_REG(0xC0);//功耗控制1
	LCD_WR_DATA8(0x35);
	
	LCD_WR_REG(0xC1);//功耗控制2 
	LCD_WR_DATA8(0x11);
	
	LCD_WR_REG(0xC5);//VCM control1
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x45);
	
	LCD_WR_REG(0xC7);//VCM control2
	LCD_WR_DATA8(0xA2);
	
	LCD_WR_REG(0xF2);//使能3G
	LCD_WR_DATA8(0x00);
	
	LCD_WR_REG(0x26);//伽玛设置
	LCD_WR_DATA8(0x01);
	
	LCD_WR_REG(0xE0);//正极伽码校准Set Gamma
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x26);
	LCD_WR_DATA8(0x24);
	LCD_WR_DATA8(0x0B);
	LCD_WR_DATA8(0x0E);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x54);
	LCD_WR_DATA8(0xA8);
	LCD_WR_DATA8(0x46);
	LCD_WR_DATA8(0x0C);
	LCD_WR_DATA8(0x17);
	LCD_WR_DATA8(0x09);
	LCD_WR_DATA8(0x0F);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x00);
	LCD_WR_REG(0XE1);//负极伽码校准Set Gamma
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x19);
	LCD_WR_DATA8(0x1B);
	LCD_WR_DATA8(0x04);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x07);
	LCD_WR_DATA8(0x2A);
	LCD_WR_DATA8(0x47);
	LCD_WR_DATA8(0x39);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x06);
	LCD_WR_DATA8(0x30);
	LCD_WR_DATA8(0x38);
	LCD_WR_DATA8(0x0F);
	
	LCD_WR_REG(0x36);//存储器访问控制 
	LCD_WR_DATA8(0x68);//横屏  左上角到(起点)到右下角(终点)扫描方式
	
	LCD_WR_REG(0X2A);//列地址设置 
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x3F);
	
	LCD_WR_REG(0X2B);//行地址设置 
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xEF);

	LCD_WR_REG(0x3A);//像素格式设置 
	LCD_WR_DATA8(0x55);
	
	LCD_WR_REG(0x11);//退出休眠
	
	delay_ms(100);//延时
	LCD_WR_REG(0x29);//显示
	LCD_WR_REG(0x2C);
	Set_direction(1);//传入1-->初始化默认为竖屏方式
}
/**********************************
 * 函数名：Set_direction
 * 描述  ：设置ILI9341GRAM指针扫描方向
 * 输入  ：	0：横向扫描
			1：纵向扫描
			2：横向扫描
			3：纵向扫描
 * 输出  ：无
 * 说明  ：
			高两位设置LED原点
			左上角00
			右上角01
			左下角10
			右下角11
			第五位：行列交换
			第四位：垂直刷新方向
			0:从上到下
			1:从下到上
			第二位：水平刷新方向
			0:从左到右
			1:从右到左
**********************************/
void Set_direction(uint8_t option)
{
    switch(option)
    {
		case 0:
		{	    
			//横屏,右上角-->左下角
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x6C);    //横屏
			LCD_WR_REG(0X2A); 			//列地址设置
			LCD_WR_DATA8(0x00);	//start:0x00-->0
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x01);	//end:0x13F-->319
			LCD_WR_DATA8(0x3F);
			
			LCD_WR_REG(0X2B);			//行地址设置
			LCD_WR_DATA8(0x00);   	//start:0x00-->0
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);  	//end:0xEF-->239
			LCD_WR_DATA8(0xEF);
			lcddev.width=360;
			lcddev.height=240;
			lcddev.direction=0;
		}break;
		case 1:
		{
			//竖屏，左上角到右下角
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x08);	//竖屏 
			LCD_WR_REG(0X2A); 
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0xEF);	
			
			LCD_WR_REG(0X2B); 
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x01);
			LCD_WR_DATA8(0x3F);
			lcddev.direction = 1;
			lcddev.width=240;
			lcddev.height=360;
		}break;
		case 2:
		{	    
			//横屏，左下角到右上角
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0xB8);    //横屏
			LCD_WR_REG(0X2A); 			//列地址设置
			LCD_WR_DATA8(0x00);	//start:0x00-->0
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x01);	//end:0x13F-->319
			LCD_WR_DATA8(0x3F);
			
			LCD_WR_REG(0X2B);			//行地址设置
			LCD_WR_DATA8(0x00);   	//start:0x00-->0
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);  	//end:0xEF-->239
			LCD_WR_DATA8(0xEF);
			lcddev.direction = 0;
			lcddev.width=360;
			lcddev.height=240;
		}break;
		case 3:
		{
			//竖屏,右下角到左上角
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0xDC);
			LCD_WR_REG(0X2A);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0xEF);
			
			LCD_WR_REG(0X2B);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x01);
			LCD_WR_DATA8(0x3F);
			lcddev.direction = 1;
			lcddev.width=240;
			lcddev.height=360;
		}break;
    }
}
void LCD_open_windows(uint16_t x,uint16_t y,uint16_t len,uint16_t wid)
{                    
	LCD_WR_REG(0X2A); 
	LCD_WR_DATA8(x>>8);
	LCD_WR_DATA8(x-((x>>8)<<8));
	LCD_WR_DATA8((x+len-1)>>8);
	LCD_WR_DATA8((x+len-1)-(((x+len-1)>>8)<<8));
	
	LCD_WR_REG(0X2B); 
	LCD_WR_DATA8(y>>8);			//start
	LCD_WR_DATA8(y-((y>>8)<<8));
	LCD_WR_DATA8((y+wid-1)>>8);	//end
	LCD_WR_DATA8((y+wid-1)-(((y+wid-1)>>8)<<8));
}
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(0x2C);
}
void LCD_Clear(uint16_t color)
{
	uint32_t index=0; 
	LCD_open_windows(0,0,240,320);
	LCD_WR_REG(0X2c); 
	for(index=0;index<76800;index++)
	{
		LCD_WR_DATA16(color);	   
	}
}
void LCD_Init(void)
{
    uint32_t i;
	lcddev.width=240;
	lcddev.height=360;
	LCD_LED=1;
	Lcd_init_conf();
    LCD_WriteRAM_Prepare();
	for(i=0;i<76800;i++)
	{
		LCD_WR_DATA16(WHITE);
	}
}
//设置光标位置
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 		    
	LCD_WR_REG(0x2A); //先高八位，后低八位
	LCD_WR_DATA8(Xpos>>8); 
	LCD_WR_DATA8(Xpos&0XFF);	 
	LCD_WR_REG(0x2B); 
	LCD_WR_DATA8(Ypos>>8); 
	LCD_WR_DATA8(Ypos&0XFF);
}
//画点
//x,y:坐标
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);		//设置光标位置 
	LCD_WriteRAM_Prepare();	//开始写入GRAM
	LCD_WR_DATA16(POINT_COLOR);
}
//在指定区域内填充单个颜色
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	xlen=ex-sx+1;
	for(i=sy;i<=ey;i++)
	{
	 	LCD_SetCursor(sx,i);//设置光标位置
		LCD_WriteRAM_Prepare();//开始写入GRAM
		for(j=0;j<xlen;j++)
			LCD_WR_DATA16(color);    
	}
}

//在指定区域内填充指定颜色块			 
//(sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex-sx+1)*(ey-sy+1)   
//color:要填充的颜色
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 		//得到填充的宽度
	height=ey-sy+1;		//高度
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//设置光标位置 
		LCD_WriteRAM_Prepare();     //开始写入GRAM
		for(j=0;j<width;j++)
			LCD_WR_DATA16(color[i*height+j]);//写入数据 
	}	  
}  
//画线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)
		incx=1; //设置单步方向 
	else if(delta_x==0)
		incx=0;//垂直线 
	else
	{
		incx=-1;
		delta_x=-delta_x;
	} 
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//水平线 
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 
	if(delta_x>delta_y)
		distance=delta_x; //选取基本增量坐标轴 
	else
		distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

