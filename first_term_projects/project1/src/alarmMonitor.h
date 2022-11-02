/*
 * alarmMonitor.h
 *
 *  Created on: Oct 25, 2022
 *      Author: ayman
 */

#ifndef ALARMMONITOR_H_
#define ALARMMONITOR_H_
#include "state.h"

extern void (*AM_block)();
void alarm_init();
 STATE_define(alarmOFF);
void high_Pressure_detected();
 STATE_define(alarmON);
 STATE_define(alarmWAIT);

#endif /* ALARMMONITOR_H_ */
