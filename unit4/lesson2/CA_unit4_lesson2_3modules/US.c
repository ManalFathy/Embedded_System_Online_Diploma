/*
 * US.c
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\US.h"
enum {
	US_busy
}US_state_id;
//variables --hidden
int US_distance =0 ;
//state pointer to function
 void (*US_state)();
int US_Get_distance_random (int l ,int r , int count);
void US_init()
{
	//init us driver
	printf("US_Init \n");
}

STATE_define(US_busy)
{
	//state_Name
	US_state_id = US_busy ;

	//state_Action
	//DC_Motor (speed)
	US_distance =US_Get_distance_random(45 ,55 ,1);

	printf("US_waiting state : distance =%d  \n",US_distance);
	US_Set_distance(US_distance);
	US_state = STATE(US_busy);
}


int US_Get_distance_random (int l ,int r , int count)
{
	//generate random number from l to r
	int i ;
	for(i=0 ; i< count ; i++)
	{
		int rand_num = (rand() % (r-l+1))+l;
		return rand_num ;
	}

}
