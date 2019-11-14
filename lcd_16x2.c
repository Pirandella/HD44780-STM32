#include "lcd_16x2.h"

//static void LCD_Delay(int us);
static void LCD_WriteCmd(uint8_t byte);
static void LCD_WriteDat(uint8_t byte);
static void LCD_Write(uint8_t data);

void LCD_Init(void){

	delay_Init();
	// LCD initialization sequence
	E(0);
	LCD_WriteCmd(0x33);
	LCD_WriteCmd(0x32);
	LCD_WriteCmd(0x28);
	LCD_WriteCmd(0x0C);
	LCD_WriteCmd(0x01);
	LCD_WriteCmd(0x06);

}

void LCD_Clear(void){
	LCD_WriteCmd(0x01);
}

void LCD_SetCursor(uint8_t x, uint8_t y){
	uint8_t pos[2] = {0x80, 0xC0};
	LCD_WriteCmd(pos[y] + x);
}

void LCD_Cursor(uint8_t n){
	LCD_WriteCmd(0x18);
}

void LCD_Scroll(uint8_t dir, uint8_t steps){
	uint8_t i;

	if(steps > 0){
		if(dir){
			for(i = 0; i < steps; i++){
				LCD_WriteCmd(0x1C);
#if FIX_DELAY
				HAL_Delay(250);
#endif
			}
		}else{
			for(i = 0; i < steps; i++){
				LCD_WriteCmd(0x18);
#if FIX_DELAY
				HAL_Delay(250);
#endif
			}
		}
	}
}

void LCD_PrintChar(char ch){
	LCD_WriteDat(ch);
}

void LCD_PrintString(const char *str){
	while(*str != '\0'){
		if(*str != '\n') LCD_WriteDat(*str++);
	}
}

void LCD_PrintNum(uint8_t n){
	if(n / 100){
		LCD_WriteDat((n / 100) + 0x30);
		LCD_WriteDat((n / 10 % 10) + 0x30);
	}else{
		if((n / 10 % 10)) LCD_WriteDat((n / 10 % 10) + 0x30);
	}
	LCD_WriteDat((n % 10) + 0x30);
}

static void LCD_WriteCmd(uint8_t byte){
	RS(0);
	LCD_Write(byte >> 4);
	LCD_Write(byte & 0x0F);
}

static void LCD_WriteDat(uint8_t byte){
	RS(1);
	LCD_Write(byte >> 4);
	LCD_Write(byte & 0x0F);
}

static void LCD_Write(uint8_t data){
	DAT_GPIO->ODR &= ~(0xF000);
	DAT_GPIO->ODR |= data << 12;

	E(1);
	delay_us(460);
	E(0);
}
