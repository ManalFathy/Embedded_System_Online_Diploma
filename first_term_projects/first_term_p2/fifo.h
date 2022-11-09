/*
 * fifo.h
 *
 *  Created on: Oct 13, 2022
 *      Author: Manal
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "fun_hed.h"

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"

//USER Configration
//select the element type (uint8_t , uint16_t,..)
//create buffer
#define element_type struct sinfo
#define width1 (55)


//FIFO Data types
typedef struct {
	unsigned int length ;
	unsigned int count ;
	element_type *base;// start of buffer
	element_type *head;// the space that will add in it
	element_type *tail;// element that will get from it

}FIFO_Buf_t;

typedef enum {
	FIFO_no_error,
	FIFO_full,
	FIFO_empty,
	FIFO_null,
FIFO_searchNotFound
}FIFO_Buf_status;

//FIFO APIS
FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo , element_type* buf , uint32_t length);
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo , element_type item);
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo , element_type* item);
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t* fifo);
void FIFO_Print(FIFO_Buf_t* fifo);
void Display_element(element_type* temp);
FIFO_Buf_status FIFO_findRN(FIFO_Buf_t* fifo ,element_type* item, int id );
FIFO_Buf_status FIFO_findFN(FIFO_Buf_t* fifo , char name[10] );
FIFO_Buf_status FIFO_findcid(FIFO_Buf_t* fifo , int id );
FIFO_Buf_status FIFO_delRN(FIFO_Buf_t* fifo , int id );

#endif /* FIFO_H_ */
