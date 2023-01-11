/*
 * UART.c
 *
 * Created: 1/10/2023 1:41:09 AM
 *  Author: MANAL
 */ 
 
 //Functions
 #include "UART.h"
 void UART_INIT(void)
 {
	  //baudrate
	  UBRRL = 51 ;
	  //normal mode
	  CLR_BIT(UCSRA,U2X);
	
	
	 //frame
	 //no parity by default
	 //8 bit data by default
	 
	 //enable  
	 SET_BIT(UCSRB,TXEN);
	 SET_BIT(UCSRB,RXEN);
 }
 void UART_Send(uint8_t data)
 {
	 while (! READ_BIT(UCSRA,UDRE));
	 UDR = data;
	 
 }
 uint8_t UART_Recieve(void)
 {
	  while (! READ_BIT(UCSRA,RXC));
	return  UDR ;
	 
 }

void UART_SendNUMBER32(uint32_t num)
{
	/*
	UART_Send((uint8_t)num);
	UART_Send((uint8_t)(num>>8));
	UART_Send((uint8_t)(num>>16));
	UART_Send((uint8_t)(num>>24));
	*/
	uint8_t* p =&num ;
	UART_Send(p[0]);
	UART_Send(p[1]);
	UART_Send(p[2]);
	UART_Send(p[3]);
}



uint32_t UART_ReciveNUMBER32(void)
{
	/*
	uint8_t b1 = UART_Recieve();
	uint8_t b2 = UART_Recieve();
	uint8_t b3 = UART_Recieve();
	uint8_t b4 = UART_Recieve();
	uint32_t num = (uint32_t)b1|(uint32_t)(b2<<8) | (uint32_t)(b3<<16) | (uint32_t)(b4<<24);
	
	*/
	uint32_t num ;
	uint8_t* p =&num ;
	
	p[0] = UART_Recieve();
	p[1] = UART_Recieve();
	p[2] = UART_Recieve();
	p[3] = UART_Recieve();
	
	return num ; 
}