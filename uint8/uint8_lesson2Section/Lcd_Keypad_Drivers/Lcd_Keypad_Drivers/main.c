/*
 * Lcd_Keypad_Drivers.c
 *
 * Created: 12/26/2022 3:39:57 PM
 * Author :Manal
 */ 

#include <avr/io.h>
#include "LCD_driver/lcd.h"
//#include "KEYPAD_driver/keypad.h"
#include "MCAL/UART.h"
int main(void)
{
	uint8_t x;
	LCD_INIT();
	//_delay_ms(10);
	//Keypad_init();
	UART_INIT();
	LCD_GOTO_XY(0,0);
	LCD_WRITE_STRING("UART TR");
	UART_Send('M');
	UART_Send('A');
	UART_Send('N');
	UART_Send('A');
	UART_Send('L');
	UART_SendNUMBER32(300);
	
	//char key_pressed;
	
        while (1) 
    {
		//LCD_GOTO_XY(2,0);
		x=UART_Recieve();
		LCD_WRITE_CHAR(x);
		uint32_t y ;
		y=UART_ReciveNUMBER32();
		LCD_WRITE_CHAR(y);
		/*
		key_pressed = Keypad_getkey();
		switch(key_pressed){
			case 'A':
			break;
			case '?':
			LCD_clear_screen();
			break;
			default:
			LCD_WRITE_CHAR(key_pressed);
			break;
		}
			*/
		}
		return 0 ;
    }


