/*
 * fifo.h
 *
 *  Created on: Oct 13, 2022
 *      Author: Manal
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdio.h"
#include "stdint.h"

//USER Configration
//select the element type (uint8_t , uint16_t,..)
//create buffer
#define element_type uint8_t
#define width1 (5)


//FIFO Data types
typedef struct {
	unsigned int length ;
	unsigned int count ;
	element_type* base;// start of buffer
	element_type* head;// the space that will add in it
	element_type* tail;// element that will get from it

}FIFO_Buf_t;

typedef enum {
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null
}FIFO_Buf_status;

//FIFO APIS
FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo , element_type* buf , uint32_t length);
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo , element_type item);
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo , element_type* item);
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t* fifo);
void FIFO_Print(FIFO_Buf_t* fifo);

#endif /* FIFO_H_ */
