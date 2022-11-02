/*
 * pressureSensor_Driver.c
 *
 *  Created on: Oct 26, 2022
 *      Author: manal
 */
#include "pressureSensor.h"
#include "driver.h"
/*int US_Get_distance_random (int l ,int r , int count)
{
	//generate random number from l to r
	int i ;
	for(i=0 ; i< count ; i++)
	{
		int rand_num = (rand() % (r-l+1))+l;
		return rand_num ;
	}

}*/
int psVAL = 0;
void (*PS_block)();

enum {
	reading ,
	waiting
}ps_state_id;

void pressure_init()
{
	//printf ("pressure sensor init\n");
	PS_block = STATE(_reading_);
}

 STATE_define(_reading_)
{
	ps_state_id = reading ;
	psVAL = getPressureVal() ;//US_Get_distance_random (15,25, 1); //
	//printf("perssure sensor reading value %d \n",psVAL);
	set_Pressure_VAL(psVAL);
	Delay(800);
	PS_block = STATE(_waiting_);

}
 STATE_define(_waiting_)
{
	ps_state_id = waiting;
	//printf("perssure sensor start waiting\n");
	Delay(10000);
	//printf("perssure sensor waiting end\n");
	PS_block = STATE(_reading_);
}
