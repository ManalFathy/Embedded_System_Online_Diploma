/*
 * Lcd_Keypad_Drivers.c
 *
 * Created: 12/26/2022 3:39:57 PM
 * Author :Manal
 */ 

#include <avr/io.h>
#include "LCD_driver/lcd.h"
#include "KEYPAD_driver/keypad.h"

int main(void)
{
	LCD_INIT();
	_delay_ms(10);
	Keypad_init();
	LCD_custom_characters();
	char key_pressed;
	
        while (1) 
    {
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
    }
}

