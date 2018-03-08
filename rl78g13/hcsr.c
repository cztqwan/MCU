#include "hcsr.h"
/*
需要把P0.1设置为out
Channel 0 中选择 Input pulse high-/low-level width measurement
channel 0 tab 中: TI00 low-/high-width range 选择: 0.5(us) < TI00 < 32.768(ms)
Measure level 选择: High-level
*/

double result[5] = {0,0,0,0,0};
double average_value = 0;
unsigned char index = 0U;
unsigned char stop = 0U;

/***********************************************************************************************************************
* Function Name: Start_Measure
* Description  : This function makes ultrasonic probe start. 
		 P0.1 is connected to the Trig port in ultrasonic probe.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void Start_Measure(void)
{
    int delay = 53;
    P0.1 = 1;
    while(delay--);
    P0.1 = 0;
}

/***********************************************************************************************************************
* Function Name: Get_Average
* Description  : This function gets average distance in five times measure.
* Arguments    : None
* Return Value : average distance
***********************************************************************************************************************/
double Get_Average(void)
{
    int index = 0;
    double distance = 0,average = 0;
    for (;index<5;index++)
    {
		distance += result[index];
    }
    average = distance/5;
    return average;
}

/***********************************************************************************************************************
* Function Name: Get_Distance
* Description  : This function is used to get the distance.
* Arguments    : Count_value is the timer count value.
* Return Value : the actual distance.
***********************************************************************************************************************/
double Get_Distance(uint32_t Count_value)
{
    double length;
    
    /******************************************************************************************************************
       Attention:
       * 4000000 is current timer's clock frequency, it is changed according to TPS and TMRmn register setting 
         in R_TAU0_Create function.
       * Because of current timer use channel 0, n=0 in TMRmn register. Refer to PRS bits in TPS and CKS bits 
	 in TMRmn register.
       * 340 is the speed of ultrasonic every second.
    *******************************************************************************************************************/
    length = (double)Count_value/4000000*340/2; 
    
    return length;
}