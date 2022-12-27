/*
 * lcd.c
 *
 * Created: 12/26/2022 3:43:23 PM
 *  Author: Manal 
 */ 
#include "lcd.h"

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}
void LCD_kick(){
	LCD_CTRL |= (1 << ENABLE_SWITCH);
	_delay_ms(50);
	LCD_CTRL &= ~(1 << ENABLE_SWITCH);
}

void LCD_check_lcd_isbusy(void)
{
	DataDIR_LCD_PORT &= ~(0xFF<<DATA_SHIFT); // data is input
	LCD_CTRL |=(1<<RW_SWITCH);//Read mode
	LCD_CTRL &= ~(1<<RS_SWITCH);//command off
	LCD_kick();
	DataDIR_LCD_PORT |=(0xFF<<DATA_SHIFT); 
	LCD_CTRL &= ~(1<<RW_SWITCH);
}

void LCD_INIT()
{
	_delay_ms(20);
	DataDIR_LCD_CTRL |= (1<<ENABLE_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	LCD_CTRL &= ~ (1<<ENABLE_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	DataDIR_LCD_PORT =0xFF; //data in output direction
	LCD_clear_screen();
	
	#ifdef EIGHT_BIT_MODE
	 LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	#endif
	
	#ifdef FOUR_BIT_MODE
	LCD_WRITE_COMMAND(0x02);
	LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);
	
}

void LCD_WRITE_COMMAND(unsigned char command){
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = command;
	LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	_delay_ms(1);
	LCD_kick();
	#endif
	#ifdef FOUR_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_kick ();
	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
	LCD_kick();
	#endif
}

void LCD_WRITE_CHAR(unsigned char character){
	#ifdef EIGHT_BIT_MODE
	LCD_check_lcd_isbusy();
	LCD_PORT = character;
	LCD_CTRL &= ~(1 << RW_SWITCH);
	LCD_CTRL |= (1 << RS_SWITCH);
	_delay_ms(1);
	LCD_kick();
	#endif
	#ifdef FOUR_BIT_MODE
	//LCD_check_lcd_isbusy();
	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
	LCD_kick();
	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
	LCD_kick ();
	#endif
}

void LCD_GOTO_XY(unsigned char line, unsigned char position){
	if (line == 1)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW+position);
		}
	}
	if (line == 2)
	{
		if (position < 16 && position >= 0)
		{
			LCD_WRITE_COMMAND(LCD_BEGIN_AT_SECOND_ROW+position);
		}
	}
}

void LCD_WRITE_STRING(char* string){
	int count = 0;
	while (*string > 0){
		count++;
		LCD_WRITE_CHAR(*string++);
		if (count == 16)
		{
			LCD_GOTO_XY(2,0);
		}
		else if (count == 32)
		{
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}
	}
} 

void LCD_custom_characters(void)
{
	LCD_WRITE_COMMAND(64);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(14);
	LCD_WRITE_CHAR(17);
	LCD_WRITE_CHAR(2);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_CHAR(0);
	LCD_WRITE_CHAR(4);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_CHAR(0);
	_delay_ms(10);
}