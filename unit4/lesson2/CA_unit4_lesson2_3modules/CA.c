/*
 * CA.c
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\CA.h"
enum {
	CA_waiting,
	CA_driving
}CA_state_id;
//variables --hidden
int CA_speed =0 ;
int CA_distance =0 ;
int CA_threshold =50 ;

//state pointer to function
void (*CA_state)();


void US_Set_distance(int d)
{
	CA_distance = d;
	(CA_distance <= CA_threshold)? (CA_state =STATE(CA_waiting)) : (CA_state =STATE(CA_driving));
	printf("US---------distance=%d-------->CA \n",CA_distance);

}
STATE_define(CA_waiting)
{
	//state_Name
	CA_state_id = CA_waiting ;
	CA_speed =0 ;
	printf("CA_waiting state : distance =%d speed =%d \n",CA_distance ,CA_speed);

	//state_Action
	//DC_Motor (speed)

	DC_motor(CA_speed);

	}
STATE_define(CA_driving)
{
	//state_Name
	CA_state_id = CA_driving ;
	printf("CA_driving state : distance =%d speed =%d \n",CA_distance ,CA_speed);

	//state_Action
	//DC_Motor (speed)
	CA_speed =30 ;
	DC_motor(CA_speed);

}


