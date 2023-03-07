/*
 * Stm32_F103C6_gpio_driver.h
 *
 *  Created on: Dec 29, 2022
 *      Author: manal
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103x6.h"


//-----------------------------
//User type definitions (structures)
//config structure
//-----------------------------

typedef struct
{
	uint16_t GPIO_PinNumber             ; //Specifies the GPIO PINS to be configured
	                                     // This parameter must be set based on @ref GPIO_PINS_define

	uint8_t  GPIO_Mode                ;//Specifies the operating mode for the selected pins
	                                   // This parameter must be set based on @ref GPIO_MODE_define

	uint8_t  GPIO_output_speed       ;//Specifies the speed for the selected pins
		                             // This parameter must be set based on @ref GPIO_output_speed_define
}GPIO_PinConfig_t;
//-----------------------------
//Macros Configuration References
//-----------------------------
/*@ref Module_REF_NAME_define
 */

//@ref GPIO_PIN_state
#define GPIO_PIN_SET                         1
#define GPIO_PIN_RESET                       0

//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_Enabled             1
#define GPIO_RETURN_LOCK_ERROR               0

//@ref GPIO_PINS_define
#define GPIO_PIN_0                   ((uint16_t)0x0001)  /* Pin 0 Selected  1*/
#define GPIO_PIN_1                   ((uint16_t)0x0002)  /* Pin 1 Selected   10*/
#define GPIO_PIN_2                   ((uint16_t)0x0004)  /* Pin 2 Selected   100*/
#define GPIO_PIN_3                   ((uint16_t)0x0008)  /* Pin 3 Selected    1000*/
#define GPIO_PIN_4                   ((uint16_t)0x0010)  /* Pin 4 Selected */
#define GPIO_PIN_5                   ((uint16_t)0x0020)  /* Pin 5 Selected */
#define GPIO_PIN_6                  ((uint16_t)0x0040)   /* Pin 6 Selected */
#define GPIO_PIN_7                   ((uint16_t)0x0080)  /* Pin 7 Selected */
#define GPIO_PIN_8                   ((uint16_t)0x0100)  /* Pin 8 Selected */
#define GPIO_PIN_9                   ((uint16_t)0x0200)  /* Pin 9 Selected */
#define GPIO_PIN_10                   ((uint16_t)0x0400)  /* Pin 10 Selected */
#define GPIO_PIN_11                   ((uint16_t)0x0800)  /* Pin 11 Selected */
#define GPIO_PIN_12                   ((uint16_t)0x1000)  /* Pin 12 Selected */
#define GPIO_PIN_13                   ((uint16_t)0x2000)  /* Pin 13 Selected */
#define GPIO_PIN_14                   ((uint16_t)0x4000)  /* Pin 14 Selected */
#define GPIO_PIN_15                  ((uint16_t)0x8000)   /* Pin 15 Selected */
#define GPIO_PIN_All                  ((uint16_t)0xFFFF)   /* ALL Pins Selected */

#define GPIO_PIN_MASK                  0x0000FFFFu   /* Pin mask for assert test */


//@ref GPIO_MODE_define
#define GPIO_Mode_Analog                   0x00000000u     //Analog mode
#define GPIO_Mode_INPUT_FLO                0x00000001u     //Floating input mode
#define GPIO_Mode_INPUT_PU                 0x00000002u     //Input with pull-up mode
#define GPIO_Mode_INPUT_PD                 0x00000003u     //Input with pull-down mode
#define GPIO_Mode_OUTPUT_PP                0x00000004u     //General purpose output push-pull mode
#define GPIO_Mode_OUTPUT_OD                0x00000005u     //General purpose output Open-drain mode
#define GPIO_Mode_OUTPUT_AF_PP             0x00000006u     //Alternate function output Push-pull mode
#define GPIO_Mode_OUTPUT_AF_OD             0x00000007u     //Alternate function output Open-drain mode
#define GPIO_Mode_AF_INPUT                 0x00000008u     //Alternate function input mode


//@ref GPIO_output_speed_define
#define GPIO_output_speed_10M               0x00000001u        //Output mode, max speed 10 MHz
#define GPIO_output_speed_2M                0x00000002u        //Output mode, max speed 2 MHz
#define GPIO_output_speed_50M                0x00000003u        //Output mode, max speed 50 MHz


/*
 * ====================================================================================================
 *                          APIs Supported by "MCAL GPIO DRIVER"
 * ====================================================================================================
 */
void MCAL_GPIO_Init (GPIO_TypeDef * GPIOx , GPIO_PinConfig_t* Pinconfig);
void MCAL_GPIO_DeInit (GPIO_TypeDef * GPIOx);

uint8_t MCAL_GPIO_ReadPin (GPIO_TypeDef * GPIOx , uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPORT (GPIO_TypeDef * GPIOx);

void MCAL_GPIO_WritePin (GPIO_TypeDef * GPIOx , uint16_t PinNumber , uint8_t value);
void MCAL_GPIO_WritePORT (GPIO_TypeDef * GPIOx , uint16_t value);

void MCAL_GPIO_TogglePin (GPIO_TypeDef * GPIOx , uint16_t PinNumber);
uint8_t MCAL_GPIO_LockPin (GPIO_TypeDef * GPIOx , uint16_t PinNumber);
#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
