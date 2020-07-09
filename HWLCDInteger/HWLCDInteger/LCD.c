/*
 * CFile1.c
 *
 * Created: 04/07/2020 11:00:44 ص
 *  Author: Ali
 */ 

#include "LCD.h"



void LCD_Init(void)
{
	
	#if LCD_MODE == 8
	
	DIO_SetPinDir(LCD_8BIT_CMND_PORT ,LCD_RS_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_8BIT_CMND_PORT ,LCD_RW_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(LCD_8BIT_CMND_PORT ,LCD_E_PIN , DIO_PIN_OUTPUT);
	
	DIO_SetPortDir(LCD_8BIT_DATA_PORT , DIO_PIN_OUTPUT);
	
	_delay_ms(100);
	
	
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0E);
	LCD_WriteCommand(0x01);
	
	_delay_ms(20);
	
	LCD_WriteCommand(0x06);
	
	_delay_ms(5);
	
	
	
	#elif LCD_MODE == 4
	
	DIO_SetPinDir(DIO_PORTB ,LCD_RS_PIN , DIO_PIN_OUTPUT);// before it was PORTB
	DIO_SetPinDir(DIO_PORTB ,LCD_RW_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTB ,LCD_E_PIN ,  DIO_PIN_OUTPUT);
	
	DIO_SetPinDir(DIO_PORTA ,LCD_D4_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTA ,LCD_D5_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTA ,LCD_D6_PIN , DIO_PIN_OUTPUT);
	DIO_SetPinDir(DIO_PORTA ,LCD_D7_PIN , DIO_PIN_OUTPUT);
	
	_delay_ms(100);
	
	
	LCD_WriteCommand(0x33);
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);
	
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x01);
	
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x02);
	
	_delay_ms(5);
	
	
	
	#endif
}

void LCD_WriteCommand(uint8 cmd)
{
	
	#if LCD_MODE == 8
	
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_RW_PIN, DIO_PIN_LOW);
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_RS_PIN, DIO_PIN_LOW);
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_E_PIN, DIO_PIN_LOW);
	
	DIO_WritePort(LCD_8BIT_DATA_PORT , cmd);
	
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	#elif LCD_MODE == 4  
	
	DIO_WritePin( DIO_PORTB ,LCD_RW_PIN, DIO_PIN_LOW);
	DIO_WritePin( DIO_PORTB ,LCD_RS_PIN, DIO_PIN_LOW);
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_LOW);
	
	
	PORTA = (cmd & 0xF0);
	
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_LOW);
	
	PORTA = (cmd << 4);
		
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	
	#endif
	
}

void LCD_WriteChar(uint8 chr)
{
	
	#if LCD_MODE == 8
	
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_RW_PIN, DIO_PIN_LOW);
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_RS_PIN, DIO_PIN_HIGH);
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_E_PIN, DIO_PIN_LOW);
	
	DIO_WritePort(LCD_8BIT_DATA_PORT , chr);
	
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_WritePin( LCD_8BIT_CMND_PORT ,LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);

	#elif LCD_MODE == 4   

	DIO_WritePin( DIO_PORTB,LCD_RW_PIN, DIO_PIN_LOW);
	DIO_WritePin( DIO_PORTB ,LCD_RS_PIN, DIO_PIN_HIGH);
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_LOW);
	
	
	PORTA = (chr & 0xF0);
	
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_LOW);
	
	PORTA = (chr << 4);
	
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_WritePin( DIO_PORTB ,LCD_E_PIN, DIO_PIN_LOW);
	
	_delay_ms(5);
	
	
	#endif
}

void LCD_WriteString(uint8* str)
{
	uint8 i = 0;
	
	while(str[i] != '\0')
	{
		LCD_WriteChar(str[i]);
		i++;
	}
}

void LCD_GoTo(uint8 row, uint8 col)
{
	uint8 pos[2] = {0x80 , 0xC0};
		
	LCD_WriteCommand(pos[row]+col);
}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);
}

void LCD_WriteInteger( sint32 num)
{

 signed long x =0 ,y=0, ic=0;//Max 6 Password Numbers
 long i=1000000;

    if(num<0)
	{
	  LCD_WriteChar('-');
	  x=-1*num;
	}
	else if(num>1)
	{
	  x=num;
	}
	else if(num == 0)
	{
	LCD_WriteChar(48);
	return;
	}

    for( ;i>=1;i/=10)
       {
	      y=x/i;
	      if(y<0)continue;
	      else if(y>0)break;
       }


    for(;i>=1;i/=10)
       {
	      y=x/i;
	      y*=i;
	     ic=y/i;

	  switch (ic)//to char
	         {
		          case 0:
		          LCD_WriteChar(48);
		          break;
		          case 1:
		          LCD_WriteChar(49);
		          break;
		          case 2:
		          LCD_WriteChar(50);
		          break;
		          case 3:
	           	  LCD_WriteChar(51);
		          break;
			  	  case 4:
		          LCD_WriteChar(52);
		          break;
		          case 5:
		          LCD_WriteChar(53);
		          break;
		          case 6:
		          LCD_WriteChar(54);
		          break;
		          case 7:
		          LCD_WriteChar(55);
		          break;
		          case 8:
		          LCD_WriteChar(56);
		          break;
		          case 9:
		          LCD_WriteChar(57);
		          break;
		          default:
		          break;
	         }
	       x-=y;
        }
}