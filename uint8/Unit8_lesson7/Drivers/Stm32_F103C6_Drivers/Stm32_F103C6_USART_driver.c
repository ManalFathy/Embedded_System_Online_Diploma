/*
 * Stm32_F103C6_USART_driver.c
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#include "Stm32_F103C6_USART_driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */
UART_Config* Global_UART_Config = NULL ;//need to update cancel this global and pass the uart config to all functions


/*
 * ======================================================================
 *                                          Generic Macros
 *======================================================================
 */



/*
 * ======================================================================
 *                                          Generic Functions
 *======================================================================
 */





/*
 * ====================================================================================================
 *                          APIs Functions Definations
 * ====================================================================================================
 */


/**================================================================
 * @Fn               -MCAL_UART_INIT
 * @brief            -Initialize UART (Asynchronous Only)
 *param[in]         -USARTx :where x can be 1,2,3 depending on device used
 *param[in]           -UART config :all the uart configuration
 * @retval           -none
 * Note              -support for now ASynch mode and clock 8 HZ
 */


void MCAL_UART_INIT(USART_TypeDef * USARTx , UART_Config* UART_config)
{
	uint32_t pclk,BRR;
	Global_UART_Config = UART_config;

	//enable the clock for given USART Peripheral
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if (USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if (USARTx == USART3)
		RCC_USART3_CLK_EN();

	//enable UART Module
	USARTx->CR1 |= (1<<13) ; //Bit 13 UE: USART enable

	//enable Mode TX RX
	USARTx->CR1 |= UART_config->USART_Mode ;

	// enable Payload width
	USARTx->CR1 |= UART_config->Payload_Length ;

	//Configure parity bits
	USARTx->CR1 |= UART_config->Parity ;

	//configure stop bits
	USARTx->CR2 |= UART_config->StopBits;

	//flow control
	USARTx->CR3 |= UART_config->HwFlowCtl ;

	//Configure baud rate
	//PCLK2 For USART1
	//PCLK1 for USART2 ,3

	if(USARTx == USART1)
		pclk = MCAL_RCC_GetPCLK2Freq();
	else
		pclk = MCAL_RCC_GetPCLK1Freq();

	BRR = UART_BRR_Register(pclk ,UART_config->BaudRate ) ;

	USARTx->BRR =BRR ;

	//enable /diable interrupt
	if(UART_config->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		USARTx->CR1 |= UART_config->IRQ_Enable ;

		//enable NVIC for USART IRQ
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;
		else if (USARTx == USART2)
			NVIC_IRQ37_USART2_Enable;
		else if (USARTx == USART3)
			NVIC_IRQ37_USART3_Enable;

	}

}

/**================================================================
 * @Fn               -MCAL_UART_DeINIT
 * @brief            -DeInitialize UART (Asynchronous Only)
 *param[in]         -USARTx :where x can be 1,2,3 depending on device used
 * @retval           -none
 * Note              -Reset the model by RCC
 */

void MCAL_UART_DeINIT(USART_TypeDef * USARTx , UART_Config* UART_config)
{
	if(USARTx == USART1)
	{
		RCC_USART1_Reset();
		NVIC_IRQ37_USART1_Disable;
	}

	else if (USARTx == USART2)
	{
		RCC_USART2_Reset();
		NVIC_IRQ37_USART2_Disable;
	}

	else if (USARTx == USART3)
	{
		RCC_USART3_Reset();
		NVIC_IRQ37_USART3_Disable;
	}


}

/**================================================================
 * @Fn               - MCAL_UART_SendData
 * @brief            -send buffer on UART
 *param[in]         -USARTx :where x can be 1,2,3 depending on device used
 *param[in]         -pTxBuffer: the buffer that will be transmitted
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -should initialize UART firist
 */
void MCAL_UART_SendData(USART_TypeDef * USARTx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn)
{
	//wait until TXE is set
	if (PollingEn == enable)
		while(!(USARTx->SR & (1<<7))); //polling

	//check the data length
	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity->
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit->
	if(Global_UART_Config->Payload_Length == UART_Payload_9B)
	{
		USARTx->DR = (* pTxBuffer & (uint16_t)0x01FF);
	}
	else
	{
		USARTx->DR = (* pTxBuffer & (uint16_t)0xFF);
	}

}


void MCAL_UART_WAIT_TC(USART_TypeDef * USARTx )
{

	while(!(USARTx->SR & (1>>6)));
}


/**================================================================
 * @Fn               - MCAL_UART_ReceiveData
 * @brief            -receive buffer from UART
 *param[in]         -USARTx :where x can be 1,2,3 depending on device used
 *param[in]         -pTxBuffer: the recieved buffer
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -none
 */
void MCAL_UART_ReceiveData(USART_TypeDef * USARTx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn)
{

	//wait until RXNE is set
	if (PollingEn == enable)
		while(!(USARTx->SR & (1<<5))); //polling
	if(Global_UART_Config->Payload_Length == UART_Payload_9B)
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			//no parity so all 9bits are data
			*((uint16_t*)pTxBuffer) = USARTx->DR ;

		}else{
			//if parity is used so 8bit is data and the last one is parity
			*((uint16_t*)pTxBuffer) =( USARTx->DR & (uint8_t)0xFF);
		}


	}
	else //8 bit data
	{
		if(Global_UART_Config->Parity == UART_Parity_NONE)
		{
			//no parity so all 9bits are data
			*((uint16_t*)pTxBuffer) = (USARTx->DR   & (uint8_t)0xFF);

		}else{
			//if parity is used so 8bit is data and the last one is parity
			*((uint16_t*)pTxBuffer) =( USARTx->DR & (uint8_t)0x7F);
		}



	}

}


