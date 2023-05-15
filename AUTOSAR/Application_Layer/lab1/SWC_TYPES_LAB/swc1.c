#include "RTE_SWC1.h"
void SUM()
{
std_ReturnType status = E_NOT_OK ;
unsigned short x,y ;
unsigned int z = 0 ;
status = RTE_Read_RpSum_Val1(&x);
status = RTE_Read_RpSum_Val2(&y);
z = x + y ;
status = RTE_Write_PpSum_SumResult(z);
	
}

