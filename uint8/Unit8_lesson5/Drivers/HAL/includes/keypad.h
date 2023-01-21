/*
 * keypad.h
 *
 * Created: 12/26/2022 10:25:04 PM
 *  Author: manal
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//#define F_CPU 8000000UL
#include "stm32f103x6.h"
#include "Stm32_F103C6_gpio_driver.h"
#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4
#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8

#define KEYPAD_PORT GPIOB
GPIO_PinConfig_t pinconfig ;

void Keypad_init();
char Keypad_getkey();



#endif /* KEYPAD_H_ */
