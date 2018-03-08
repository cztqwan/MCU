#include "remote.h"
#include "r_cg_userdefine.h"
/*
Channel 4 中选择 Input pulse high-/low-level width measurement
channel 4 tab 中: TI00 low-/high-width range 选择: 0.5(us) < TI00 < 32.768(ms)
Measure level 选择: High-level
*/

/*
定时器文件中变量
uint8_t Bit_num=0;
uint8_t RmtSta=0;
定时器中断中的内容
	if(RmtSta==1)
	{
		if(g_tau0_ch4_width>1100&&g_tau0_ch4_width<3300)//560*4为标准值,560us
		{
			RmtRec<<=1;
			RmtRec|=0;
			Bit_num++;
		}else if(g_tau0_ch4_width>5500&&g_tau0_ch4_width<7300)//1680*4为标准值,1680us
		{
			RmtRec<<=1;
			RmtRec|=1;
			Bit_num++;
		}
		if(Bit_num>=32)
		{
			RmtFin=1;//标记已经完成一次按键的键值信息采集
			RmtSta=0;//清空引导码收到标记，等待下一次接收
			Bit_num=0;
		}
	}
	else if(g_tau0_ch4_width>16800&&g_tau0_ch4_width<18800)
	{
		RmtSta=1;
	}
*/

uint8_t RmtFin=0;	//红外接收完一次数据标记
uint32_t RmtRec=0;	//红外接收到的数据

//处理红外键盘
//返回值:
//	 0,没有任何按键按下
//其他,按下的按键键值.
uint8_t Remote_Scan(void)
{        
	uint8_t sta=0;       
    uint8_t t1,t2,t3;  
	if(RmtFin==1)//得到一个按键的所有信息了
	{ 
	    t1=RmtRec>>24;			//得到地址码
	    t2=(RmtRec>>16)&0xff;	//得到地址反码
 	    if((t1==(uint8_t)~t2)&&t1==REMOTE_ID)//检验遥控识别码(ID)及地址
	    {
	        t1=RmtRec>>8;
	        t2=RmtRec;
			t3=~t2;
	        if(t1==(uint8_t)~t2)
			{			
				sta=t1;//键值正确
				RmtFin=0;
			}
		}   
		if(sta==0)//按键数据错误/遥控已经没有按下
		{
		 	RmtFin=0;//清除接收到有效按键标识
		}
	}  
    return sta;
}

uint8_t Read_RemoteValue(void)
{
	uint8_t key_num=0,key_Value=0;
	key_num=Remote_Scan();
	if(key_num)
	{	 	  
		switch(key_num)
		{
			case 162:key_Value='P';		break;//POWER
			case 226:key_Value='M';		break;//MENU
			case 34: key_Value='T';		break;//TEST
			case 2:  key_Value='+';		break;
			case 194:key_Value='r';		break;//RETURN
			case 224:key_Value='<';		break;
			case 168:key_Value='@';		break;
			case 144:key_Value='>';		break;
			case 104:key_Value='0';		break;
			case 152:key_Value='-';		break;
			case 176:key_Value='C';		break;
			case 48:key_Value='1';		break;
			case 24:key_Value='2';		break;  
			case 122:key_Value='3';		break;
			case 16:key_Value='4';		break;				
			case 56:key_Value='5';		break;
			case 90:key_Value='6';		break;
			case 66:key_Value='7';		break;
			case 74:key_Value='8';		break;
			case 82:key_Value='9';		break; 
		}
	}
	return key_Value;
}


