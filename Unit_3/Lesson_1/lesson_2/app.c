#include "uart.h"
unsigned char string_buffer[20] = "learn_in_depth:Manal";

void main (void)
{
	 Uart_Send_String(string_buffer);
}