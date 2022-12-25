/*
 * unit7lesson1Section.c
 *
 * Created: 12/23/2022 5:09:53 PM
 * Author : manal
 */ 


#include "MemoryMap.h"
#include "Utils.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	//Set PD5 PD6 PD7 AS Output
	SetBit(DDRD,5);
	SetBit(DDRD,6);
	SetBit(DDRD,7);

    while (1) 
    {
		
	SetBit(PORTD,5);
	_delay_ms(1000);
		SetBit(PORTD,6);
		_delay_ms(1000);
		SetBit(PORTD,7);
		_delay_ms(1000);
		ClearBit(PORTD,7);
		_delay_ms(1000);
		ClearBit(PORTD,6);
		_delay_ms(1000);
		ClearBit(PORTD,5);
		_delay_ms(1000);	
		
	}
		
}

