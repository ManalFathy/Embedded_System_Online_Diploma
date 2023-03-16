/*
 * CortexMX_OS_porting.c
 *
 *  Created on: Mar 10, 2023
 *      Author: Manal
 */

#include "CortexMX_OS_porting.h"


void HardFault_Handler (void)
{
	while(1);

}
void	MemManage_Handler(void)
{
	while(1);

}
void	BusFault_Handler(void)
{
	while(1);

}
void	UsageFault_Handler(void)
{
	while(1);

}

__attribute ((naked))void SVC_Handler() //naked function >>there is no created stack
{
	__asm("tst lr , #4 \n\t" //check bit 2(4=100) in LR (EXC.Return Code)--> 1 MSP stack \ 0 PSP stack
			"ITE EQ \n\t"
			"mrseq r0 , MSP \n\t"
			"mrsne r0 , PSP \n\t"
			"B OS_SVC");
}


HW_init()
{
	//initialize clock tree (RCC ->systick timer &CPU) 8 MHZ
	//8MHZ
	//1 count -> 0.125 us
	//x count  -> 1 ms
	//x = 8000 count

	//decrease PendSV interrupt priority to be smaller than or equal SYSTICK timer
	//SYSTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn , 15);
}

void trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;
}


void Start_Ticker()
{
	//initialize clock tree (RCC ->systick timer &CPU) 8 MHZ
	//8MHZ
	//1 count -> 0.125 us
	//x count  -> 1 ms
	//x = 8000 count

	SysTick_Config(8000);

}

void SysTick_Handler()
{
	MYRTOS_Update_TasksWaitingTime();
	SYStickLed ^= 1 ;
	//decide whats next
	Decide_whatNext();

	//switch context
	trigger_OS_PendSV();
}
