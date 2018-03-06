#include "lcd_spi.h"
#include "font.h"
#include "systick.h"

uint8_t bitdata;
_lcd_dev lcddev;
uint16_t BACK_COLOR=WHITE;
uint16_t POINT_COLOR=RED;

/*******************************************
 * 函数名：LCD_GPIO_Config
 * 描述  ：根据FSMC配置LCD的I/O
 * 输入  : 无 
 * 输出  ：无
*********************************************/  
void LCD_GPIO_Config(void)
{    
	GPIO_InitTypeDef GPIO_InitStructure;

	//使能PORTB,D,E,G以及AFIO复用功能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;				 //PA1背光
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/****************************************************************************
* 名    称：LCD_Writ_Bus
* 功    能：STM32_模拟SPI写一个字节数据底层函数
****************************************************************************/
void LCD_Writ_Bus(uint8_t da)
{	
	uint8_t i;
	bitdata=da;
	for(i=0;i<8;i++)
	{
		if(bitdata&0x80)
			LCD_SDI_H;
		else
			LCD_SDI_L;
		LCD_SCK_L;
		LCD_SCK_H;
		bitdata<<=1;
	}
}

/****************************************************************************
* 名    称：LCD_WR_DATA8
* 功    能：向液晶屏写一个8位数据
****************************************************************************/
void LCD_WR_DATA8(uint8_t da)
{
	LCD_CS_L;
	LCD_DC_H;
	LCD_Writ_Bus(da);
	LCD_CS_H;
}

/****************************************************************************
* 名    称：LCD_WR_DATA16
* 功    能：向液晶屏写一个16位数据
****************************************************************************/
void LCD_WR_DATA16(uint16_t da)
{
    LCD_WR_DATA8(da>>8);
    LCD_WR_DATA8(da);
}

/****************************************************************************
* 名    称：LCD_WR_REG
* 功    能：向液晶屏写一个8位指令
* 入口参数：da   寄存器地址
****************************************************************************/
void LCD_WR_REG(uint8_t da)	 
{
	LCD_CS_L;
	LCD_DC_L;
	LCD_Writ_Bus(da);
	LCD_CS_H;
}

/****************************************************************************
* 名    称：void LCD_WriteReg(u8 Index,u16 Data)
* 功    能：写寄存器数据
****************************************************************************/
void LCD_WR_REG_DATA(uint8_t reg,uint16_t da)
{
    LCD_WR_REG(reg);
    LCD_WR_DATA16(da);
}

/****************************************************************************
* 名    称：LCD_Reset
* 功    能：液晶硬复位函数
* 说    明：液晶初始化前需执行一次复位操作
****************************************************************************/
void LCD_Reset(void)
{
	LCD_REST_L;
	Delay_ms(100);
	LCD_REST_H;
	Delay_ms(50);
}

/****************************************************************************
* 名    称：LCD_Init
* 功    能：液晶初始化函数
****************************************************************************/
void LCD_Init(void)
{
	lcddev.id=9341;lcddev.direction=1;
	lcddev.height=320;lcddev.width=240;
	LCD_GPIO_Config();			//IO口初始化
	LCD_Reset();				//复位
	Lcd_init_conf();
	//LCD_LED_H;				//背光
}

/**********************************
 * 函数名：Lcd_init_conf
 * 描述  ：ILI9341 LCD寄存器初始配置
*************************************/
void Lcd_init_conf(void)
{
	LCD_WR_REG(0xCB);  
	LCD_WR_DATA8(0x39); 
	LCD_WR_DATA8(0x2C); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x34); 
	LCD_WR_DATA8(0x02); 

	LCD_WR_REG(0xCF);  
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0XC1); 
	LCD_WR_DATA8(0X30); 

	LCD_WR_REG(0xE8);  
	LCD_WR_DATA8(0x85); 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x78); 

	LCD_WR_REG(0xEA);  
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x00); 

	LCD_WR_REG(0xED);  
	LCD_WR_DATA8(0x64); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0X12); 
	LCD_WR_DATA8(0X81); 

	LCD_WR_REG(0xF7);  
	LCD_WR_DATA8(0x20); 

	LCD_WR_REG(0xC0);    //Power control 
	LCD_WR_DATA8(0x23);   //VRH[5:0] 

	LCD_WR_REG(0xC1);    //Power control 
	LCD_WR_DATA8(0x10);   //SAP[2:0];BT[3:0] 

	LCD_WR_REG(0xC5);    //VCM control 
	LCD_WR_DATA8(0x3e); //对比度调节
	LCD_WR_DATA8(0x28); 

	LCD_WR_REG(0xC7);    //VCM control2 
	LCD_WR_DATA8(0x86);  //--

	LCD_WR_REG(0x36);    // Memory Access Control 

	LCD_WR_DATA8(0x48);  //48 68竖屏//28 E8 横屏

	LCD_WR_REG(0x3A);    
	LCD_WR_DATA8(0x55); 

	LCD_WR_REG(0xB1);    
	LCD_WR_DATA8(0x00);  
	LCD_WR_DATA8(0x18); 

	LCD_WR_REG(0xB6);    // Display Function Control 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x82);
	LCD_WR_DATA8(0x27);  

	LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
	LCD_WR_DATA8(0x00); 

	LCD_WR_REG(0x26);    //Gamma curve selected 
	LCD_WR_DATA8(0x01); 

	LCD_WR_REG(0xE0);    //Set Gamma 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x31); 
	LCD_WR_DATA8(0x2B); 
	LCD_WR_DATA8(0x0C); 
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x4E); 
	LCD_WR_DATA8(0xF1); 
	LCD_WR_DATA8(0x37); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x10); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x09); 
	LCD_WR_DATA8(0x00); 

	LCD_WR_REG(0XE1);    //Set Gamma 
	LCD_WR_DATA8(0x00); 
	LCD_WR_DATA8(0x0E); 
	LCD_WR_DATA8(0x14); 
	LCD_WR_DATA8(0x03); 
	LCD_WR_DATA8(0x11); 
	LCD_WR_DATA8(0x07); 
	LCD_WR_DATA8(0x31); 
	LCD_WR_DATA8(0xC1); 
	LCD_WR_DATA8(0x48); 
	LCD_WR_DATA8(0x08); 
	LCD_WR_DATA8(0x0F); 
	LCD_WR_DATA8(0x0C); 
	LCD_WR_DATA8(0x31); 
	LCD_WR_DATA8(0x36); 
	LCD_WR_DATA8(0x0F); 

	LCD_WR_REG(0x11);    //Exit Sleep 
	Delay_ms(120); 
		
	LCD_WR_REG(0x29);    //Display on 
	LCD_WR_REG(0x2c); 
}

