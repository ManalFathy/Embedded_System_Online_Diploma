/*
 * Stm32_F103C6_gpio_driver.c
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#include "Stm32_F103C6_gpio_driver.h"

uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0 :
		return 0 ;
		break ;
	case GPIO_PIN_1 :
		return 4 ;
		break ;
	case GPIO_PIN_2 :
		return 8 ;
		break ;
	case GPIO_PIN_3 :
		return 12 ;
		break ;
	case GPIO_PIN_4 :
		return 16 ;
		break ;
	case GPIO_PIN_5 :
		return 20 ;
		break ;
	case GPIO_PIN_6 :
		return 24 ;
		break ;
	case GPIO_PIN_7 :
		return 28 ;
		break ;
	case GPIO_PIN_8 :
		return 0 ;
		break ;
	case GPIO_PIN_9 :
		return 4 ;
		break ;
	case GPIO_PIN_10 :
		return 8 ;
		break ;
	case GPIO_PIN_11 :
		return 12 ;
		break ;
	case GPIO_PIN_12 :
		return 16 ;
		break ;
	case GPIO_PIN_13 :
		return 20 ;
		break ;
	case GPIO_PIN_14 :
		return 24 ;
		break ;
	case GPIO_PIN_15 :
		return 28 ;
		break ;
	}
	return 0 ;
}

/**================================================================
 * @Fn               -MCAL_GPIO_Init
 * @brief            -Initializes the GPIOx PINy according to the specified parameters in the pin config
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]        -Pinconfid :pointer to a GPIO_PinConfig_t structure that contains the configration
 *                     information for the specified GPIO PIN
 * @retval           -none
 * Note              -stm32f103c6 MCU has GPIO A,B,C,D,E Modules
 *                     But LQFP48 package has only GPIO A,B,part of C,D exported as external pins from thw MCU
 */

void MCAL_GPIO_Init(GPIO_TypeDef* GPIOx , GPIO_PinConfig_t* Pinconfig)
{
	//Port configuration register low (GPIOx_CRL) Configure PINS from 0 >> 7
	//Port configuration register High (GPIOx_CRH) Configure PINS from 8 >> 15
	volatile uint32_t* configregister = NULL ;
	uint8_t pin_config = 0;
	configregister = (Pinconfig ->GPIO_PinNumber < GPIO_PIN_8) ?  &GPIOx->CRL : &GPIOx->CRH ;

	//clear CNF[1:0] MODE[1:0]
	(*configregister) &= ~(0xf << Get_CRLH_Position(Pinconfig->GPIO_PinNumber)) ;

	//if pin is output
	if ( (Pinconfig->GPIO_Mode == GPIO_Mode_OUTPUT_AF_OD) || (Pinconfig->GPIO_Mode == GPIO_Mode_OUTPUT_AF_PP) || (Pinconfig->GPIO_Mode == GPIO_Mode_OUTPUT_OD) || (Pinconfig->GPIO_Mode == GPIO_Mode_OUTPUT_PP) )
	{
		pin_config =  ((((Pinconfig->GPIO_Mode -4) << 2) | Pinconfig->GPIO_output_speed) & 0x0f );

	}
	//if pin is input
	else
	{
		// MODE = 00: Input mode (reset state)

		if ( (Pinconfig->GPIO_Mode == GPIO_Mode_Analog) || (Pinconfig->GPIO_Mode == GPIO_Mode_INPUT_FLO ))
		{
			pin_config =  ((((Pinconfig->GPIO_Mode) << 2) | 0x0) & 0x0f );

		}
		else if (Pinconfig->GPIO_Mode == GPIO_Mode_AF_INPUT) //consider it as input floating
		{
			pin_config =  ((((GPIO_Mode_INPUT_FLO) << 2) | 0x0) & 0x0f );
		}
		else //PU PD Input
		{
			pin_config =  ((((Pinconfig->GPIO_Mode) << 2) | 0x0) & 0x0f );
			if(Pinconfig->GPIO_Mode == GPIO_Mode_INPUT_PU)
			{
				//Table 20. Port bit configuration table PxODR 1
				GPIOx->ODR |= Pinconfig->GPIO_PinNumber ;
			}
			else //PD
			{
				//Table 20. Port bit configuration table PxODR 0
				GPIOx->ODR &= ~ (Pinconfig->GPIO_PinNumber) ;
			}
		}

	}
	//write on CRL OR CRH

	(*configregister) |= ( (pin_config) << Get_CRLH_Position(Pinconfig->GPIO_PinNumber) );

}


