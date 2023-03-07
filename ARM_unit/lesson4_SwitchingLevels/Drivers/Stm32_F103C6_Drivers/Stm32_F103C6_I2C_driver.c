/*
 * Stm32_F103C6_I2C_driver.c
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#include "Stm32_F103C6_I2C_driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */
I2C_InitTyeDef Global_I2C_Config[2] = {NULL , NULL};


/*
 * ======================================================================
 *                                          Generic Macros
 *======================================================================
 */

#define       I2C1_INDEX                                   0
#define       I2C2_INDEX                                   1



/*
 * ====================================================================================================
 *                          APIs Functions Definations
 * ====================================================================================================
 */


/**================================================================
 * @Fn               -MCAL_I2C_INIT
 * @brief            -Initialize I2C according to the specified parameters
 *param[in]         -I2Cx :where x can be 1,2 depending on device used
 *param[in]           -I2C_InitStruct :all the I2C configuration
 * @retval           -none
 * Note              -support for SM only
 */
void MCAL_I2C_INIT(I2C_TypeDef * I2Cx , I2C_InitTyeDef* I2C_InitStruct)
{
	uint16_t tempreg = 0 , freqrange = 0 ;
	uint32_t PClk1 = 8000000 ;
	uint16_t result = 0 ;

	//Enable RCC Clock
	if (I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_InitStruct ;
		RCC_I2C1_CLK_EN();


	}else //I2C2
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_InitStruct ;
		RCC_I2C2_CLK_EN();
	}

	if(I2C_InitStruct->I2C_Mode == I2C_Mode_I2C)
	{
		/*------------------------------------------Init Timing---------------------------*/

		//1-I2C_CR2 :FREQ[5:0]:Peripheral clock frequency
		/*get the I2Cx_CR2 Value */
		tempreg = I2Cx->CR2 ;
		/*clear the FREQ[5:0] bits  */
		tempreg &= ~(I2C_CR2_FREQ_Msk) ;
		/*get PCLK1 frequency value */
		PClk1 = MCAL_RCC_GetPCLK1Freq();
		/*Set frequency Bits depending on PClk1 value */
		freqrange = (uint16_t)(PClk1 / 1000000);
		tempreg |= freqrange;
		/* write to CR2*/
		I2Cx->CR2 = tempreg ;

		//2-Configure the clock control registers

		/*Disable the selected I2C Peripheral to configure Time Just to make sure */
		I2Cx->CR1 &= ~(I2C_CR1_PE);
		tempreg = 0;

		/*Configure speed in standard mode */
		if((I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_50K) || (I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_100K))
		{
			/*standard mode speed calculation*/
			//T_high = CCR*T_pclk1 & T_pclk1 = T_high + T_low
			//CRR = Tclk / (2*Tpclk1)
			//CRR = (F_pclk1) / (2* F_i2cclk)
			result =(uint16_t) (PClk1 / ( I2C_InitStruct->I2C_ClockSpeed * 2 ));
			tempreg = I2Cx->CCR;
			tempreg |= result;
			/* write to CRR*/
			I2Cx->CCR = tempreg ;

			//3-I2C_TRISE Configuration
			/* frequency bits +1 */
			I2Cx->TRISE = freqrange +1 ;

		}
		else
		{
			//fast mode not Supported
		}

		/*------------------------------------------I2Cx CR1 Configuration ---------------------------*/
		/*get the I2Cx_CR1 Value */
		tempreg = I2Cx->CR1 ;
		tempreg |= (uint16_t)(I2C_InitStruct->I2c_ACK_Control | I2C_InitStruct->General_Call_Address_Detection | I2C_InitStruct->I2C_Mode |I2C_InitStruct->StretchMode);

		/* write to CR1*/
		I2Cx->CR1 =tempreg ;

		/*------------------------------------------I2Cx OAR1 & I2Cx OAR2 Configuration ---------------------------*/
		tempreg = 0;
		if(I2C_InitStruct->I2C_Slave_Address.Enable_Dual_ADD == 1) // there is a secendry address
		{
			tempreg = I2C_OAR2_ENDUAL;
			tempreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_add << I2C_OAR2_ADD2_Pos; //<<1
			I2Cx->OAR2 =tempreg ;
		}
		//Primary address
		tempreg = 0;
		tempreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_add << 1 ;
		tempreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_Slave_mode ;		//7bit add or 10
		I2Cx->OAR1 =tempreg ;




	}else
	{
		//SMBUS Not supported
	}

	//Interrupt Mode (Slave Mode)
	if(I2C_InitStruct->P_Slave_Event_CallBack != NULL) //enable SLAVE IRQ states Mode
	{
		//Enable irq
		I2Cx->CR2 |= I2C_CR2_ITERREN ;
		I2Cx->CR2 |= I2C_CR2_ITEVTEN ;
		I2Cx->CR2 |= I2C_CR2_ITBUFEN ;
		if(I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;
		}
		else if(I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}

		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;

	}

	/*Enable the selected I2C Peripheral */
	I2Cx->CR1 |= (I2C_CR1_PE);




}

