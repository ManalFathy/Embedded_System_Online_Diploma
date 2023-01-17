/*
 * UART.h
 *
 * Created: 1/10/2023 1:42:15 AM
 *  Author: MANAL
 */ 


#ifndef UART_H_
#define UART_H_

#define F_CPU 1000000UL

#include<avr/io.h>
#include<util/delay.h>

#define defaultStop '\r' //enter

#define CLR_BIT(REG,BIT)   REG&= ~(1<<BIT)
#define SET_BIT(REG,BIT)   REG|=(1<<BIT) 
#define READ_BIT(REG,BIT)   (REG>>BIT)&1
//APIS
void UART_INIT(void);
void UART_Send(uint8_t data);
uint8_t UART_Recieve(void);
uint32_t UART_ReciveNUMBER32(void);
void UART_SendNUMBER32(uint32_t num);

void UART_Send_Str(uint8_t* str);
void UART_Receive_Str(uint8_t* Buff);
uint8_t UART_Recieve_PeriodicCheck (uint8_t* data);
void UART_SendNoBlock(uint8_t data);
uint8_t UART_RecieveNoBlock(void);
void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);
void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);
void UART_SendString_Asynch(uint8_t* str);
void UART_ReceiveString_Asynch(uint8_t* str);
#endif /* UART_H_ */