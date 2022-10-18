/*
 * lifo.h
 *
 *  Created on: Oct 11, 2022
 *      Author: manal
 */

#ifndef LIFO_H_
#define LIFO_H_
#include "stdio.h"
#include "stdlib.h"

//type definitions
typedef struct
{
	unsigned int length;
	unsigned int count;
	unsigned int* head;
	unsigned int* base;
}LIFO_Buf_t ;

typedef enum
{
	LIFO_No_error ,
	LIFO_full ,
	LIFO_empty,
	LIFO_Null
}LIFO_Status;


// APIS
LIFO_Status LIFO_Add_item (LIFO_Buf_t* lifo_buf , unsigned int item);
LIFO_Status LIFO_get_item (LIFO_Buf_t* lifo_buf , unsigned int* item);// item pointer to add the item in it
LIFO_Status LIFO_init (LIFO_Buf_t* lifo_buf , unsigned int* buf , unsigned int length);


#endif /* LIFO_H_ */
