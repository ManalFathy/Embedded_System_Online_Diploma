/*
 * UART.c
 *
 * Created: 1/10/2023 1:41:09 AM
 *  Author: MANAL
 */ 

 
 //Functions
 #include "UART.h"
#include "C:\Users\ayman\Documents\Atmel Studio\7.0\Lcd_Keypad_Drivers\Lcd_Keypad_Drivers\LCD_driver\lcd.h"
 
 static uint8_t* TX_str;
volatile static uint8_t* RX_str;
 static uint8_t flag_send =1;
  static uint8_t flag_Receive =1;
  
volatile  static uint8_t j=0;
  
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

void UART_Send_Str(uint8_t* str)
{
	uint8_t i ;
	for(i=0 ; i<str[i] ; i++) // str[i]=NULL SO if there is a space(null) it will end the loop so we use default stop to be checked in reciever
	{
		UART_Send(str[i]);
	}
	UART_Send(defaultStop); //used for receiver check
	
}

void UART_Receive_Str(uint8_t* Buff) //return pointer to buff but through the fun argument
{
	uint8_t i = 0 ;
	Buff[i] = UART_Recieve();
	while (Buff[i] != defaultStop)
	{
		i++;
		Buff[i] =UART_Recieve();
		
	}
	Buff[i] = '\0';

}


uint8_t UART_Recieve_PeriodicCheck (uint8_t* data)
{
	if(READ_BIT(UCSRA ,RXC))
	{
		*data =UDR;
		return 1;
	}
	return 0 ;
}

void UART_SendNoBlock(uint8_t data)
{
	UDR =data ;                          // add check
	
}
uint8_t UART_RecieveNoBlock(void)
{
	return UDR ;
	
}
void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
	
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
	
}
void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);	
}
void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
	
}

void UART_SendString_Asynch(uint8_t* str)
{
	if(flag_send ==1)               //to make sure that the function didn't handle another string
	{
		TX_str=str;
		flag_send =0;
		UART_TX_InterruptEnable();
		//UART_SendNoBlock(str[0]);
	//	TX_str=str;
		//flag_send =0;
	}
	
}
void __vector_15 (void) __attribute__((signal));
void __vector_15 (void)

//ISR(USART_TXC_vect)
{
	static uint8_t i=0;
	UART_SendNoBlock(TX_str[i]);
	if(TX_str[i] != '\0')
	{
		i++;
		
	}
	else
	{
		UART_TX_InterruptDisable();
		i=0;
		flag_send =1;
	}
}




void UART_ReceiveString_Asynch(uint8_t* str)
{
	
	//str[j] = UART_RecieveNoBlock();
	//j++;
	RX_str = str;
	UART_RX_InterruptEnable();
	
	
     
	
}

//void __vector_14 (void) __attribute__((signal));
//void __vector_14 (void)

ISR(USART_RXC_vect)
{
	RX_str[j] = UART_RecieveNoBlock();
	if(RX_str[j] != '\0')
	{
		j++;
		
	}
	else
	{
		RX_str[j] != '\0';		
		j=0;
		lcd_goto_xy(2,0);
		lcd_write_string(RX_str);
		//flag_Receive =1;
	}
}