/**================================================================
 * @Fn               -MCAL_I2C_DeINIT
 * @brief            -DeInitialize I2C
 *param[in]         -I2Cx :where x can be 1,2 depending on device used
 * @retval           -none
 * Note              -Reset the model by RCC
 */
void MCAL_I2C_DeINIT(I2C_TypeDef * I2Cx )
{
	if(I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		RCC_I2C1_Reset();
	}
	else if(I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
		RCC_I2C2_Reset();
	}



}

/**================================================================
 * @Fn               - MCAL_I2C_GPIO_Set_Pins
 * @brief            -set the Gpio pins (can know the Pins from GPIO Pins table from TRM)
 *param[in]         -I2Cx :where x can be 1,2,depending on device used
 * @retval           -none
 * Note              -should enable the corresponding ALT &GPIO in RCC CLOCK AND called after MCAL_I2C_INIT()
 */

void MCAL_I2C_GPIO_Set_Pins (I2C_TypeDef * I2Cx)
{
	GPIO_PinConfig_t Pincfg;

	if(I2Cx == I2C1)
	{
		//PB6 : I2C1_SCL
		//PB7 : I2C1_SDA
		Pincfg.GPIO_PinNumber = GPIO_PIN_6 ;
		Pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_OD;
		Pincfg.GPIO_output_speed = GPIO_output_speed_10M;
		MCAL_GPIO_Init(GPIOB,&Pincfg);

		Pincfg.GPIO_PinNumber = GPIO_PIN_7 ;
		Pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_OD;
		Pincfg.GPIO_output_speed = GPIO_output_speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pincfg);
	}

	else if(I2Cx == I2C2)
	{
		//PB10 : I2C2_SCL
		//PB11 : I2C2_SDA
		Pincfg.GPIO_PinNumber = GPIO_PIN_10 ;
		Pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_OD;
		Pincfg.GPIO_output_speed = GPIO_output_speed_10M;
		MCAL_GPIO_Init(GPIOB,&Pincfg);

		Pincfg.GPIO_PinNumber = GPIO_PIN_11 ;
		Pincfg.GPIO_Mode = GPIO_Mode_OUTPUT_AF_OD;
		Pincfg.GPIO_output_speed = GPIO_output_speed_10M;
		MCAL_GPIO_Init(GPIOB, &Pincfg);
	}


}

/**================================================================
 * @Fn               -MCAL_I2C_Master_TX
 * @brief            - I2C Master transmit according to the specified parameters
 *param[in]           -I2Cx :where x can be 1,2 depending on device used
 *param[in]           -devAddr :the device address that the master want transmit data to it
 *param[in]             -dataOut :Pointer to the data that will be transmitted
 *param[in]            -datalen : the length of the data
 *param[in]            -Stop : specifies whether is there stop condition or not
 *param[in]            -Start : specifies whether is there a repeated start or not
 * @retval           -none
 * Note              -none
 */
