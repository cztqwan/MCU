#include "key_juzhen.h"
#include "delay.h"

//P1.0-P1.3 ����Ϊ���״̬
//P1.4-P1.7 ����Ϊ����״̬����ʹ���ڲ�������
//ʹ�ô˺�������ʱ����־���,�Գ���û��Ӱ��
//P1.0(46)-->H1
//P1.1(45)-->H2
//P1.2(44)-->H3
//P1.3(43)-->H4
//P1.4(42)-->L1
//P1.5(41)-->L2
//P1.6(40)-->L3
//P1.7(39)-->L4

//ȡ�ð��µļ�ֵ��1~F��,10�á�0����ʾ
uint8_t Get_KeyValue()
{
	unsigned char temp;
	uint8_t key_value=0;
	uint8_t i,j;
	P1=0xff;
	P1.0=0; /*P1.0�����*/
	temp=P1;
	temp=temp&0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100); /*ȥ������������ �ɸ��ݲ�ͬҪ�������ʱ*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*�����P1.0�����ӵ�4�������Ƿ��а��´���*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return '1'; /*����1*/
				break;
				case 0xd0:
					return '2'; /*����2*/
				break;
				case 0xb0:
					return '3'; /*����3*/
				break;
				case 0x70:
					return '4'; /*����4*/
				break;
			}
		}		
	}
	P1=0xff;
	P1.1=0; /*P1.1�����*/
	temp=P1;
	temp=temp & 0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100);/*ȥ������������ �ɸ��ݲ�ͬҪ�������ʱ*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*�����P1.1�����ӵ�4�������Ƿ��а��´���*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return '5'; /*����5*/
				break;
				case 0xd0:
					return '6'; /*����6*/
				break;
				case 0xb0:
					return '7'; /*����7*/
				break;
				case 0x70:
					return '8'; /*����8*/
				break;
			}
		}
	}
	P1=0xff;
	P1.2=0; /* P1.2�����*/
	temp=P1;
	temp=temp & 0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100); /*ȥ������������ �ɸ��ݲ�ͬҪ�������ʱ*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*�����P1.2�����ӵ�4�������Ƿ��а��´���*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return '9'; /*����9*/
				break;
				case 0xd0:
					return '0'; /*����0*/
				break;
				case 0xb0:
					return 'A'; /*����A*/
				break;
				case 0x70:
					return 'B'; /*����B*/
				break;
			}
		}
	}
	P1=0xff;
	P1.3=0; /* P1.3�����*/
	temp=P1;
	temp=temp & 0xf0;
	if (temp!=0xf0)
	{
		delay_ms(100); /*ȥ������������ �ɸ��ݲ�ͬҪ�������ʱ*/
		temp=P1;
		temp=temp & 0xf0;
		if (temp!=0xf0) /*�����P1.3�����ӵ�4�������Ƿ��а��´���*/
		{
			temp=P1;
			temp=temp & 0xf0;
			switch(temp)
			{
				case 0xe0:
					return 'C'; /*����C*/
				break;
				case 0xd0:
					return 'D'; /*����D*/
				break;
				case 0xb0:
					return 'E'; /*����E*/
				break;
				case 0x70:
					return 'F'; /*����F*/
				break;
			}
		}
	}
	return 0;
}