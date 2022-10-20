/*
 * main.c
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\CA.h"
#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\US.h"
#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\DC.h"

void setup ()
{
	//init all the drivers
	//init IRQ ...
	//init HAL US_Driver DC_Driver
	//init block
	US_init();
	DC_init();
//set states pointers for each block
	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);

}

int main()
{
 setup();
while(1)
{
	volatile int d;
	//call state for each block
	US_state();
	CA_state();
	DC_state();
	//delay
	for(d=0 ; d<=1000 ; d++);
}

return 0 ;
}
