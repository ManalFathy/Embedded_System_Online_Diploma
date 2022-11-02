


#include "driver.h"
#include "alarmMonitor.h"
#include "mainAlgorithm.h"
#include "pressureSensor.h"
void setup()
{
	GPIO_INITIALIZATION();
	alarm_init();
	 pressure_init();
	PS_block = STATE(_reading_);
	MA_block = set_Pressure_VAL ;
	AM_block = STATE(alarmOFF);

}
int main ()
{

	setup();
	while (1)
	{
		//Implement your Design 
		PS_block() ;
		//MA_block();
		AM_block();
Delay(100000);

	}
return 0 ;
}
