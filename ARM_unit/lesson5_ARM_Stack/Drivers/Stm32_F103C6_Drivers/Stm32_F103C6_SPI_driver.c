/*
 * Stm32_F103C6_SPI_driver.c
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#include "Stm32_F103C6_SPI_driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */

SPI_Config* Global_SPI_Config[2] = {NULL , NULL} ;
SPI_Config  Global_SPI_Config1;
SPI_Config  Global_SPI_Config2;
/*
 * ======================================================================
 *                                          Generic Macros
 *======================================================================
 */
#define SPI1_Index                                  0
#define SPI2_Index                                   1


#define SPI_SR_TXE                                ((uint8_t)0x02)  // transmit buffer empty bit2
#define SPI_SR_RXNE                                ((uint8_t)0x01)  // receive buffer not empty bit1
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
 * @Fn               -MCAL_SPI_INIT
 * @brief            -Initialize SPI according to the specified parameters
 *param[in]         -SPIx :where x can be 1,2 depending on device used
 *param[in]           -SPI confg :all the SPI configuration
 * @retval           -none
 * Note              -support for SPI Full duplex Master and slave only
 */

void MCAL_SPI_INIT(SPI_TypeDef * SPIx , SPI_Config* SPI_confg)
{
	//safty for Registers
	uint16_t tempreg_CR1 =0 ;
	uint16_t tempreg_CR2 =0 ;

	if(SPIx ==SPI1)
	{
	   Global_SPI_Config1 = *SPI_confg;
		Global_SPI_Config[SPI1_Index] = & Global_SPI_Config1 ;
		RCC_SPI1_CLK_EN();

	}else if(SPIx ==SPI2)
	{
		  Global_SPI_Config2 = *SPI_confg;
		Global_SPI_Config[SPI2_Index] = &Global_SPI_Config2 ;
		RCC_SPI2_CLK_EN();
	}

	//Enable SPI CR1:Bit6 SPE
	tempreg_CR1 = (0x1U <<6);

	//Master 0r slave
	tempreg_CR1 |= SPI_confg->Device_Mode;

	//SPI Communication mode
	tempreg_CR1 |= SPI_confg->Communication_Mode;

	//SPI Frame format
	tempreg_CR1 |= SPI_confg->frame_format;

	//SPI Data size
	tempreg_CR1 |= SPI_confg->Data_Size;

	//SPI CLOCK POLARITY
	tempreg_CR1 |= SPI_confg->CLKPolarity;

	//SPI CLOCK PHASE
	tempreg_CR1 |= SPI_confg->CLKPhase;

	//===================================NSS=================
	if(SPI_confg->NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tempreg_CR2 |= SPI_confg->NSS;
	}
	else if (SPI_confg->NSS == SPI_NSS_Hard_Master_SS_output_disable)
	{
		tempreg_CR2 &= SPI_confg->NSS;

	}
	else
	{
		tempreg_CR1 |= SPI_confg->NSS;
	}

	//baud rate
	tempreg_CR1 |= SPI_confg->SPI_BAUDRATEPrescaler;

	//IRQ
	if(SPI_confg ->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		tempreg_CR2 |= SPI_confg->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable ;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable ;
		}
	}


	SPIx->CR1 = tempreg_CR1 ;
	SPIx->CR2 = tempreg_CR2 ;

}

/**================================================================
 * @Fn               -MCAL_SPI_DeINIT
 * @brief            -DeInitialize SPI
 *param[in]         -SPIx :where x can be 1,2 depending on device used
 *param[in]           -SPI confg :all the SPI configuration
 * @retval           -none
 * Note              -Reset the model by RCC
 */
void MCAL_SPI_DeINIT(SPI_TypeDef * SPIx , SPI_Config* SPI_confg)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}
}

/**================================================================
 * @Fn               - MCAL_SPI_SendData
 * @brief            -send buffer on SPI
 *param[in]         -SPIx :where x can be 1,2 depending on device used
 *param[in]         -pTxBuffer: the buffer that will be transmitted
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -should initialize SPI firist
 *                    - this sendData function is implemented for Full Duplex SPI only
 *                    - But if you want it for all modes should check first on Communication mode
 */
void MCAL_SPI_SendData(SPI_TypeDef * SPIx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn)
{
	if(PollingEn == enable)
		while(! ((SPIx->SR) & SPI_SR_TXE)); //wait until the TX buffer be empty

	SPIx->DR = *pTxBuffer;

}

/**================================================================
 * @Fn               - MCAL_SPI_ReceiveData
 * @brief            -receive buffer on SPI
 *param[in]         -SPIx :where x can be 1,2 depending on device used
 *param[in]         -pTxBuffer: the buffer that will be transmitted
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -none
 */

void MCAL_SPI_ReceiveData(SPI_TypeDef * SPIx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn)
{
	if(PollingEn == enable)
		while(! ((SPIx->SR) & SPI_SR_RXNE)); //wait until the RX buffer be not empty

	*pTxBuffer = SPIx->DR;

}



/**================================================================
 * @Fn               - MCAL_SPI_TX_RX
 * @brief            -receive and transmit buffer on SPI
 *param[in]         -SPIx :where x can be 1,2 depending on device used
 *param[in]         -pTxBuffer: the buffer that will be transmitted
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -none
 */

void MCAL_SPI_TX_RX(SPI_TypeDef * SPIx , uint16_t* pTxBuffer , enum Polling_mechanism PollingEn)
{

	if(PollingEn == enable)
		while(! ((SPIx->SR) & SPI_SR_TXE)); //wait until the TX buffer be empty

	SPIx->DR = *pTxBuffer;

	if(PollingEn == enable)
		while(! ((SPIx->SR) & SPI_SR_RXNE)); //wait until the RX buffer be not empty

	*pTxBuffer = SPIx->DR;

}

