/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2013 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_timer_user.c
* Version      : CodeGenerator for RL78/G13 V2.00.00.07 [22 Feb 2013]
* Device(s)    : R5F100LE
* Tool-Chain   : CA78K0R
* Description  : This file implements device driver for TAU module.
* Creation Date: 2015/8/8
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
#pragma interrupt INTTM00 r_tau0_channel0_interrupt
#pragma interrupt INTTM04 r_tau0_channel4_interrupt
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* For TAU0_ch0 pulse measurement */
volatile uint32_t g_tau0_ch0_width = 0U;
/* For TAU0_ch4 pulse measurement */
volatile uint32_t g_tau0_ch4_width = 0U;
/* Start user code for global. Do not edit comment generated here */
uint8_t Bit_num=0;
uint8_t RmtSta=0;
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_tau0_channel0_interrupt
* Description  : This function is INTTM00 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel0_interrupt(void)
{
    if ((TSR00 & _0001_TAU_OVERFLOW_OCCURS) == 1U)    /* overflow occurs */
    {            
        g_tau0_ch0_width = (uint32_t)(TDR00 + 1U) + 0x10000U;
    }
    else
    {
        g_tau0_ch0_width = (uint32_t)(TDR00 + 1U);
    }

    /* Start user code. Do not edit comment generated here */
	result[index] = Get_Distance(g_tau0_ch0_width);
    index++;
    if(index>=5)
    {
		stop = 1;
    }
    Start_Measure();
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_tau0_channel4_interrupt
* Description  : This function is INTTM04 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
__interrupt static void r_tau0_channel4_interrupt(void)
{
    if ((TSR04 & _0001_TAU_OVERFLOW_OCCURS) == 1U)    /* overflow occurs */
    {            
        g_tau0_ch4_width = (uint32_t)(TDR04 + 1U) + 0x10000U;
    }
    else
    {
        g_tau0_ch4_width = (uint32_t)(TDR04 + 1U);
    }

    /* Start user code. Do not edit comment generated here */
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
	/* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
