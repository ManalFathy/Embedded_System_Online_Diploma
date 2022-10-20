/*
 * CA.h
 *
 *  Created on: Oct 18, 2022
 *      Author: manal
 */

#ifndef CA_H_
#define CA_H_
#include "C:\WS_EmbDip\ECLIPSE_WS_2\unit4_lesson2_CA_V1\state.h"
//define states


//declare states functions CA
STATE_define(CA_waiting);
STATE_define(CA_driving);
//state pointer to function
extern void (*CA_state)();


#endif /* CA_H_ */
