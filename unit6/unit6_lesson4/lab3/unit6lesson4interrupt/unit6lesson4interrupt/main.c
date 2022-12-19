

/*
 * main.c
 *
 *  Created on: Dec 16, 2022
 *      Author: manal
 */
#define F_CPU 8000000ul
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

/*
//Register addresses
#define BASE  0x20

//PORT D
#define PORTD    *((volatile uint32_t *)(BASE+0x12))
#define DDRD    *((volatile uint32_t *)(BASE+0x11))


//PORT B
#define PORTB    *((volatile uint32_t *)(BASE+0x18))
#define DDRB    *((volatile uint32_t *)(BASE+0x17))


#define SREG    *((volatile uint32_t *)(BASE+0x3F))
#define GICR    *((volatile uint32_t *)(BASE+0x3B))
#define MCUCR     *((volatile uint32_t *)(BASE+0x35))
#define MCUCSR     *((volatile uint32_t *)(BASE+0x34))
#define GIFR     *((volatile uint32_t *)(BASE+0x3A))
*/

int main()
{
	//PORTD PD2 INT0 input direction
	//DDRD  &= ~(1<<2);

	//PORTD PD3 INT1 input direction
	//DDRD  &= ~(1<<3);

	//PORTB PB2 INT2 input direction
	//DDRB  &= ~(1<<2);

	//PORTD PD5 PD6 PD7 output direction for leds
	DDRD  |= (0b111<<5);


	//enable global irq
	//SREG |= (1<<7);
	sei();

	//set general interrupt control register to enable INT0 INT1 INT2
	GICR |= (0b111<<5);

	//the logical change trigger for INT0
	//	Any logical change generates an interrupt request
	MCUCR |= (1<<0);
	MCUCR &= ~(1<<1);

	//the logical change trigger for INT1
	//a rising edge generates an interrupt request
	MCUCR |= (0b11<<2);

	//the logical change trigger for INT2
	//a falling edge generates an interrupt request
	MCUCSR &= ~(1<<6);


	while(1)
	{
		PORTD &= ~(1<<5);
		PORTD &= ~(1<<6);
		PORTD &= ~(1<<7);
		
	}
}

ISR(INT0_vect)
{
	//toggle led
	PORTD |=(1<<5);
	_delay_ms(500);
	
	//GIFR |=(1<<6);
}
ISR(INT1_vect)
{
	PORTD |=(1<<6);
	_delay_ms(500);

	//GIFR |=(1<<7);
}
ISR(INT2_vect)
{
	PORTD |=(1<<7);
	_delay_ms(500);
	
	//GIFR |=(1<<5);
}
