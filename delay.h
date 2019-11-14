/*
 * delay.h
 *
 *  Created on: Oct 10, 2019
 *      Author: Pirandella
 */

#ifndef _DELAY_H_
#define _DELAY_H_

#include "stm32f1xx_hal.h"

void delay_Init(void);
void delay_us(uint32_t us);

#endif /* _DELAY_H_ */
