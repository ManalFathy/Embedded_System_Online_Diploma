/*
 * scheduler.c
 *
 *  Created on: Mar 10, 2023
 *      Author: Manal
 */



#include "Scheduler.h"
#include "My_RTOS_FIFO.h"
struct {
	Task_ref* OSTasks[100]; //SChedular table
	unsigned int _S_MSP_Task ;
	unsigned int _E_MSP_Task ;
	unsigned int PSP_Task_Locator ;
	unsigned int NoOfActiveTasks ;
	Task_ref* CurrentTask ;
	Task_ref* NextTask ;
	enum{
		OSsuspend,
		OsRunning
	}OSmodeID;
}OS_Control;


FIFO_Buf_t Ready_QUEUE ;

Task_ref* Ready_QUEUE_FIFO[100] ;
Task_ref MYRTOS_idleTask ;


__attribute ((naked)) void PendSV_Handler()
{
	//====================================
	//Save the Context of the Current Task
	//====================================
	//Get the Current Task "Current PSP from CPU register" as CPU Push XPSR,.....,R0
	OS_GET_PSP(OS_Control.CurrentTask->Current_PSP);

	//using this Current_PSP (Pointer) tp store (R4 to R11)
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r4 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r5 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r6 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r7 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r8 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r9 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r10 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP-- ;
	__asm volatile("mov %0,r11 " : "=r" (*(OS_Control.CurrentTask->Current_PSP))  );

	//save the current Value of PSP
	//already saved in Current_PSP



	//====================================
	//Restore the Context of the Next Task
	//====================================
	if (OS_Control.NextTask != NULL){
		OS_Control.CurrentTask = OS_Control.NextTask ;
		OS_Control.NextTask = NULL ;
	}

	__asm volatile("mov r11,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r10,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r9,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r8,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r7,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r6,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r5,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;
	__asm volatile("mov r4,%0 " : : "r" (*(OS_Control.CurrentTask->Current_PSP))  );
	OS_Control.CurrentTask->Current_PSP++ ;

	//update PSP and exit
	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	__asm volatile("BX LR");

}

//"wfe" wait for event (CPU will be in sleep mode until event occur (excptional or physical interrupt))
//"wfi" wait for interrupt (CPU will be in sleep mode until event occur ( physical interrupt))
//reduced power  and CPU utilization

void MYRTOS_IdleTask()
{
	while(1)
	{
		IdleTaskLed ^= 1 ;
		//__asm("NOP"); // high cpu utilization
		__asm("wfe");
	}

}








void MYRTOS_Create_MainStack()
{
	OS_Control._S_MSP_Task = &_estack;
	OS_Control._E_MSP_Task = OS_Control._S_MSP_Task - MainStackSize;
	//Aligned 8 Bytes spaces between Main Task and PSP tasks
	OS_Control.PSP_Task_Locator = (OS_Control._E_MSP_Task - 8);

	//if (_E_MSP_Task <&_eheap) Error:excedded the available stack size
}

MYRTOS_errorID MYRTOS_init()
{
	MYRTOS_errorID error = NoError ;

	//Update OS Mode (OSsuspend)
	OS_Control.OSmodeID = OSsuspend ;

	//Specify the MAIN Stack for OS
	MYRTOS_Create_MainStack();

	//Create OS Ready Queue
	if (FIFO_init(&Ready_QUEUE, Ready_QUEUE_FIFO, 100) !=FIFO_NO_ERROR)
	{
		error += Ready_Queue_init_error ;
	}

	//Configure IDLE TASK
	strcpy (MYRTOS_idleTask.TaskName, "idleTask");
	MYRTOS_idleTask.priority = 255 ;
	MYRTOS_idleTask.p_TaskEntry = MYRTOS_IdleTask ;
	MYRTOS_idleTask.Stack_Size = 300 ;

	error += MYRTOS_CreateTask(&MYRTOS_idleTask);

	return error ;

}


void MyRTOS_Create_TaskStack(Task_ref* Tref)
{

	/* Task frame
	 * ============
	 *  xPSR
	 * PC(Next task instruction which should be run)
	 * LR(return register which is saved in cpu while task running before task switching)
	 * r12
	 * r3
	 * r3
	 * r1
	 * r0

	 * ============
	 * r5,r6,r7,r8,r9,r10,r11(Saved/Restore Manually)
	 *
	 */

	Tref->Current_PSP = Tref->_S_PSP_Task ;

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = 0x01000000;         //DUMMY_XPSR should T =1 to avoid BUS fault;//0x01000000

	Tref->Current_PSP-- ;
	*(Tref->Current_PSP) = (unsigned int)Tref->p_TaskEntry ; //PC

	Tref->Current_PSP-- ; //LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP
	*(Tref->Current_PSP)  = 0xFFFFFFFD ;

	for (int  j=0 ; j< 13 ; j++ )
	{
		Tref->Current_PSP-- ;
		*(Tref->Current_PSP)  = 0 ;

	}



}
MYRTOS_errorID MYRTOS_CreateTask(Task_ref* Tref)
{
	MYRTOS_errorID error = NoError ;

	//Create Its OWN PSP stack
	//Check task stack size exceeded the PSP stack
	Tref->_S_PSP_Task = OS_Control.PSP_Task_Locator;
	Tref->_E_PSP_Task = Tref->_S_PSP_Task - Tref->Stack_Size ;

	/*
	 * _S_PSP_Task
	 * Task Stack
	 * _E_PSP_Task
	 * 8 bytes space
	 *
	 * _eheap
	 */

	//create its own PSP stack
	/*	if(Tref->_E_PSP_Task < (unsigned int)(&(_eheap)))
	{
		return Task_exceeded_StackSize ;
	}*/

	//Aligned 8 Bytes spaces between Task PSP and other
	OS_Control.PSP_Task_Locator = (Tref->_E_PSP_Task - 8);

	//Initialize PSP Task Stack
	MyRTOS_Create_TaskStack( Tref);

	//update sch Table
	OS_Control.OSTasks[OS_Control.NoOfActiveTasks]= Tref ;
	OS_Control.NoOfActiveTasks++ ;


	//update the task state to suspend mode
	Tref->TaskState = Suspend ;

	return error ;

}

//Handler
void bubbleSort()
{
	unsigned int i, j , n;
	Task_ref* temp ;
	n = OS_Control.NoOfActiveTasks ;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (OS_Control.OSTasks[j]->priority > OS_Control.OSTasks[j + 1]->priority)
			{
				temp = OS_Control.OSTasks[j] ;
				OS_Control.OSTasks[j] = OS_Control.OSTasks[j + 1 ] ;
				OS_Control.OSTasks[j + 1] = temp ;
			}

}
//Handler
void MyRTOS_Update_Schadule_tables()
{
	Task_ref* temp =NULL ;
	Task_ref* Ptask ;
	Task_ref* PnextTask ;
	int i = 0 ;

	//1- bubble sort SchTable OS_Control-> OSTASKS[100] (priority high then low)
	bubbleSort();
	//2- free Ready Queue
	while(FIFO_dequeue(&Ready_QUEUE, &temp /* pointer to pointer */)!=FIFO_EMPTY);

	//3- update ready queue

	while(i< OS_Control.NoOfActiveTasks)
	{
		Ptask = OS_Control.OSTasks[i] ;
		PnextTask = OS_Control.OSTasks[i+1] ;
		if (Ptask->TaskState != Suspend)
		{
			//in case we reached to the end of avaliable OSTASKS
			if (PnextTask->TaskState == Suspend)
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = ready ;
				break ;
			}
			//	if the Ptask priority > nexttask then (lowest number is meaning higher priority)
			if (Ptask->priority < PnextTask->priority )
			{
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = ready ;
				break ;
			}else if (Ptask->priority == PnextTask->priority)
			{
				//	if the Ptask priority == nexttask then
				//		push Ptask to ready state
				//	And make the ptask = nexttask  and nexttask++
				FIFO_enqueue(&Ready_QUEUE, Ptask);
				Ptask->TaskState = ready ;
			}else if (Ptask->priority > PnextTask->priority)
			{
				//not allowed to happen as we already reordered it by bubble sort
				break ;
			}
		}


		i++ ;
	}

}

