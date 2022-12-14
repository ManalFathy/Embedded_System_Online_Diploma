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



#include <stdint.h>
#include <stdlib.h>
extern void H_fault_Handler()
{
}
typedef volatile unsigned int vint32_t;
#define RCC_BASE    0x40021000
#define PorTA_BASE  0x40010800

#define RCC_APB2ENR *((volatile uint32_t *)(RCC_BASE+0x18))
#define GPIO_ODR    *((volatile uint32_t *)(PorTA_BASE+0x0c))
#define GPIO_CRH    *((volatile uint32_t *)(PorTA_BASE+0x04))

typedef union{
	vint32_t all_feilds;
	struct{
		vint32_t reserved:13;
		vint32_t pin13:1;

	}pin;
}R_ODR_t;
volatile R_ODR_t* R_ODR = (volatile R_ODR_t*)(PorTA_BASE+0x0c);
unsigned char g_variabels[3]={1,2,3};
unsigned char const const_variabels[3]={1,2,3};
unsigned char bss_var[3];


void* _sbrk(int incr)
{
	static unsigned char* heap_ptr = NULL;
	unsigned char* prev_heap_ptr = NULL;
	extern unsigned int _E_bss; // symbol
	extern unsigned int _heap_End; // symbol
	// first time initialized
	if(heap_ptr == NULL)
		heap_ptr = (unsigned char*)&_E_bss;
	
	prev_heap_ptr = heap_ptr;
	//protect stack
	if((heap_ptr + incr) > (unsigned char*)&_heap_End)
	return (void*)NULL;
    //bokking incr size
	heap_ptr += incr;
	
	return (void*) prev_heap_ptr;
	
	
}


int main(void)
{
	int* p = (int*)malloc(4);// allocate 4 bytes
	free(p); 
	RCC_APB2ENR |= (1<<2);
	GPIO_CRH &=0xFF0FFFFF;
	GPIO_CRH |=0x00200000;

	while(1)
	{
		int i;
		//GPIO_ODR |= 1<<13; //Set bit 13
		R_ODR->pin.pin13 = 1;
		for( i=0;i<5000;i++);
		//GPIO_ODR &=(~ (1<<13));
		R_ODR->pin.pin13 = 0;
		for( i=0;i<5000;i++);
	}
			return 0;
		}


