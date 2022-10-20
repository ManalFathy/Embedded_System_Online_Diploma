/*
 * CA.h
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#ifndef US_H_
#define US_H_
#include "C:\WS_EmbDip\ECLIPSE_WS_2\CA_unit4_lesson2_3modules\state.h"
//define states


//declare states functions CA
STATE_define(US_busy);
//state pointer to function
extern void (*US_state)();
void US_init();


#endif /* US_H_ */