/**================================================================
 * @Fn               -MCAL_GPIO_DeInit
 * @brief            -Reset the GPIOx Registers
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval           -none
 * Note              -none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
	/* Manual Reset
	GPIOx->CRL = 0x44444444 ;
	GPIOx->CRH = 0x44444444 ;
	//GPIOx->IDR read only
	GPIOx->ODR = 0x00000000 ;
	GPIOx->BSRR = 0x00000000 ;
	GPIOx->BRR = 0x00000000 ;
	GPIOx->LCKR = 0x00000000 ;

	or you can use the reset controller in RCC
	APB2 peripheral reset register (RCC_APB2RSTR)
	SEt and cleared by software
	 */
	if (GPIOx == GPIOA)
	{
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if (GPIOx == GPIOB)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if (GPIOx == GPIOC)
	{
		RCC->APB2RSTR |= (1<<4);
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if (GPIOx == GPIOD)
	{
		RCC->APB2RSTR |= (1<<5);
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if (GPIOx == GPIOE)
	{
		RCC->APB2RSTR |= (1<<6);
		RCC->APB2RSTR &= ~(1<<6);
	}

}

/**================================================================
 * @Fn               -MCAL_GPIO_ReadPin
 * @brief            -Read specific pin
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]        -PinNumber : Set Pin Number according to @ref GPIO_PINS_define
 * @retval           -the input pin value (two values based on @ref GPIO_PIN_state
 * Note              -none
 */
uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef * GPIOx , uint16_t PinNumber)
{
	uint8_t bitstatus ;
	if (((GPIOx->IDR) & PinNumber) != (uint32_t)GPIO_PIN_RESET )
	{
		bitstatus = GPIO_PIN_SET ;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET ;
	}

	return bitstatus ;

}

/**================================================================
 * @Fn               -MCAL_GPIO_ReadPort
 * @brief            -Read the input port value
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @retval           -the input port value
 * Note              -none
 */
uint16_t MCAL_GPIO_ReadPORT (GPIO_TypeDef * GPIOx)
{
	 uint16_t port_value ;
	port_value = (uint16_t)(GPIOx->IDR) ;
	return port_value ;
}

/**================================================================
 * @Fn               -MCAL_GPIO_WritePin
 * @brief            -write specific pin
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]        -PinNumber : specifies the port Pin to read set by @ref GPIO_PINS_define
 * @param[in]        -Value : Pin value
 * @retval           -none
 * Note              -none
 */

void MCAL_GPIO_WritePin (GPIO_TypeDef * GPIOx , uint16_t PinNumber , uint8_t value)
{

	if (value != (uint32_t)GPIO_PIN_RESET )
	{
		//GPIOx->ODR |= PinNumber ;
		//or
		//		BSy: Port x Set bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Set the corresponding ODRx bit
		GPIOx->BSRR = (uint32_t)PinNumber ;
	}
	else
	{
		//		BRy: Port x Reset bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Reset the corresponding ODRx bit
		GPIOx->BRR = (uint32_t)PinNumber ;
	}
}

/**================================================================
 * @Fn               -MCAL_GPIO_WritePort
 * @brief            -write on output port
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]        -Value : Port value
 * @retval           -none
 * Note              -none
 */
void MCAL_GPIO_WritePORT (GPIO_TypeDef * GPIOx , uint16_t value)
{
	GPIOx->ODR = (uint32_t)value ;

}

/**================================================================
 * @Fn               -MCAL_GPIO_TogglePin
 * @brief            -Toggles specific pin
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]        -PinNumber : specifies the port Pin to toggle set by @ref GPIO_PINS_define
 * @retval           -none
 * Note              -none
 */
void MCAL_GPIO_TogglePin (GPIO_TypeDef * GPIOx , uint16_t PinNumber)
{
	GPIOx->ODR ^= PinNumber ;

}
/**================================================================
 * @Fn               -MCAL_GPIO_LockPin
 * @brief            -The locking mechanism allows the IO configuration to be frozen until the next reset
 * @param[in]        -GPIOx :where x can be (A..E depending on device used) to select the GPIO peripheral
 * @param[in]        -PinNumber : specifies the port Pin to toggle set by @ref GPIO_PINS_define
 * @retval           -OK if pin config is Locked or ERROR if pin not locked (OK &ERROR are defined @ref GPIO_RETURN_LOCK
 * Note              -none
 */
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef * GPIOx , uint16_t PinNumber)
{
	//	Bit 16 LCKK[16]: Lock key
	//	This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
	//	0: Port configuration lock key not active
	//	1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
	//	LOCK key writing sequence:
	//	Write 1
	//	Write 0
	//	Write 1
	//	Read 0
	//	Read 1 (this read is optional but confirms that the lock is active)
	//	Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
	//	Any error in the lock sequence will abort the lock.
	//	Bits 15:0 LCKy: Port x Lock bit y (y= 0 .. 15)
	//	These bits are read write but can only be written when the LCKK bit is 0.
	//	0: Port configuration not locked
	//	1: Port configuration locked.

	//set LCKK[16]
	volatile uint32_t temp = 1<<16 ;
	//SET LCKY
	temp |= PinNumber ;
	//	Write 1
	GPIOx->LCKR = temp ;
	//	Write 0 and keep the LCKy 1
	GPIOx->LCKR = PinNumber;
	//	Write 1
	GPIOx->LCKR = temp ;
	//	Read 0
	temp = GPIOx->LCKR ;
	//	Read 1
	if((uint32_t) GPIOx->LCKR & 1<<16)
	{
		return GPIO_RETURN_LOCK_Enabled;
	}
	else
	{
		return GPIO_RETURN_LOCK_ERROR;
	}


}
