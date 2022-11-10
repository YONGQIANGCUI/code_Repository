#ifndef __OLED_0_96_DRIVER_H
#define __OLED_0_96_DRIVER_H

#include "stm32f1xx_hal.h"
#include "main.h"
#include "picture.h"
#include "api_delay.h"
#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	

extern void OLED_Init(void);
extern void OLED_Clear(void);
extern void OLED_ShowCHinese(uint8_t x,uint8_t y,uint8_t no);
#endif

