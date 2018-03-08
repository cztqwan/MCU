#ifndef __HCSR_H
#define __HCSR_H

#include "r_cg_macrodriver.h"

extern double result[5];
extern double average_value;
extern unsigned char index;
extern unsigned char stop;

void Start_Measure(void);
double Get_Average(void);
double Get_Distance(uint32_t Count_value);

#endif