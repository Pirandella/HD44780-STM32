/*
 * delay.c
 *
 *  Created on: Oct 10, 2019
 *      Author: Pirandella
 */

#include "delay.h"

uint32_t DWT_Scale;

void delay_Init(void){
	DWT_Scale = (HAL_RCC_GetHCLKFreq() / 1000000);
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL = ENABLE;
}

void delay_us(uint32_t us){
	uint32_t DWT_Startwert = DWT->CYCCNT;
	uint32_t ticks = (us * DWT_Scale) - 20;
	while ((DWT->CYCCNT - DWT_Startwert) < ticks);
}
