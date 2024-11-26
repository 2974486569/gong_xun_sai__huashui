#ifndef __DELAY_US_H__
#define __DELAY_US_H__
#define CPU_FREQUENCY_MHZ    167		// STM32时钟频率
#include "main.h"
#include "delay.h"
void SysTick_Delay_Us(uint32_t delay);

#endif