/**================================================================
 * @Fn               - MCAL_UART_GPIO_Set_Pins
 * @brief            -set the Gpio pins
 *param[in]         -USARTx :where x can be 1,2,3 depending on device used
 * @retval           -none
 * Note              -should enable the corresponding ALT &GPIO in RCC CLOCK AND called after MCAL_UART_INIT()
 */

void MCAL_UART_GPIO_Set_Pins (USART_TypeDef * USARTx)
{
	GPIO_PinConfig_t pincfg;
	if(USARTx == USART1)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		pincfg.GPIO_PinNumber = GPIO_PIN_9 ;
		pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
		pincfg.GPIO_output_speed = GPIO_output_speed_10M;
		MCAL_GPIO_Init(GPIOA, &pincfg) ;

		//PA10 RX
		pincfg.GPIO_PinNumber = GPIO_PIN_10 ;
		pincfg.GPIO_Mode = GPIO_Mode_AF_INPUT;
		MCAL_GPIO_Init(GPIOA, &pincfg) ;

		//PA11 CTS
		if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN_11 ;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

		}

		//PA12 RTS
		if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
			{
			pincfg.GPIO_PinNumber = GPIO_PIN_12 ;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			}

	}

	else if(USARTx == USART2)
		{
			//from alternative pin table for LQF and see recommended gpio pins configuration table
			//PA2 TX
			//PA3 RX
			//PA0 CTS
			//PA1 RTS

			//PA2 TX
			pincfg.GPIO_PinNumber = GPIO_PIN_2 ;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			//PA3 RX
			pincfg.GPIO_PinNumber = GPIO_PIN_3 ;
			pincfg.GPIO_Mode = GPIO_Mode_AF_INPUT;
			MCAL_GPIO_Init(GPIOA, &pincfg) ;

			//PA0 CTS
			if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
			{
				pincfg.GPIO_PinNumber = GPIO_PIN_0 ;
				pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &pincfg) ;

			}

			//PA1 RTS
			if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
				{
				pincfg.GPIO_PinNumber = GPIO_PIN_1 ;
				pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
				pincfg.GPIO_output_speed = GPIO_output_speed_10M;
				MCAL_GPIO_Init(GPIOA, &pincfg) ;

				}

		}

	else if(USARTx == USART3)
		{
			//from alternative pin table for LQF and see recommended gpio pins configuration table
			//PB10 TX
			//PB11 RX
			//PB13 CTS
			//PA14 RTS

			//PB10 TX
			pincfg.GPIO_PinNumber = GPIO_PIN_10 ;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

			//PB11 RX
			pincfg.GPIO_PinNumber = GPIO_PIN_11 ;
			pincfg.GPIO_Mode = GPIO_Mode_AF_INPUT;
			MCAL_GPIO_Init(GPIOB, &pincfg) ;

			//PA13 CTS
			if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
			{
				pincfg.GPIO_PinNumber = GPIO_PIN_13 ;
				pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &pincfg) ;

			}

			//PA12 RTS
			if(Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == UART_HwFlowCtl_RTS_CTS)
				{
				pincfg.GPIO_PinNumber = GPIO_PIN_14 ;
				pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
				pincfg.GPIO_output_speed = GPIO_output_speed_10M;
				MCAL_GPIO_Init(GPIOA, &pincfg) ;

				}

		}
}



//ISR
void USART1_IRQHandler(void)
{
	Global_UART_Config->P_IRQ_Callback();
}

void USART2_IRQHandler(void)
{
	Global_UART_Config->P_IRQ_Callback();
}

void USART3_IRQHandler(void)
{
	Global_UART_Config->P_IRQ_Callback();
}