void MCAL_I2C_Master_TX(I2C_TypeDef * I2Cx , uint16_t devAddr , uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start)
{
	int i = 0;
	/*To do add timeout (configure timer working for specific duration rise interrupt
	 * timer_interuptISR{flag = 1}
	 * so any code exist in while(check flag || any polling conditions) */

	/*1--Set the start bit in the I2C_CR1 register to generate a start condition */

	I2C_GenerateSTART(I2Cx, ENABLE,Start);

	/*2--wait for EV5*/
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while (!(I2C_GetFlagStatus(I2Cx,EV5)));

	/*--Send Address*/
	I2C_SendAddress(I2Cx, devAddr,I2C_Direction_Transmitter);

	/*3--wait for EV6*/
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while (!(I2C_GetFlagStatus(I2Cx,EV6)));

	/*4--check for TRA (transmition) , BUSY (BUS is busy),MSL(still the Master didnot lose arbitration),TXE(EV8_1)*/
	//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	while (!(I2C_GetFlagStatus(I2Cx,MASTER_BYTE_TRANSMITING)));

	/*Send the data*/
	for(i=0 ; i< datalen ; i++)
	{
		/*write in the DR register the data to be sent*/
		I2Cx->DR = dataOut[i];
		/*wait for EV8*/
		//EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
		while (!(I2C_GetFlagStatus(I2Cx,EV8)));
	}

	/*6--wait for EV8_2*/
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	//while (!(I2C_GetFlagStatus(I2Cx,EV8_2)));

	/*7--send a stop condition*/
	if(Stop == with_Stop)
	{
		I2C_GenerateSTOP(I2Cx,ENABLE);
	}

}

/**================================================================
 * @Fn               -MCAL_I2C_Master_RX
 * @brief            - I2C Master Receive according to the specified parameters
 *param[in]           -I2Cx :where x can be 1,2 depending on device used
 *param[in]           -devAddr :the device address that the master want transmit data to it
 *param[in]             -dataOut :Pointer to the data that will be received
 *param[in]            -datalen : the length of the data
 *param[in]            -Stop : specifies whether is there stop condition or not
 *param[in]            -Start : specifies whether is there a repeated start or not
 * @retval           -none
 * Note              -none
 */
void MCAL_I2C_Master_RX(I2C_TypeDef * I2Cx , uint16_t devAddr , uint8_t* dataOut , uint32_t datalen , Stop_Condition Stop , Repeated_Start Start)
{
	uint8_t index = (I2Cx == I2C1) ? I2C1_INDEX :I2C2_INDEX ;
	int i = 0;

	/*1--Set the start bit in the I2C_CR1 register to generate a start condition */

	I2C_GenerateSTART(I2Cx, ENABLE,Start);

	/*2--wait for EV5*/
	//EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while (!(I2C_GetFlagStatus(I2Cx,EV5)));

	/*--Send Address*/
	I2C_SendAddress(I2Cx, devAddr,I2C_Direction_receieve);

	/*3--wait for EV6*/
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while (!(I2C_GetFlagStatus(I2Cx,EV6)));

	//enable the ACKnowlage
	I2C_ACKnowlageConfig(I2Cx ,ENABLE);

	if(datalen)//if the data exist
	{   //read the data until len become zero
		for(i= datalen ; i >1 ; i--)
		{
			/*4--wait for EV7 RXNE */
			while (!(I2C_GetFlagStatus(I2Cx,EV7)));

			/*read the data from the DR into the buffer*/
			*dataOut = I2Cx->DR ;

			/*Increment the buffer*/
			dataOut++;

		}

		//5--Send Not ACKnowlage
		I2C_ACKnowlageConfig(I2Cx ,DISABLE);
	}

	/*6--send a stop condition*/
	if(Stop == with_Stop)
	{
		I2C_GenerateSTOP(I2Cx,ENABLE);
	}

	//RE enable ACKnowlage if this is the defalt
	if(Global_I2C_Config[index].I2c_ACK_Control == I2C_ACK_Enable)
	{
		I2C_ACKnowlageConfig(I2Cx ,ENABLE);
	}


}

void MCAL_I2C_SlaveSendData(I2C_TypeDef * I2Cx ,uint8_t data)
{
	I2Cx->DR = data;
}
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef * I2Cx)
{
	return (uint8_t) I2Cx->DR ;
}


/*
 * ======================================================================
 *                                          Generic Functions
 *======================================================================
 */

void I2C_GenerateSTART(I2C_TypeDef * I2Cx , FunctionalState NewState ,Repeated_Start Start)
{
	if(Start != repeated_start)
	{
		//check if the bus is idle
		while (I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY )); //oring with timer --> not stuck in this while
	}

	if(NewState != DISABLE )
	{
		/*Generate a start condition*/
		I2Cx->CR1 |= I2C_CR1_START ;
	}
	else
	{
		/*disable the  start condition*/
		I2Cx->CR1 &= ~(I2C_CR1_START) ;
	}
}

