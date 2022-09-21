#include "uart.h"
#define UART0DR *((volatile unsigned int *const)((unsigned int *)0x101f1000))//to put avalue on this register

void Uart_Send_String(unsigned char * p_tx_string)  //function take a pointer to string 
{
	while(*p_tx_string != '\0')      //send the string char by char to register
	{
		UART0DR = (unsigned int)(*p_tx_string);
		p_tx_string ++;
	}
}