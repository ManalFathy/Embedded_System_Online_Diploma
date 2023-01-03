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

void clock_init()
{
	//enable GPIOA clock
	RCC_GPIOA_CLK_EN();
	//enable GPIOB clock
	RCC_GPIOB_CLK_EN() ;
}

void GPIO_init()
{
	GPIO_PinConfig_t pinconfig ;
	//PA1 input HighZ floating input
	pinconfig.GPIO_PinNumber = GPIO_PIN_1 ;
	pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
	MCAL_GPIO_Init(GPIOA, &pinconfig);



	//pB1 output push pull mode
	// output max 10MHZ
	pinconfig.GPIO_PinNumber = GPIO_PIN_1 ;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(GPIOB, &pinconfig);

	//PA13 input HighZ
	pinconfig.GPIO_PinNumber = GPIO_PIN_13 ;
	pinconfig.GPIO_Mode = GPIO_Mode_INPUT_FLO ;
	MCAL_GPIO_Init(GPIOA, &pinconfig);

	//pB13 output push pull mode
	pinconfig.GPIO_PinNumber = GPIO_PIN_13 ;
	pinconfig.GPIO_Mode = GPIO_Mode_OUTPUT_PP ;
	pinconfig.GPIO_output_speed = GPIO_output_speed_10M;
	MCAL_GPIO_Init(GPIOB, &pinconfig);
}

void my_wait(int x)
{
	unsigned int i,j;
	for(i=0 ; i<x ; i++);
	for(j=0 ;j<255 ; j++);
}

int main(void)
{
	clock_init();
	GPIO_init();

	while(1)
	{
		//PA1 connected with external PUR

		if( MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0 ) // press
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1) ;
			while(  MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0 ) ;//single press

		}

		//PA13 connected with external PDR
		if( MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1 ) // MULTIpress
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13) ;;

		}
		my_wait(1);

	}

	return 0;
}