/**********************************
 * 函数名：Set_direction
 * 描述  ：设置屏幕方向
*************************************/
void Set_direction(uint8_t dir)
{
    switch(dir)
    {
		case R2L_U2D:
		{	    
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x08);
			lcddev.width=240;
			lcddev.height=320;
			lcddev.direction=1;
		}break;
		case R2L_D2U:
		{
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x88);
			lcddev.width=240;
			lcddev.height=320;
			lcddev.direction=1;
		}break;
		case L2R_U2D:
		{	    
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x48);
			lcddev.width=240;
			lcddev.height=320;
			lcddev.direction=1;
		}break;
		case L2R_D2U:
		{	    
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0xc8);
			lcddev.width=240;
			lcddev.height=320;
			lcddev.direction=1;
		}break;
		case U2D_L2R:
		{
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x28);
			lcddev.width=320;
			lcddev.height=240;
			lcddev.direction=0;
		}break;
		case D2U_L2R://D2U_L2R
		{
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x68);
			lcddev.direction=0;
			lcddev.width=320;
			lcddev.height=240;
		}break;
		case U2D_R2L:
		{
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0xa8);
			lcddev.direction=0;
			lcddev.width=320;
			lcddev.height=240;
		}break;
		case D2U_R2L:
		{
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0xe8);
			lcddev.direction=0;
			lcddev.width=320;
			lcddev.height=240;
		}break;	 
    }
	LCD_WR_REG(0X2A); 
	LCD_WR_DATA8(0);
	LCD_WR_DATA8(0);
	LCD_WR_DATA8((lcddev.width-1)>>8);
	LCD_WR_DATA8((lcddev.width-1)&0XFF);
	LCD_WR_REG(0X2B); 
	LCD_WR_DATA8(0);
	LCD_WR_DATA8(0);
	LCD_WR_DATA8((lcddev.height-1)>>8);
	LCD_WR_DATA8((lcddev.height-1)&0XFF);
}

