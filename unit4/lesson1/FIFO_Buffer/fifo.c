/*
 * fifo.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Manal
 */
#include "C:\WS_EmbDip\ECLIPSE_WS_2\FIFO_Buffer\fifo.h"

//FIFO APIS
FIFO_Buf_status FIFO_init(FIFO_Buf_t* fifo , element_type* buf , uint32_t length)
{

	//buf is vaild
	if(buf == NULL)
	{
		return FIFO_null;
	}
	else
	{
	fifo->base = buf ;
	fifo->head = buf ;
	fifo->tail = buf ;
	fifo->length = length;
	fifo->count = 0 ;
	return FIFO_no_error ;
	}
}
FIFO_Buf_status FIFO_enqueue(FIFO_Buf_t* fifo , element_type item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	if (FIFO_IS_FULL(fifo) == FIFO_full)
		return FIFO_full;
	*(fifo->head) = item;
	fifo->count ++;
	//circular fifo
	if(fifo->head == (fifo->base + ((fifo->length) * sizeof(element_type))))
		fifo->head = fifo->base ;
	else
	fifo->head ++;
	return FIFO_no_error ;

}
FIFO_Buf_status FIFO_dequeue(FIFO_Buf_t* fifo , element_type* item)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	//check fifo is empty
	if (fifo->count == 0)
		return FIFO_empty;
	*item = *(fifo->tail) ;
	fifo->count --;
	//circular fifo
	if(fifo->tail == (fifo->base + (fifo->length) * sizeof(element_type)))
		fifo->tail = fifo->base ;
	fifo->tail ++;
	return FIFO_no_error ;

}
FIFO_Buf_status FIFO_IS_FULL(FIFO_Buf_t* fifo)
{
	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;
	if(fifo->count == fifo->length)
		return FIFO_full;
	return FIFO_no_error;
}
void FIFO_Print(FIFO_Buf_t* fifo) // print from tail to head without any change in fifo
{
	element_type* temp;
	int i ;
	if (fifo->count == 0)
	{
		printf("fifo is empty \n");
	}
	else{
		temp = fifo->tail;
		printf("\n =========fifo print=========\n");
		for(i=0 ; i<fifo->count ; i++)
		{
			printf(" \t %x \n  ", *temp);
			temp++;
		}
		printf("\n ==================\n");
	}




}
