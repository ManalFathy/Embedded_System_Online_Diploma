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
#include "lcd.h"
#include "keypad.h"

extern int _estack ;

#define TaskA_Stack_Size  100 //100 Bytes
#define TaskB_Stack_Size  100 //100 Bytes

//Main Stack
unsigned int _S_MSP = &_estack;
unsigned int _E_MSP ;

//Process Stack Task A
unsigned int _S_PSP_TA ;
unsigned int _E_PSP_TA ;

//Process Stack Task B
unsigned int _S_PSP_TB;
unsigned int _E_PSP_TB ;

#define OS_SET_PSP(add)              __asm volatile("mov r0 , %0 \n\t msr PSP , r0" : : "r" (add) )
#define OS_SWITCH_SP_to_PSP          __asm volatile("mrs r0,CONTROL \n\t mov r1,#0x02 \n\t orr r0,r0,r1 \n\t msr CONTROL,r0") //Set Bit 1 in CONTROL
#define OS_SWITCH_SP_to_MSP          __asm volatile("mrs r0,CONTROL \n\t mov r1,#0x05 \n\t and r0,r0,r1 \n\t msr CONTROL,r0") //Clear Bit 1 in CONTROL

#define OS_SWITCH_to_PrivilageMode    __asm volatile("mrs r3 , CONTROL \n\t lsr r3 , r3 ,#0x1 \n\t lsl r3 , r3 ,#0x1 \n\t msr CONTROL , r3")
#define OS_SWITCH_to_UNPrivilageMode    __asm volatile("mrs r3 , CONTROL \n\t orr r3 , r3 ,#0x1 \n\t msr CONTROL , r3")

#define OS_Generate_Expections       __asm volatile("SVC #0x3")

enum CpuAcessLevel {
	privileged ,
	unprivileged
};

void SVC_Handler()
{
	OS_SWITCH_to_PrivilageMode;
}

/*void SWITCH_CPU_AcessLevel(enum CpuAcessLevel  level)
{
	switch (level)
	{
	case privileged:                            //should be done in handler(privilege)mode
		//Clear Bit 0 in CONTROL Resister
		__asm("mrs r3 , CONTROL \n\t"
				"lsr r3 , r3 ,#0x1 \n\t"
				"lsl r3 , r3 ,#0x1 \n\t"
				"msr CONTROL , r3");
		break;
		break;

	case unprivileged:
		//Set Bit 0 in CONTROL Resister
		__asm("mrs r3 , CONTROL \n\t"
				"orr r3 , r3 ,#0x1 \n\t"
				"msr CONTROL , r3");
		break;
	}
}*/
void my_wait(int x)
{
	unsigned int i,j;
	for(i=0 ; i<x ; i++);
	for(j=0 ;j<255 ; j++);
}
unsigned int  TaskA_flag , TaskB_flag , IRQ_flag =0 ;

unsigned int CPU_Control_Register = 0;
unsigned int CPU_IPSR_Register = 0;

void EXTI9_Callback(void)
{

	if(IRQ_flag == 0)
	{
		IRQ_flag =1;
		TaskA_flag =1 ;
	}
	else if (IRQ_flag == 1)
	{
		TaskB_flag =1 ;
		IRQ_flag =0;
	}
	//SWITCH_CPU_AcessLevel(privileged);
}


int TaskA(int a , int b , int c )
{
	return a+b+c ;
}

int TaskB(int a , int b , int c , int d)
{
	return a+b+c ;
}
void MainOS()
{
	//Main Stack
	_E_MSP = (_S_MSP - 512); // Descending stack

	//Task A Stack
	_S_PSP_TA = (_E_MSP - 8);
	_E_PSP_TA = (_S_PSP_TA - TaskA_Stack_Size);

	//Task B Stack
	_S_PSP_TB = (_E_PSP_TA - 8);
	_E_PSP_TB = (_S_PSP_TB - TaskB_Stack_Size);

	while(1)
	{
		__asm("nop");
		if(TaskA_flag == 1)
		{    //set PSP Register = _S_PSP_TA
			OS_SET_PSP(_S_PSP_TA);
			//SP = PSP instead of MSP
			OS_SWITCH_SP_to_PSP;
			//Switch from privileged to unprivileged
			OS_SWITCH_to_UNPrivilageMode;

			TaskA_flag = TaskA(1, 2, 3) ;

			//Switch from unprivileged to privileged
			OS_Generate_Expections ;
			//SP = MSP
			OS_SWITCH_SP_to_MSP ;
		}
		else if(TaskB_flag == 1)
		{
			//set PSP Register = _S_PSP_TB
			OS_SET_PSP(_S_PSP_TB);
			//SP = PSP instead of MSP
			OS_SWITCH_SP_to_PSP;
			//Switch from privileged to unprivileged
			OS_SWITCH_to_UNPrivilageMode;

			TaskB_flag =TaskB(1, 2, 3, 4) ;
			//Switch from unprivileged to privileged
			OS_Generate_Expections;
			//SP = MSP
			OS_SWITCH_SP_to_MSP ;
		}
	}
}

int main(void)
{

	//Enable clock
	RCC_GPIOA_CLK_EN();
	RCC_GPIOB_CLK_EN();
	RCC_AFIO_CLK_EN();

	LCD_INIT();
	LCD_clear_screen();

	EXTI_Pinconfig_t EXTI_CFG ;
	EXTI_CFG.EXTI_PIN = EXTI9PB9 ;
	EXTI_CFG.Trigger_Case = EXTI_Trigger_RISING ;
	EXTI_CFG.P_IRQ_Callback = EXTI9_Callback ;
	EXTI_CFG.IRQ_EN = EXTI_IRQ_Enable ;
	MCAL_EXTI_GPIO_INIT(&EXTI_CFG);


	MainOS();

	//SWITCH_CPU_AcessLevel(unprivileged);


	while(1)
	{
		if(IRQ_flag)
		{
			LCD_clear_screen();
			IRQ_flag =0;
		}

	}













	return 0;
}