/**********************************
 * 函数名：LCD_Set_Window
 * 描述  ：开窗函数
*************************************/
void LCD_Set_Window(uint16_t x,uint16_t y,uint16_t len,uint16_t wid)
{                    
	LCD_WR_REG(0X2A); 
	LCD_WR_DATA8(x>>8);
	LCD_WR_DATA8(x-((x>>8)<<8));
	LCD_WR_DATA8(len>>8);
	LCD_WR_DATA8(len-((len>>8)<<8));
	
	LCD_WR_REG(0X2B); 
	LCD_WR_DATA8(y>>8);			//start
	LCD_WR_DATA8(y-((y>>8)<<8));
	LCD_WR_DATA8(wid>>8);	//end
	LCD_WR_DATA8(wid-((wid>>8)<<8));
}

//准备输入数据
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(0x2C);
}

//清屏
void LCD_Clear(uint16_t color)
{
	uint32_t index=0; 
	LCD_SetCursor(0,0);
	LCD_WriteRAM_Prepare();
	for(index=0;index<lcddev.height*lcddev.width;index++)
	{
		LCD_WR_DATA16(color);	   
	}
}

//设置坐标
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
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);		//设置光标位置 
	LCD_WriteRAM_Prepare();	//开始写入GRAM
	LCD_WR_DATA16(POINT_COLOR);
}

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

void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
	int a,b;
	int di;
	a=0;
	b=r;	  
	di=3-(r<<1);
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);
 		LCD_DrawPoint(x0+b,y0-a);
		LCD_DrawPoint(x0+b,y0+a);
		LCD_DrawPoint(x0+a,y0+b);
		LCD_DrawPoint(x0-a,y0+b);
 		LCD_DrawPoint(x0-b,y0+a);
		LCD_DrawPoint(x0-a,y0-b);
  		LCD_DrawPoint(x0-b,y0-a);
		a++;  
		if(di<0)
			di+=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
}

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
{  							  
    uint8_t temp,t1,t,size_2;
	uint16_t y0=y;
	uint16_t colortemp=POINT_COLOR;      			     
	//设置窗口		   
	num=num-' ';//得到偏移后的值
	if(size==12)
		size_2=12;
	else
		size_2=size*size/16;
	if(!mode) //非叠加方式
	{
	    for(t=0;t<size_2;t++)
	    {   
			if(size==12)
				temp=asc2_1206[num][t];
			else if(size==24)
				temp=asc2_2412[num][t];
			else if(size==32)
				temp=asc2_3216[num][t];
			else 
				temp=asc2_1608[num][t];
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				LCD_DrawPoint(x,y);	
				temp<<=1;
				y++;
				if(x>=lcddev.width){POINT_COLOR=colortemp;return;}
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}
					break;
				}
			}  	 
	    }    
	}else
	{
	    for(t=0;t<size_2;t++)
	    {   
			if(size==12)
				temp=asc2_1206[num][t];
			else if(size==24)
				temp=asc2_2412[num][t];
			else if(size==32)
				temp=asc2_3216[num][t];
			else 
				temp=asc2_1608[num][t];
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
				temp<<=1;
				y++;
				if(x>=lcddev.height){POINT_COLOR=colortemp;return;}
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){POINT_COLOR=colortemp;return;}
					break;
				}
			}  	 
	    }     
	}
	POINT_COLOR=colortemp;	    	   	 	  
}

uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)
		result*=m;    
	return result;
}

void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
}

void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
}
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{         
	uint8_t x0=x;
	uint8_t mode=1;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))
    {   
		
        if(x>=width)
		{
			x=x0;
			y=y+size;
		}
        if(y>=height)
		{
			break;
		}
        LCD_ShowChar(x,y,*p,size,mode);
        x+=size/2;
        p++;
    }  
}

