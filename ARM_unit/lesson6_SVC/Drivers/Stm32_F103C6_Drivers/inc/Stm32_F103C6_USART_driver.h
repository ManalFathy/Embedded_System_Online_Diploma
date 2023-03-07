/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#ifndef INC_STM32_F103C6_USART_DRIVER_H_
#define INC_STM32_F103C6_USART_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_RCC_driver.h"


//-----------------------------
//User type definitions (structures)
//config structure
//-----------------------------
typedef struct
{
	uint8_t  					USART_Mode ; //Specifies TX/RX Enable/Disable
	                                         //This parameter must be set based on @ref UART_Mode_define

	uint32_t  					BaudRate ; //Specifies The communication Baud rate
	                                         //This parameter must be set based on @ref UART_BaudRate_define

	uint8_t  					Payload_Length ; //Specifies The number of data bits transmitted or received in the frame
	                                         //This parameter must be set based on @ref UART_Payload_define

	uint8_t  					Parity ; //Specifies The parity mode
	                                         //This parameter must be set based on @ref UART_Parity_define

	uint8_t  					StopBits ; //Specifies The number os stop bits transmitted
	                                         //This parameter must be set based on @ref UART_StopBits_define

	uint8_t  					HwFlowCtl ; //Specifies wheter the hardware flow control mode Enable/Disable
	                                         //This parameter must be set based on @ref UART_HwFlowCtl_define

	uint8_t  					IRQ_Enable ; //Specifies UART IRQ TX/RX Enable/Disable
	                                         //This parameter must be set based on @ref UART_IRQ_Enable_define

	void (*P_IRQ_Callback)(void) ;           // set the C Function() which will be called once the IRQ  Happen
}UART_Config;
//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref Module_REF_NAME_define

//@ref UART_Mode_define

#define UART_Mode_RX                     (uint32_t)(1<<2)//Bit 2 RE: Receiver enable
#define UART_Mode_TX                      (uint32_t)(1<<3)//Bit 3 TE: Transmitter enable
#define UART_Mode_TX_RX                   (uint32_t)(1<<2 | 1<<3)


//@ref UART_BaudRate_define

#define UART_BaudRate_2400                       2400
#define UART_BaudRate_9600                       9600
#define UART_BaudRate_19200                      19200
#define UART_BaudRate_57600                      57600
#define UART_BaudRate_115200                     115200
#define UART_BaudRate_230400                     230400
#define UART_BaudRate_460800                     460800
#define UART_BaudRate_921600                     921600
#define UART_BaudRate_2250000                    2250000
#define UART_BaudRate_4500000                    4500000

//@ref UART_Payload_define
#define UART_Payload_8B                         (uint32_t)(0)
#define UART_Payload_9B                         (uint32_t)(1<<12)

//@ref UART_Parity_define

#define UART_Parity_NONE                        (uint32_t)(0)
#define UART_Parity_EVEN                        (uint32_t)(1<<10)
#define UART_Parity_ODD                         (uint32_t)(1<<10 | 1<<9)

//@ref UART_StopBits_define

#define UART_StopBits_half                      (uint32_t)(1<<12)
#define UART_StopBits_1                          (uint32_t)(0)
#define UART_StopBits_1_half                      (uint32_t)(1<<12 | 1<<13)
#define UART_StopBits_2                           (uint32_t)(1<<13)


//@ref UART_HwFlowCtl_define

#define UART_HwFlowCtl_NONE                       (uint32_t)(0)
#define UART_HwFlowCtl_RTS                       (uint32_t)(1<<8)
#define UART_HwFlowCtl_CTS                       (uint32_t)(1<<9)
#define UART_HwFlowCtl_RTS_CTS                     (uint32_t)(1<<8 | 1<<9)

//@ref UART_IRQ_Enable_define

#define UART_IRQ_Enable_NONE                       (uint32_t)(0)
#define UART_IRQ_Enable_TXE                       (uint32_t)(1<<7)//transmit data register empty
#define UART_IRQ_Enable_TC                       (uint32_t)(1<<6) //Transmission complete interrupt enable
#define UART_IRQ_Enable_RXNEIE                     (uint32_t)(1<<5)//Recived data ready to read and overrun error detected
#define UART_IRQ_Enable_PE                          (uint32_t)(1<<8) //parity error





//Baudrate calculation
//USARTDIV = fclk /(16*Baudrate)
//USARTDIV_Mul100  = (uint32)(100*fclk)/(16*Baudrate)
//USARTDIV_Mul100  = (uint32)(25*fclk)/(4*Baudrate)
//DIV_Mantissa_MUL100 = Integar part (USARTDIV) *100
//DIV_Mantissa = Integar part (USARTDIV)
//DIV_Fraction = ((USARTDIV_Mul100 - DIV_Mantissa_MUL100 ) * 16 )/100)

#define USARTDIV(_PCLK_,_BAUD_)           (uint32_t)(_PCLK_/(16 * _BAUD_))
#define USARTDIV_Mul100(_PCLK_,_BAUD_)           (uint32_t)((25 * _PCLK_)/(4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_,_BAUD_)           (uint32_t) (USARTDIV(_PCLK_,_BAUD_) * 100)
#define Mantissa(_PCLK_,_BAUD_)                 (uint32_t) (USARTDIV(_PCLK_,_BAUD_))
#define DIV_Fraction(_PCLK_,_BAUD_)             (uint32_t) (( USARTDIV_Mul100(_PCLK_,_BAUD_)  - Mantissa_MUL100(_PCLK_,_BAUD_)) * 16 ) /100
#define UART_BRR_Register(_PCLK_,_BAUD_)        ( (Mantissa(_PCLK_,_BAUD_)) <<4 ) | ( (DIV_Fraction(_PCLK_,_BAUD_)) & 0xF)

/*
 * ====================================================================================================
 *                          APIs Supported by "MCAL USART DRIVER"
 * ====================================================================================================
 */

void MCAL_UART_INIT(USART_TypeDef * USARTx , UART_Config* UART_config) ;
void MCAL_UART_DeINIT(USART_TypeDef * USARTx , UART_Config* UART_config) ;

void MCAL_UART_GPIO_Set_Pins (USART_TypeDef * USARTx) ;

void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn) ;
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn) ;

void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx );

//to do
// void MCAL_USART_LIN_INIT() ;        //LIN
// void MCAL_USART_INIT() ;            //Synchrounous
// void MCAL_USART_DMA_INIT() ;         //Multibuffer communication


#endif /* INC_STM32_F103C6_USART_DRIVER_H_ */
