/*
 * IncFile1.h
 *
 * Created: 04/07/2020 11:01:43 ص
 *  Author: Ali
 */ 


#ifndef LCD_H
#define LCD_H

#define F_CPU 16000000
#include "LCD_Cfg.h"
#include <util/delay.h>




void LCD_Init(void);

void LCD_WriteCommand(uint8 cmd);

void LCD_WriteChar(uint8 chr);

void LCD_WriteString(uint8* str);

void LCD_GoTo(uint8 row, uint8 col);

void LCD_Clear(void);

void LCD_WriteInteger( sint32 num);

#endif /* INCFILE1_H_ */