uint16_t image_getcolor(uint8_t mode,uint8_t *str)
{
	uint16_t color;
	if(mode)
	{
		color=((uint16_t)*str++)<<8;
		color|=*str;
	}else
	{
		color=*str++;
		color|=((uint16_t)*str)<<8;
	}
	return color;	
}

void image_show(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint8_t scan,uint8_t *p)
{  
	uint32_t i;
	uint32_t len=0;
	if((scan&0x03)==0)
	{
		switch(scan>>6)
		{
			case 0:
				Set_direction(L2R_U2D);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xsta,ysta);
				break; 
			case 1:
				Set_direction(L2R_D2U);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xsta,yend);
				break; 
			case 2:
				Set_direction(R2L_U2D);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xend,ysta);
				break; 
			case 3:
				Set_direction(R2L_D2U);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xend,yend);
				break; 
		}
	}else
	{
		switch(scan>>6)
		{
			case 0:
				Set_direction(U2D_L2R);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xsta,ysta);
				break; 
			case 1:
				Set_direction(D2U_L2R);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xsta,yend);
				break; 
			case 2:
				Set_direction(U2D_R2L);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xend,ysta);
				break; 
			case 3:
				Set_direction(D2U_R2L);
				LCD_Set_Window(xsta,ysta,xend,yend);
				LCD_SetCursor(xend,yend);
				break; 
		}
	}
	LCD_WriteRAM_Prepare();
	len=(xend-xsta+1)*(yend-ysta+1);
	for(i=0;i<len;i++)
	{
		LCD_WR_DATA16(image_getcolor(scan&(1<<4),p));
		p+=2;
	}	    					  	    
} 
void image_display(uint16_t x,uint16_t y,uint8_t* imgx)
{
	HEADCOLOR *imginfo;
 	uint8_t ifosize=sizeof(HEADCOLOR);
	imginfo=(HEADCOLOR*)imgx;
 	image_show(x,y,x+imginfo->w-1,y+imginfo->h-1,imginfo->scan,imgx+ifosize);		
}


u8 * findHz_24(unsigned char *hz)  /* 在自定义汉字库在查找所要显示的汉字的位置 */ 
{
    unsigned int i=0;
    FNT_GB24 *ptGb24 = (FNT_GB24 *)GBHZ_24;
    
    while(ptGb24[i].Index[0] > 0x80) 
	{
        if ((*hz == ptGb24[i].Index[0]) && (*(hz+1) == ptGb24[i].Index[1])) //找到汉字的位置了
		{
			return ptGb24[i].Msk;
        }
        i++;
        if(i > (sizeof((FNT_GB24 *)GBHZ_24) / sizeof(FNT_GB24) - 1))  /* 搜索下标约束 */
        {
		    break;
        }
    }
    return 0;
}

u8 * findHz_32(unsigned char *hz)  /* 在自定义汉字库在查找所要显示的汉字的位置 */ 
{
    unsigned int i=0;
    FNT_GB32 *ptGb32 = (FNT_GB32 *)GBHZ_32;
    
    while(ptGb32[i].Index[0] > 0x80) 
	{
        if ((*hz == ptGb32[i].Index[0]) && (*(hz+1) == ptGb32[i].Index[1])) //找到汉字的位置了
		{
			return ptGb32[i].Msk;
        }
        i++;
        if(i > (sizeof((FNT_GB32 *)GBHZ_32) / sizeof(FNT_GB32) - 1))  /* 搜索下标约束 */
        {
		    break;
        }
    }
    return 0;
}

u8 * findHz_16(unsigned char *hz)  /* 在自定义汉字库在查找所要显示的汉字的位置 */ 
{
    unsigned int i=0;
    FNT_GB16 *ptGb16 = (FNT_GB16 *)GBHZ_16;
    
    while(ptGb16[i].Index[0] > 0x80) 
	{
        if ((*hz == ptGb16[i].Index[0]) && (*(hz+1) == ptGb16[i].Index[1])) //找到汉字的位置了
		{
			return ptGb16[i].Msk;
        }
        i++;
        if(i > (sizeof((FNT_GB16 *)GBHZ_16) / sizeof(FNT_GB16) - 1))  /* 搜索下标约束 */
        {
		    break;
        }
    }
    return 0;
}

