/*
 * lcd.c
 *
 * Created: 12/26/2022 3:43:23 PM
 *  Author: Manal 
 */ 
#include "../../HAL/includes/lcd.h"

void _delay_ms(int x)
{
	unsigned int i,j;
	for(i=0 ; i<x ; i++);
	for(j=0 ;j<255 ; j++);
}

void LCD_clear_screen(){
	LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
}
void LCD_kick(){
	//LCD_CTRL |= (1 << ENABLE_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_SET) ;
	_delay_ms(50);
//	LCD_CTRL &= ~(1 << ENABLE_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_RESET) ;
}

void LCD_check_lcd_isbusy(void)
{

	//DataDIR_LCD_PORT &= ~(0xFF<<DATA_SHIFT); // data is input
	pinconfig.GPIO_PinNumber = GPIO_PIN_0;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

		pinconfig.GPIO_PinNumber = GPIO_PIN_1;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

		pinconfig.GPIO_PinNumber = GPIO_PIN_2;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

		pinconfig.GPIO_PinNumber = GPIO_PIN_3;
		pinconfig.GPIO_Mode =GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

		pinconfig.GPIO_PinNumber = GPIO_PIN_4;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

		pinconfig.GPIO_PinNumber = GPIO_PIN_5;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);
		LCD_clear_screen();

		pinconfig.GPIO_PinNumber = GPIO_PIN_6;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

		pinconfig.GPIO_PinNumber = GPIO_PIN_7;
		pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
		MCAL_GPIO_Init(LCD_CTRL, &pinconfig);



	//LCD_CTRL |=(1<<RW_SWITCH);//Read mode
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_SET) ;

	//LCD_CTRL &= ~(1<<RS_SWITCH);//command off
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET) ;

	LCD_kick();

	//DataDIR_LCD_PORT |=(0xFF<<DATA_SHIFT);
	//LCD_CTRL &= ~(1<<RW_SWITCH); //write
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET) ;
}

void LCD_INIT()
{
	_delay_ms(20);
	//	DataDIR_LCD_CTRL |= (1<<ENABLE_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);
	//	LCD_CTRL &= ~ (1<<ENABLE_SWITCH | 1<<RS_SWITCH | 1<<RW_SWITCH);


	// ENABLE_SWITCH , RS_SWITCH ,RW_SWITCH  input HighZ floating input
	pinconfig.GPIO_PinNumber = ENABLE_SWITCH;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = RS_SWITCH;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = RW_SWITCH;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);


	//DataDIR_LCD_PORT =0xFF;data in output direction
	_delay_ms(15);
	//data pins output with speed 10MHZ

	pinconfig.GPIO_PinNumber = GPIO_PIN_0;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN_1;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN_2;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN_3;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN_4;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN_5;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);
	LCD_clear_screen();

	pinconfig.GPIO_PinNumber = GPIO_PIN_6;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	pinconfig.GPIO_PinNumber = GPIO_PIN_7;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(LCD_CTRL, &pinconfig);

	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(LCD_CTRL, ENABLE_SWITCH, GPIO_PIN_RESET);
	_delay_ms(15);
	LCD_clear_screen();
	//#ifdef EIGHT_BIT_MODE
	LCD_WRITE_COMMAND(LCD_FUNCTION_8BIT_2LINES);
	//#endif

	//#ifdef FOUR_BIT_MODE
	//LCD_WRITE_COMMAND(0x02);
	//LCD_WRITE_COMMAND(LCD_FUNCTION_4BIT_2LINES);
	//#endif
	LCD_WRITE_COMMAND(LCD_ENTRY_MODE);
	LCD_WRITE_COMMAND(LCD_BEGIN_AT_FIRST_ROW);
	LCD_WRITE_COMMAND(LCD_DISP_ON_CURSOR_BLINK);

}

void LCD_WRITE_COMMAND(unsigned char command){
//#ifdef EIGHT_BIT_MODE
	//LCD_check_lcd_isbusy();
	//LCD_PORT = command;
	MCAL_GPIO_WritePORT(LCD_CTRL, command) ;

	//LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_RESET) ;
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET) ;

	_delay_ms(1);
	LCD_kick();
//#endif
//#ifdef FOUR_BIT_MODE
//	LCD_check_lcd_isbusy();
//	LCD_PORT = (LCD_PORT & 0x0F) | (command & 0xF0);
//	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//	LCD_kick ();
//	LCD_PORT = (LCD_PORT & 0x0F) | (command << 4);
//	LCD_CTRL &= ~ ((1<<RW_SWITCH)|(1<<RS_SWITCH));
//	LCD_kick();
//#endif
}

void LCD_WRITE_CHAR(unsigned char character){
//#ifdef EIGHT_BIT_MODE
	//LCD_check_lcd_isbusy();
	//LCD_PORT = character;
	MCAL_GPIO_WritePORT(LCD_CTRL, character) ;

	//LCD_CTRL &= ~(1 << RW_SWITCH);
	//LCD_CTRL |= (1 << RS_SWITCH);
	MCAL_GPIO_WritePin(LCD_CTRL, RS_SWITCH, GPIO_PIN_SET) ;
	MCAL_GPIO_WritePin(LCD_CTRL, RW_SWITCH, GPIO_PIN_RESET) ;

	_delay_ms(1);
	LCD_kick();
//#endif
//#ifdef FOUR_BIT_MODE
//	//LCD_check_lcd_isbusy();
//	LCD_PORT = (LCD_PORT & 0x0F) | (character & 0xF0);
//	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
//	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
//	LCD_kick();
//	LCD_PORT = (LCD_PORT & 0x0F) | (character << 4);
//	LCD_CTRL |= 1<<RS_SWITCH; //turn RS ON for Data mode.
//	LCD_CTRL &= ~ (1<<RW_SWITCH);//turn RW off so you can write.
//	LCD_kick ();
//#endif
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
