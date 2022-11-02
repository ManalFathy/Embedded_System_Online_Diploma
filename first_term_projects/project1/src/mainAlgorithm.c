/*
 * mainAlgorithm.c
 *
 *  Created on: Oct 25, 2022
 *      Author: manal
 *
 */
#include "mainAlgorithm.h"
int p =0;
void (*MA_block)();
void set_Pressure_VAL(int p)
{

	if (p > threshold)
	{
		//printf("main algorithm high p sending %d \n",p);
		high_Pressure_detected();

	}
	else
	{
	//printf("main algorithm low p %d \n",p);
	}
	// MA_block = set_Pressure_VAL ;

}


