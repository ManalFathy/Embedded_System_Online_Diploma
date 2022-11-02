#ifndef STATE_H_
#define STATE_H_
#include "stdio.h"
#include "stdlib.h"

//automatic state function generated
#define STATE_define(_statFUN_) void ST_##_statFUN_()
#define STATE(_statFUN_)  ST_##_statFUN_

//states connections
void set_Pressure_VAL(int psVAL);
void high_Pressure_detected();
void Set_Alarm_actuator(int i);

#endif /* STATE_H_ */
