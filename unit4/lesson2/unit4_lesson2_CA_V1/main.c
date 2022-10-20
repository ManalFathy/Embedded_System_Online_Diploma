/*
 * main.c
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\unit4_lesson2_CA_V1\CA.h"

void setup ()
{
	//init all the drivers
	//init IRQ ...
	//init HAL US_Driver DC_Driver
	//init block
//set states pointers for each block
	CA_state = STATE(CA_waiting);

}

int main()
{
 setup();
while(1)
{
	volatile int d;
	//call state for each block
	CA_state();
	//delay
	for(d=0 ; d<=1000 ; d++);
}

return 0 ;
}
