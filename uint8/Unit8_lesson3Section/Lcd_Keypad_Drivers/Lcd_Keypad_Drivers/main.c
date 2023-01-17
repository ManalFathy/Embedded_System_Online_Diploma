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
#include <avr/interrupt.h>

char n[10]={ '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' ,'8' , '9' } ;
int main(void)
{
	
	sei();
	uint8_t x,z,i =0;
	uint8_t*  y;
uint8_t str[10];
lcd_init();
UART_INIT();
lcd_goto_xy(1,0);
lcd_write_string("UART TX");
UART_Send_Str("MANAL");

UART_SendString_Asynch("Ahmed ");
//UART_ReceiveString_Asynch(str);
while (1)
{
	
/////////////////////////////////////blocking mode
	
	/*lcd_goto_xy(1,0);
	lcd_write_char(n[i]);
		i++;
		if(i==10)
	    i=0;
		_delay_ms(1000);
		
		lcd_goto_xy(2,0);
		 UART_Receive_Str(str);
		 lcd_write_string(str);
		 _delay_ms(100);*/
	
	/////////////////////////////////////periodic check
//this may use data lose if user send multiple data and cpu didn't read it overrun error 
	/*	if(UART_Recieve_PeriodicCheck(&y))
		{
			lcd_goto_xy(2,0);
			lcd_write_char(y);
		}
		lcd_goto_xy(1,0);
		lcd_write_char(n[i]);
		i++;
		if(i==10)
		i=0;
		_delay_ms(100);*/
		
		//////////////////////////////////////////ASYNCHROUNUS
		//need to update to be asynchronous
	//	lcd_goto_xy(2,0);
	//	UART_Receive_Str(str);
	//	lcd_write_string(str);
		
		lcd_goto_xy(1,0);
		lcd_write_char(n[i]);
		i++;
		if(i==10)
		i=0;
		_delay_ms(100);
		
}
}