u8 * findHz_12(unsigned char *hz)  /* 在自定义汉字库在查找所要显示的汉字的位置 */ 
{
    unsigned int i=0;
    FNT_GB12 *ptGb12 = (FNT_GB12 *)GBHZ_12;
    
    while(ptGb12[i].Index[0] > 0x80) 
	{
        if ((*hz == ptGb12[i].Index[0]) && (*(hz+1) == ptGb12[i].Index[1])) //找到汉字的位置了
		{
			return ptGb12[i].Msk;
        }
        i++;
        if(i > (sizeof((FNT_GB12 *)GBHZ_12) / sizeof(FNT_GB12) - 1))  /* 搜索下标约束 */
        {
		    break;
        }
    }
    return 0;
}

//显示一个指定大小的汉字
//x,y :汉字的坐标
//font:汉字 GBK 码
//size:字体大小
//mode:0,正常显示,1,叠加显示 
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{
	u8 temp,t,t1,size_2;
	u16 y0=y;
	u8 *dzk;	//点阵数据
	u16 tempcolor; 
	if(size==12)
		size_2=size*2;
	else
		size_2=size*size/8;
	switch(size)
	{
		case 12:
			dzk=findHz_12(font);/* 取得当前字模，半字对齐访问*/
			break;
		case 16:
			dzk=findHz_16(font);/* 取得当前字模，半字对齐访问*/
			break;
		case 24:
			dzk=findHz_24(font);/* 取得当前字模，半字对齐访问*/
			break;
		case 32:
			dzk=findHz_32(font);/* 取得当前字模，半字对齐访问*/
			break;
		default:return;//不支持的字体大小
	}
	if(mode==0)//正常显示
	{
		for(t=0;t<size_2;t++)
		{ 
			temp=dzk[t];	//得到点的数据
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)
					LCD_DrawPoint(x,y);
				else
				{
					tempcolor=POINT_COLOR;
					POINT_COLOR=BACK_COLOR;
					LCD_DrawPoint(x,y);
					POINT_COLOR=tempcolor;//还原
				}
				temp<<=1; 
				y++;
				if((y-y0)==size) 
				{
					y=y0;
					x++;
					break;
				}
			}
		}
	}else//叠加显示
	{
		for(t=0;t<size_2;t++)
		{ 
			temp=dzk[t];//得到 12 数据
			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)LCD_DrawPoint(x,y);
				temp<<=1; y++;
				if((y-y0)==size) { y=y0; x++; break; }
			}
		}
	}
}

//在指定位置开始显示一个字符串 
//支持自动换行
//(x,y):起始坐标
//width,height:区域
//str :字符串
//size :字体大小
//mode:0,非叠加方式;1,叠加方式 
void Show_Str(u16 x,u16 y,u16 width,u16 height,u8* str,u8 size,u8 mode)
{
	u16 x0=x;
	u16 y0=y;							  	  
    u8 bHz=0;     //字符或者中文  	    				    				  	  
    while(*str!=0)//数据未结束
    { 
        if(!bHz)
        {
	        if(*str>0x80)
				bHz=1;//中文 
	        else              //字符
	        {      
                if(x>(x0+width-size/2))//换行
				{				   
					y+=size;
					x=x0;	   
				}							    
		        if(y>(y0+height-size))break;//越界返回      
		        if(*str==13)//换行符号
		        {         
		            y+=size;
					x=x0;
		            str++; 
		        }  
		        else LCD_ShowChar(x,y,*str,size,mode);//有效部分写入 
				str++; 
		        x+=size/2; //字符,为全字的一半 
	        }
        }else//中文 
        {     
            bHz=0;//有汉字库    
            if(x>(x0+width-size))//换行
			{	    
				y+=size;
				x=x0;		  
			}
	        if(y>(y0+height-size))break;//越界返回  						     
	        Show_Font(x,y,str,size,mode); //显示这个汉字,空心显示 
	        str+=2; 
	        x+=size;//下一个汉字偏移	    
        }						 
    } 
}

