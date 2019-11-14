#ifndef _LCD_16x2_H_
#define _LCD_16x2_H_

#include "stm32f1xx_hal.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>

#include "delay.h"

#define CNT_GPIO	GPIOB
#define DAT_GPIO 	GPIOB

#define RS_PIN		GPIO_PIN_10
#define E_PIN		GPIO_PIN_11

#define RS(x)		(x) ? (CNT_GPIO->ODR |= RS_PIN) : (CNT_GPIO->ODR &= ~RS_PIN)
#define E(x)		(x) ? (CNT_GPIO->ODR |= E_PIN)  : (CNT_GPIO->ODR &= ~E_PIN)

#define LEFT		0
#define RIGHT		1

#define FIX_DELAY	0

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t x, uint8_t y);
void LCD_Cursor(uint8_t n);
void LCD_Scroll(uint8_t dir, uint8_t steps);
void LCD_PrintChar(char ch);
void LCD_PrintString(const char *str);
void LCD_PrintNum(uint8_t n);

#endif //_LCD_16x2_H_
