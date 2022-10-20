/*
 * CA.c
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\unit4_lesson2_CA_V1\CA.h"
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
int US_Get_distance_random (int l ,int r , int count);

STATE_define(CA_waiting)
{
	//state_Name
	CA_state_id = CA_waiting ;

	//state_Action
	//DC_Motor (speed)
	CA_speed =0 ;

	//state_check
	//us_get_distance(distance)
	CA_distance =US_Get_distance_random(45 ,55 ,1);
	(CA_distance <= CA_threshold)? (CA_state =STATE(CA_waiting)) : (CA_state =STATE(CA_driving));
	printf("CA_waiting state : distance =%d speed =%d \n",CA_distance ,CA_speed);
}
STATE_define(CA_driving)
{
	//state_Name
	CA_state_id = CA_driving ;

	//state_Action
	//DC_Motor (speed)
	CA_speed =30 ;

	//state_check
	//us_get_distance(distance)
	CA_distance =US_Get_distance_random(45 ,55 ,1);
	(CA_distance <= CA_threshold)? (CA_state =STATE(CA_waiting)) : (CA_state =STATE(CA_driving));
	printf("CA_driving state : distance =%d speed =%d \n",CA_distance ,CA_speed);

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
