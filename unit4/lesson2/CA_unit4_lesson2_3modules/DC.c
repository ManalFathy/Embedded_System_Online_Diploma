/*
 * DC.c
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\DC.h"
enum {
	DC_idle,
	DC_busy
}DC_state_id;
//variables --hidden
int DC_speed =0 ;

//state pointer to function
void (*DC_state)();
void DC_init()
{
	//init pwm
	printf("DC_init \n");
}
void DC_motor(int s)
{
	DC_speed =s ;
	DC_state = STATE(DC_busy);
	printf("CA---------speed=%d-------->DC \n",DC_speed);
}

STATE_define(DC_idle)
{
	//state_Name
	DC_state_id = DC_idle ;

	//state_Action
	//call pwm to make speed = DC_speed
	//DC_Motor (speed)
	DC_speed =0 ;
	printf("DC_idle state : speed =%d \n",DC_speed);
	DC_state = STATE(DC_idle);

}
STATE_define(DC_busy)
{
	//state_Name
	DC_state_id = DC_busy ;

	//state_Action
	//DC_Motor (speed)
	DC_speed =30 ;
	printf("DC_busy state : speed =%d \n",DC_speed);
DC_state = STATE(DC_idle);

}


