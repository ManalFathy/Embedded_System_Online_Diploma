/********************************************************************
 * Automatically generated by ARUnit
 * Filename: ARUnit_DoorSensorAbstractionSWC_.c
 * Generated on: Wed May 17 13:3:22 EDT
 ********************************************************************/

#include "string.h"
#include "ARUnit_DoorSensorAbstractionSWC.h"


extern const Rte_CDS_DoorSensorAbstractionSWC Rte_Instance_DoorSensorAbstractionSWC;
extern const Rte_CDS_DoorSensorAbstractionSWC * const Rte_Inst_DoorSensorAbstractionSWC;




DECLSPEC_EXPORT void ARUnit_IWrite_DoorSensorAbstractionSWC_ReadDoorSensor_PP_SRI_DoorState(myuint8 DoorState)
{
		(Rte_Inst_DoorSensorAbstractionSWC)->ReadDoorSensor_PP_SRI_DoorState->value = DoorState;
}
DECLSPEC_EXPORT myuint8* ARUnit_IWriteRef_DoorSensorAbstractionSWC_ReadDoorSensor_PP_SRI_DoorState(void)
{
	return &(Rte_Inst_DoorSensorAbstractionSWC)->ReadDoorSensor_PP_SRI_DoorState->value;
}
DECLSPEC_EXPORT myuint8 ARUnit_IRead_DoorSensorAbstractionSWC_ReadDoorSensor_PP_SRI_DoorState(void)
{
	return (Rte_Inst_DoorSensorAbstractionSWC)->ReadDoorSensor_PP_SRI_DoorState->value;
}
DECLSPEC_EXPORT Std_ReturnType ARUnit_Trigger_DoorSensorAbstractionSWC_Led_Switch_runnable(myuint8 LedState)
{
	return Led_Switch_runnable(LedState);
}


DECLSPEC_EXPORT void ARUnit_Trigger_DoorSensorAbstractionSWC_ReadDoorSensor_runnable(void)
{
	ReadDoorSensor_runnable();
}
