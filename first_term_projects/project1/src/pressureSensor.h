/*
 * pressureSensor.h
 *
 *  Created on: Oct 26, 2022
 *      Author: manal
 */

#ifndef PRESSURESENSOR_H_
#define PRESSURESENSOR_H_
#include "state.h"

extern void (*PS_block)();
 STATE_define(_reading_);
 STATE_define(_waiting_);

#endif /* PRESSURESENSOR_H_ */