//Handler Mode
void Decide_whatNext()
{
	//if Ready Queue is empty && OS_Control->currentTask != suspend
	if (Ready_QUEUE.counter == 0 && OS_Control.CurrentTask->TaskState != Suspend) //FIFO_EMPTY
	{
		OS_Control.CurrentTask->TaskState = Running ;
		//add the current task again(round robin)
		FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
		OS_Control.NextTask = OS_Control.CurrentTask ;
	}else
	{
		FIFO_dequeue(&Ready_QUEUE, &OS_Control.NextTask);
		OS_Control.NextTask->TaskState = Running ;
		//update Ready queue (to keep round robin Algo. happen)
		if ((OS_Control.CurrentTask->priority == OS_Control.NextTask->priority )&&(OS_Control.CurrentTask->TaskState != Suspend))
		{
			FIFO_enqueue(&Ready_QUEUE, OS_Control.CurrentTask);
			OS_Control.CurrentTask->TaskState = ready ;
		}
	}
}

//Handler Mode
void OS_SVC(int* Stack_Frame)
{
	//r0,r1,r2,r3,r12,LR,return address (PC) and XPSR
	unsigned char SVC_number ;
	SVC_number = *((unsigned char*)(((unsigned char*)Stack_Frame[6])-2)) ;

	switch (SVC_number)
	{
	case SVC_ActivateTask:
	case SVC_TerminateTask:
		//Update Sch Table, Ready Queue
		MyRTOS_Update_Schadule_tables();
		//OS is in Running State
		if (OS_Control.OSmodeID == OsRunning)
		{
			if (strcmp(OS_Control.CurrentTask->TaskName,"idleTask") != 0)
			{
				//Decide what Next
				Decide_whatNext();

				//trigger OS_pendSV (Switch Context/Restore)
				trigger_OS_PendSV();
			}
		}

		break;
	case SVC_TaskWaitingTime :
		MyRTOS_Update_Schadule_tables();
		break;

	case SVC_AquireMUTEX:

		break;

	case SVC_ReleaseMUTEX:

		break;

	}


}

