/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#include "Stm32_F103C6_EXTI_driver.h"
#include"Stm32_F103C6_USART_driver.h"
#include "lcd.h"
#include "keypad.h"

 unsigned char ch ;
void clock_init()
{
RCC_GPIOA_CLK_EN();
RCC_AFIO_CLK_EN();
}

void M_UART_IRQ_Callback(void)
{
	  MCAL_UART_ReceiveData(USART1, &ch, disable);
	MCAL_UART_SendData(USART1, &ch, enable);
}

int main(void)
{
     UART_Config uartCFG ;

	clock_init();

	uartCFG.BaudRate = UART_BaudRate_115200;
	uartCFG.HwFlowCtl =UART_HwFlowCtl_NONE;
	uartCFG.Parity = UART_Parity_NONE;
	uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNEIE;
	uartCFG.P_IRQ_Callback = M_UART_IRQ_Callback;
	uartCFG.Payload_Length = UART_Payload_8B ;
	uartCFG.USART_Mode = UART_Mode_TX_RX;
	uartCFG.StopBits = UART_StopBits_1 ;

	MCAL_UART_INIT(USART1, &uartCFG);
	MCAL_UART_GPIO_Set_Pins(USART1) ;

   while(1)
   {


   }













	return 0;
}