/**================================================================
 * @Fn               - MCAL_SPI_GPIO_Set_Pins
 * @brief            -set the Gpio pins (can know the Pins from GPIO Pins table from TRM)
 *param[in]         -SPIx :where x can be 1,2,depending on device used
 * @retval           -none
 * Note              -should enable the corresponding ALT &GPIO in RCC CLOCK AND called after MCAL_SPI_INIT()
 */

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef * SPIx)
{
	GPIO_PinConfig_t pincfg;
	if (SPIx == SPI1)
	{
		//PA4 :SPI1_NSS
		//PA5 :SPI1_SCK
		//PA6 :SPI1_MISO
		//PA7 :SPI1_MOSI
		//from recommendation table in GPIO chapter
		if(Global_SPI_Config[SPI1_Index]->Device_Mode ==SPI_Device_Mode_Master)
		{
			//PA4 :SPI1_NSS

			switch(Global_SPI_Config[SPI1_Index]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable : //NSS input to sense multi master
				//Hardware master input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_4;
				pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA,&pincfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable :
				//Hardware master ALternative output
				pincfg.GPIO_PinNumber = GPIO_PIN_4;
				pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
				pincfg.GPIO_output_speed = GPIO_output_speed_10M;
				MCAL_GPIO_Init(GPIOA,&pincfg);
				break;

			}
			//PA5 :SPI1_SCK
			//Master output alternative function push pull
			pincfg.GPIO_PinNumber = GPIO_PIN_5;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOA,&pincfg);

			//PA6 :SPI1_MISO
			//Master input floating in case of FULL Duplex
			pincfg.GPIO_PinNumber = GPIO_PIN_6;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&pincfg);

			//PA7 :SPI1_MOSI
			//Master ouput alternative function PP in case of FULL Duplex

			pincfg.GPIO_PinNumber = GPIO_PIN_7;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOA,&pincfg);


		}
		else //slave
		{     //PA4 :SPI1_NSS
			if(Global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_Hard_Slave) //in case of sw there is no gpio configuration
			{
				//Hardware slave input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_4;
				pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA,&pincfg);
			}


			//PA5 :SPI1_SCK
			//slave input floating
			pincfg.GPIO_PinNumber = GPIO_PIN_5;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&pincfg);


			//PA6 :SPI1_MISO
			//slave alternative output pp
			pincfg.GPIO_PinNumber = GPIO_PIN_6;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOA,&pincfg);


			//PA7 :SPI1_MOSI
			//slave input floating
			pincfg.GPIO_PinNumber = GPIO_PIN_7;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA,&pincfg);


		}


	}
	else if (SPIx == SPI2)
	{
		//PB12 :SPI2_NSS
		//PB13 :SPI2_SCK
		//PB14 :SPI2_MISO
		//PB15 :SPI2_MOSI

		if(Global_SPI_Config[SPI2_Index]->Device_Mode ==SPI_Device_Mode_Master)
		{



			//PB12 :SPI2_NSS

			switch(Global_SPI_Config[SPI2_Index]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable : //NSS input to sense multi master
				//Hardware master input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_12;
				pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB,&pincfg);
				break;

			case SPI_NSS_Hard_Master_SS_output_enable :
				//Hardware master ALternative output
				pincfg.GPIO_PinNumber = GPIO_PIN_12;
				pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
				pincfg.GPIO_output_speed = GPIO_output_speed_10M;
				MCAL_GPIO_Init(GPIOB,&pincfg);
				break;

			}
			//PB13 :SPI2_SCK
			//Master output alternative function push pull
			pincfg.GPIO_PinNumber = GPIO_PIN_13;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOB,&pincfg);

			//PB14 :SPI2_MISO
			//Master input floating in case of FULL Duplex
			pincfg.GPIO_PinNumber = GPIO_PIN_14;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB,&pincfg);

			//PB15 :SPI2_MOSI
			//Master ouput alternative function PP in case of FULL Duplex

			pincfg.GPIO_PinNumber = GPIO_PIN_15;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOB,&pincfg);


		}
		else //slave
		{     //PB12 :SPI2_NSS
			if(Global_SPI_Config[SPI2_Index]->NSS == SPI_NSS_Hard_Slave) //in case of sw there is no gpio configuration
			{
				//Hardware slave input floating
				pincfg.GPIO_PinNumber = GPIO_PIN_12;
				pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB,&pincfg);
			}


			//PB13 :SPI2_SCK
			//slave input floating
			pincfg.GPIO_PinNumber = GPIO_PIN_13;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB,&pincfg);


			//PB14 :SPI2_MISO
			//slave alternative output pp
			pincfg.GPIO_PinNumber = GPIO_PIN_14;
			pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_PP;
			pincfg.GPIO_output_speed = GPIO_output_speed_10M;
			MCAL_GPIO_Init(GPIOB,&pincfg);


			//PB15 :SPI2_MOSI
			//slave input floating
			pincfg.GPIO_PinNumber = GPIO_PIN_15;
			pincfg.GPIO_Mode = GPIO_Mode_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB,&pincfg);


		}

	}
}

/*
 * ====================================================================================================
 *                                        IRQ
 * ====================================================================================================
 */

void SPI1_IRQHandler (void)  /* SPI1 global interrupt*/
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI1->SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI1->SR & (1<<0)) >> 0);
	irq_src.ERR = ((SPI1->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI1_Index]->P_IRQ_CallBack (irq_src);

}

void SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src;
	irq_src.TXE = ((SPI2->SR & (1<<1)) >> 1);
	irq_src.RXNE = ((SPI2->SR & (1<<0)) >> 0);
	irq_src.ERR = ((SPI2->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI2_Index]->P_IRQ_CallBack (irq_src);
}