//Thread Mode
MYRTOS_OS_SVC_Set(SVC_ID ID)
{
	switch (ID)
	{
	case SVC_ActivateTask:
		__asm("svc #0x00");
		break;
	case SVC_TerminateTask:
		__asm("svc #0x01");
		break;
	case SVC_TaskWaitingTime:
		__asm("svc #0x02");
		break;
	case SVC_AquireMUTEX:
		__asm("svc #0x03");
		break;
	case SVC_ReleaseMUTEX:
		__asm("svc #0x04");
				break;
	}
}

void MYRTOS_ActivateTask (Task_ref* Tref)
{
	Tref->TaskState = Waiting ;
	MYRTOS_OS_SVC_Set(SVC_ActivateTask);
}
void MYRTOS_TerminateTask (Task_ref* Tref)
{
	Tref->TaskState = Suspend ;
	MYRTOS_OS_SVC_Set(SVC_TerminateTask);
}

void MYRTOS_Taskwait(unsigned int NoTicks , Task_ref* SelfTref) // go to suspend state until no of ticks
{
	SelfTref->TimingWaiting.Blocking = Enable;
	SelfTref->TimingWaiting.Ticks_Count = NoTicks ;

	// Task should be blocked
	SelfTref->TaskState = Suspend ;
	MYRTOS_OS_SVC_Set(SVC_TerminateTask);
}


void MYRTOS_STARTOS()
{
	OS_Control.OSmodeID = OsRunning ;
	//Set Default "Current Task =Idle Task"
	OS_Control.CurrentTask = &MYRTOS_idleTask ;
	//Activate IDLE Task
	MYRTOS_ActivateTask(&MYRTOS_idleTask);
	//Start Ticker
	Start_Ticker(); // 1ms

	OS_SET_PSP(OS_Control.CurrentTask->Current_PSP);
	//Switch Thread Mode SP from MSP to PSP
	OS_SWITCH_SP_to_PSP;
	OS_SWITCH_to_UNPrivilageMode;
	MYRTOS_idleTask.p_TaskEntry();
}

void MYRTOS_Update_TasksWaitingTime()
{
	for(int i=0 ; i<OS_Control.NoOfActiveTasks ; i++ )
	{
		if(OS_Control.OSTasks[i]->TaskState == Suspend)
		{
			if(OS_Control.OSTasks[i]->TimingWaiting.Blocking == Enable )
			{
				OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count -- ;
				if(OS_Control.OSTasks[i]->TimingWaiting.Ticks_Count == 0)
				{
					OS_Control.OSTasks[i]->TimingWaiting.Blocking = Disable ;
					OS_Control.OSTasks[i]->TaskState = Waiting ;
					MYRTOS_OS_SVC_Set(SVC_TaskWaitingTime);
				}
			}
		}
	}
}



MYRTOS_errorID MYRTOS_AcquireMutex(Mutex_ref* Mref , Task_ref* Tref)
{
	if(Mref->CurrentTUser == NULL) // not taken
	{
		Mref->CurrentTUser =Tref;
	}
	else
	{
		if(Mref->NextTUser == NULL) // not pending request
		{
			Mref->NextTUser =Tref;
			Tref->TaskState = Suspend ;//wait for the Mutex
			MYRTOS_OS_SVC_Set(SVC_TerminateTask);

		}
		else //pending request by another task
		{
			return MutexReachedMAXNumberOFUsers;
		}

	}
return NoError;
}
void MYRTOS_ReleaseMutex(Mutex_ref* Mref)
{
	if(Mref->CurrentTUser != NULL)
	{
		Mref->CurrentTUser = Mref->NextTUser ;
		Mref->NextTUser = NULL;
		Mref->CurrentTUser->TaskState = Waiting ;
		MYRTOS_OS_SVC_Set(SVC_ActivateTask);
	}

}














































