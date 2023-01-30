/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"


#define HSE_CLK (uint32_t)16000000
#define HSI_RC_CLK (uint32_t)8000000

//-----------------------------
//User type definitions (structures)
//config structure
//-----------------------------

//-----------------------------
//Macros Configuration References
//-----------------------------
/*@ref Module_REF_NAME_define

/*
 * ====================================================================================================
 *                          APIs Supported by "MCAL RCC DRIVER"
 * ====================================================================================================
 */
uint32_t MCAL_RCC_GetSYSCLK1Freq(void) ;
uint32_t MCAL_RCC_GetHCLKFreq(void) ;
uint32_t MCAL_RCC_GetPCLK1Freq(void) ;
uint32_t MCAL_RCC_GetPCLK2Freq(void) ;





#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
