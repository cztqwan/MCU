#include "LCD.h"

uint8_t bitdata;
_lcd_dev lcddev;//�����ṹ��

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

//�������� 8λ����
void LCD_WR_DATA8(uint8_t da)
{
    LCD_DC=1;
    LCD_Writ_Bus(da);
}

//�������� 16λ����
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
 * ��������Lcd_init_conf
 * ����  ��ILI9341 LCD�Ĵ�����ʼ����
 * ����  : ��
 * ���  ����
 * ����  ����
 * ע��  ����
*************************************/
void Lcd_init_conf(void)
{
	LCD_CS=1;   
	LCD_REST=0;
	delay_ms(50);
	LCD_REST=1;
	delay_ms(50);
	LCD_CS=0;  //��Ƭѡʹ��
	
	LCD_WR_REG(0xCF);//���Ŀ���B
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x81);
	LCD_WR_DATA8(0x30);
	
	LCD_WR_REG(0xED);//��Դ���п���
	LCD_WR_DATA8(0x64);
	LCD_WR_DATA8(0x03);
	LCD_WR_DATA8(0x12);
	LCD_WR_DATA8(0x81);
	
	LCD_WR_REG(0xE8);//����ʱ�����A
	LCD_WR_DATA8(0x85);
	LCD_WR_DATA8(0x10);
	LCD_WR_DATA8(0x78);
	
	LCD_WR_REG(0xCB);//���Ŀ���
	LCD_WR_DATA8(0x39);
	LCD_WR_DATA8(0x2C);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x34);
	LCD_WR_DATA8(0x02);
	
	LCD_WR_REG(0xF7);
	LCD_WR_DATA8(0x20);
	
	LCD_WR_REG(0xEA);//����ʱ�����B
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	
	LCD_WR_REG(0xB1);//֡���ʿ���
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x1B);
	
	LCD_WR_REG(0xB6);//��ʾ���ܿ���
	LCD_WR_DATA8(0x0A);
	LCD_WR_DATA8(0xA2);
	
	LCD_WR_REG(0xC0);//���Ŀ���1
	LCD_WR_DATA8(0x35);
	
	LCD_WR_REG(0xC1);//���Ŀ���2 
	LCD_WR_DATA8(0x11);
	
	LCD_WR_REG(0xC5);//VCM control1
	LCD_WR_DATA8(0x45);
	LCD_WR_DATA8(0x45);
	
	LCD_WR_REG(0xC7);//VCM control2
	LCD_WR_DATA8(0xA2);
	
	LCD_WR_REG(0xF2);//ʹ��3G
	LCD_WR_DATA8(0x00);
	
	LCD_WR_REG(0x26);//٤������
	LCD_WR_DATA8(0x01);
	
	LCD_WR_REG(0xE0);//����٤��У׼Set Gamma
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
	LCD_WR_REG(0XE1);//����٤��У׼Set Gamma
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
	
	LCD_WR_REG(0x36);//�洢�����ʿ��� 
	LCD_WR_DATA8(0x68);//����  ���Ͻǵ�(���)�����½�(�յ�)ɨ�跽ʽ
	
	LCD_WR_REG(0X2A);//�е�ַ���� 
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x01);
	LCD_WR_DATA8(0x3F);
	
	LCD_WR_REG(0X2B);//�е�ַ���� 
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0x00);
	LCD_WR_DATA8(0xEF);

	LCD_WR_REG(0x3A);//���ظ�ʽ���� 
	LCD_WR_DATA8(0x55);
	
	LCD_WR_REG(0x11);//�˳�����
	
	delay_ms(100);//��ʱ
	LCD_WR_REG(0x29);//��ʾ
	LCD_WR_REG(0x2C);
	Set_direction(1);//����1-->��ʼ��Ĭ��Ϊ������ʽ
}
/**********************************
 * ��������Set_direction
 * ����  ������ILI9341GRAMָ��ɨ�跽��
 * ����  ��	0������ɨ��
			1������ɨ��
			2������ɨ��
			3������ɨ��
 * ���  ����
 * ˵��  ��
			����λ����LEDԭ��
			���Ͻ�00
			���Ͻ�01
			���½�10
			���½�11
			����λ�����н���
			����λ����ֱˢ�·���
			0:���ϵ���
			1:���µ���
			�ڶ�λ��ˮƽˢ�·���
			0:������
			1:���ҵ���
**********************************/
void Set_direction(uint8_t option)
{
    switch(option)
    {
		case 0:
		{	    
			//����,���Ͻ�-->���½�
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x6C);    //����
			LCD_WR_REG(0X2A); 			//�е�ַ����
			LCD_WR_DATA8(0x00);	//start:0x00-->0
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x01);	//end:0x13F-->319
			LCD_WR_DATA8(0x3F);
			
			LCD_WR_REG(0X2B);			//�е�ַ����
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
			//���������Ͻǵ����½�
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0x08);	//���� 
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
			//���������½ǵ����Ͻ�
			LCD_WR_REG(0x36); 
			LCD_WR_DATA8(0xB8);    //����
			LCD_WR_REG(0X2A); 			//�е�ַ����
			LCD_WR_DATA8(0x00);	//start:0x00-->0
			LCD_WR_DATA8(0x00);
			LCD_WR_DATA8(0x01);	//end:0x13F-->319
			LCD_WR_DATA8(0x3F);
			
			LCD_WR_REG(0X2B);			//�е�ַ����
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
			//����,���½ǵ����Ͻ�
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
//���ù��λ��
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 		    
	LCD_WR_REG(0x2A); //�ȸ߰�λ����Ͱ�λ
	LCD_WR_DATA8(Xpos>>8); 
	LCD_WR_DATA8(Xpos&0XFF);	 
	LCD_WR_REG(0x2B); 
	LCD_WR_DATA8(Ypos>>8); 
	LCD_WR_DATA8(Ypos&0XFF);
}
//����
//x,y:����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);		//���ù��λ�� 
	LCD_WriteRAM_Prepare();	//��ʼд��GRAM
	LCD_WR_DATA16(POINT_COLOR);
}
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	xlen=ex-sx+1;
	for(i=sy;i<=ey;i++)
	{
	 	LCD_SetCursor(sx,i);//���ù��λ��
		LCD_WriteRAM_Prepare();//��ʼд��GRAM
		for(j=0;j<xlen;j++)
			LCD_WR_DATA16(color);    
	}
}

//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 		//�õ����Ŀ��
	height=ey-sy+1;		//�߶�
 	for(i=0;i<height;i++)
	{
 		LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)
			LCD_WR_DATA16(color[i*height+j]);//д������ 
	}	  
}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)
		incx=1; //���õ������� 
	else if(delta_x==0)
		incx=0;//��ֱ�� 
	else
	{
		incx=-1;
		delta_x=-delta_x;
	} 
	if(delta_y>0)
		incy=1; 
	else if(delta_y==0)
		incy=0;//ˮƽ�� 
	else
	{
		incy=-1;
		delta_y=-delta_y;
	} 
	if(delta_x>delta_y)
		distance=delta_x; //ѡȡ�������������� 
	else
		distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
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

