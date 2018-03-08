#include "key_juzhen.h"
#include "delay.h"

//P1.0-P1.3 设置为输出状态
//P1.4-P1.7 设置为输入状态并且使用内部上拉。
//使用此函数编译时会出现警告,对程序没有影响
//P1.0(46)-->H1
//P1.1(45)-->H2
//P1.2(44)-->H3
//P1.3(43)-->H4
//P1.4(42)-->L1
//P1.5(41)-->L2
//P1.6(40)-->L3
//P1.7(39)-->L4

//取得按下的键值‘1~F’,10用‘0’表示
uint8_t Get_KeyValue()
{
	unsigned char temp;
	uint8_t key_value=0;
	uint8_t i,j;
	P1=0xff;
	P1.0=0; /*P1.0输出低*/
	temp=P1;
	temp=temp&0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100); /*去除按键抖动， 可根据不同要求调整延时*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*检测与P1.0相连接的4个按键是否有按下触发*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return '1'; /*按键1*/
				break;
				case 0xd0:
					return '2'; /*按键2*/
				break;
				case 0xb0:
					return '3'; /*按键3*/
				break;
				case 0x70:
					return '4'; /*按键4*/
				break;
			}
		}		
	}
	P1=0xff;
	P1.1=0; /*P1.1输出低*/
	temp=P1;
	temp=temp & 0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100);/*去除按键抖动， 可根据不同要求调整延时*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*检测与P1.1相连接的4个按键是否有按下触发*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return '5'; /*按键5*/
				break;
				case 0xd0:
					return '6'; /*按键6*/
				break;
				case 0xb0:
					return '7'; /*按键7*/
				break;
				case 0x70:
					return '8'; /*按键8*/
				break;
			}
		}
	}
	P1=0xff;
	P1.2=0; /* P1.2输出低*/
	temp=P1;
	temp=temp & 0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100); /*去除按键抖动， 可根据不同要求调整延时*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*检测与P1.2相连接的4个按键是否有按下触发*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return '9'; /*按键9*/
				break;
				case 0xd0:
					return '0'; /*按键0*/
				break;
				case 0xb0:
					return 'A'; /*按键A*/
				break;
				case 0x70:
					return 'B'; /*按键B*/
				break;
			}
		}
	}
	P1=0xff;
	P1.3=0; /* P1.3输出低*/
	temp=P1;
	temp=temp & 0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100); /*去除按键抖动， 可根据不同要求调整延时*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*检测与P1.3相连接的4个按键是否有按下触发*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return 'C'; /*按键C*/
				break;
				case 0xd0:
					return 'D'; /*按键D*/
				break;
				case 0xb0:
					return 'E'; /*按键E*/
				break;
				case 0x70:
					return 'F'; /*按键F*/
				break;
			}
		}
	}
	return 0;
}