/*
 * alarmMonitor.c
 *
 *  Created on: Oct 25, 2022
 *      Author: manal
 */
#include "alarmMonitor.h"
#include "driver.h"
enum{
	alarm_on ,
	alarm_off ,
	alarm_wait
}AM_state_id;

void (*AM_block)();
void alarm_init()
{
	//printf("alarm monitor init \n ");
	Set_Alarm_actuator(1);
	AM_block = STATE(alarmOFF);
}
 STATE_define(alarmOFF)
{
	// printf("alarm monitor send off \n");
	AM_state_id = alarm_off;
	Set_Alarm_actuator(1); // stop alarm
}
void high_Pressure_detected()
{
	AM_block = STATE(alarmON);
}

 STATE_define(alarmON)
{
	 //printf("alarm monitor send on \n");
	AM_state_id = alarm_on ;
	Set_Alarm_actuator(0);//
	AM_block = STATE(alarmWAIT);
}
 STATE_define(alarmWAIT)
{
	// printf("alarm monitor start wait 60s\n");
	AM_state_id = alarm_wait ;
	Delay(60);
	//Set_Alarm_actuator(1);
	//printf("alarm monitor end wait 60s\n");
	AM_block = STATE(alarmOFF);

}