void I2C_SendAddress(I2C_TypeDef * I2Cx ,uint16_t Address , I2C_Direction Direction)//suppoted 7 bit mode only
{
	Address = Address <<1 ;
	if(Direction != I2C_Direction_Transmitter)
	{
		/*Set the address bit0 for read*/
		Address |= 1<<0;
	}
	else
	{
		/*reset the address bit0 for write*/
		Address &= ~ (1<<0);
	}

	/*Send the address*/
	I2Cx->DR = Address ;

}

FlagStatus I2C_GetFlagStatus(I2C_TypeDef * I2Cx , Status flag)
{
	volatile uint32_t dummyread ;
	FlagStatus bitstatus = RESET ;
	uint32_t flag1 =0 , flag2 =0;
	uint32_t lastevent =0;

	switch(flag)
	{
	case I2C_FLAG_BUSY:
	{
		//		Bit 1 BUSY: Bus busy
		//		0: No communication on the bus
		//		1: Communication ongoing on the bus
		//		– Set by hardware on detection of SDA or SCL low
		//		– cleared by hardware on detection of a Stop condition.
		//		It indicates a communication in progress on the bus. This information is still updated when
		//		the interface is disabled (PE=0).
		if(I2Cx->SR2 & I2C_SR2_BUSY)
			bitstatus = SET ;
		else
			bitstatus =RESET ;
		break ;
	}
	case EV5 :
	{
		//		Bit 0 SB: Start bit (Master mode)
		//		0: No Start condition
		//		1: Start condition generated.
		//		– Set when a Start condition generated.
		//		– Cleared by software by reading the SR1 register followed by writing the DR register, or by
		//		hardware when PE=0
		if(I2Cx->SR1 & I2C_SR1_SB)
			bitstatus = SET ;
		else
			bitstatus =RESET ;
		break ;
	}
	case EV6 :
	{
		//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
		if(I2Cx->SR1 & I2C_SR1_ADDR)
			bitstatus = SET ;
		else
			bitstatus =RESET ;
		break ;
	}
	case MASTER_BYTE_TRANSMITING :
	{
		/*read I2Cx status registers*/
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		//concatenate SR1&SR2
		flag2 = flag2<<16;
		lastevent = ((flag1 | flag2) &(uint32_t)0x00FFFFFF);

		if((lastevent & flag )== flag)
			bitstatus = SET ;
		else
			{bitstatus =RESET ;}
		break ;
	}
	case EV8_1: //EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
	case EV8 : //EV8: TxE=1, shift register not empty, .data register empty, cleared by writing DR register
	{
		if(I2Cx->SR1 & I2C_SR1_TXE)
			bitstatus = SET ;
		else
			bitstatus =RESET ;
		break ;
	}


	case EV7 :
	{
		//	Bit 7 TxE: Data register empty (transmitters)
		//	0: Data register not empty
		//	1: Data register empty
		//	– Set when DR is empty in transmission. TxE is not set during address phase.
		//	– Cleared by software writing to the DR register or by hardware after a start or a stop condition
		//	or when PE=0.
		//	TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
		//	Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
		//	BTF is set, as in both cases the data register is still empty.
		if(I2Cx->SR1 & I2C_SR1_RXNE)
			bitstatus = SET ;
		else
			bitstatus =RESET ;
		break ;
	}


	}
	return bitstatus;

}

void I2C_GenerateSTOP(I2C_TypeDef * I2Cx , FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		/*generate a stop condition*/
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		/*disable the stop condition*/
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}
}

void I2C_ACKnowlageConfig(I2C_TypeDef * I2Cx  ,FunctionalState NewState)
{
	if(NewState != DISABLE)
		{
			/*generate the acknowladge*/
			I2Cx->CR1 |= I2C_CR1_ACK;
		}
		else
		{
			/*disable the acknowladge*/
			I2Cx->CR1 &= ~(I2C_CR1_ACK);
		}
}

/*
 * ====================================================================================================
 *                                        IRQ
 * ====================================================================================================
 */

//void I2C1_EV_IRQHandler (void)     		         	/* I2C1 event interrupt */
//{
//
//}
//void I2C1_ER_IRQHandler (void)       			/* I2C1 error interrupt */
//{
//
//}
//void I2C2_EV_IRQHandler(void)        			/* I2C2 event interrupt  */
//{
//
//}
//void I2C2_ER_IRQHandler(void)                  /* I2C2 error interrupt */
//{
//
//}









