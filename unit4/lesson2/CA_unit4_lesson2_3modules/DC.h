/*
 * CA.h
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#ifndef DC_H_
#define DC_H_
#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\state.h"
//define states


//declare states functions CA
STATE_define(DC_idle);
STATE_define(DC_busy);
//state pointer to function
extern void (*DC_state)();
void DC_init();


#endif /* DC_H_ */
