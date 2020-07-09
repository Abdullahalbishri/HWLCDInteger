/*
 * HWLCDInteger.c
 *
 * Created: 7/8/2020 1:09:29 AM
 * Author : Abdullah Saad Albishri
 * Course : Embedded System Diploma
 */ 

#include "LCD.h"


int main(void)
{
     LCD_Init();

	 LCD_WriteInteger(1234);

    while (1) 
    {
    }
}

