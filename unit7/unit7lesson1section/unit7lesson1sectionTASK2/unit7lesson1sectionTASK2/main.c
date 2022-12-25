/*
 * unit7lesson1sectionTASK2.c
 *
 * Created: 12/23/2022 5:09:53 PM
 * Author : manal
 */ 


#include "MemoryMap.h"
#include "Utels.h"
#define F_CPU 8000000UL
#include <util/delay.h>

int main(void)
{
	unsigned char f =0;
	//Set PD5 PD6 PD7 AS Output
	SetBit(DDRD,5);
	SetBit(DDRD,6);
	SetBit(DDRD,7);
	

    while (1) 
    {
		if(ReadBit(PIND,0)==1)//PRess the PDR button
		{
			if (f==0)
			{
				SetBit(PORTD,5);
				_delay_ms(1000);
				f++;	
			}
			else if (f==1)
			{
				SetBit(PORTD,6);
				_delay_ms(1000);
				f++;	
			}
			else if (f==2)
			{
				SetBit(PORTD,7);
				_delay_ms(1000);
				f++;
			}
			else if (f==3)
			{
				ClearBit(PORTD,5);
				ClearBit(PORTD,6);
				ClearBit(PORTD,7);
				f=0;
				_delay_ms(1000);
			}
			
		}
	}
		
}

