/*
 * IncFile1.h
 *
 * Created: 04/07/2020 10:43:12 ص
 *  Author: Ali
 */ 


#ifndef LCD_Cfg_H
#define LCD_Cfg_H


#include "DIO.h"

#define  LCD_MODE     4

#define  LCD_8BIT_CMND_PORT     DIO_PORTA
#define  LCD_8BIT_DATA_PORT     DIO_PORTA

#define  LCD_4BIT_CMND_PORT     DIO_PORTB
#define  LCD_4BIT_DATA_PORT     DIO_PORTA



#define  LCD_RS_PIN             1
#define  LCD_RW_PIN             2
#define  LCD_E_PIN              3


#define  LCD_D0_PIN             0
#define  LCD_D1_PIN             1
#define  LCD_D2_PIN             2
#define  LCD_D3_PIN             3
#define  LCD_D4_PIN             4
#define  LCD_D5_PIN             5
#define  LCD_D6_PIN             6
#define  LCD_D7_PIN             7





#endif /* INCFILE1_H_ */