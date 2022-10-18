/*
 * main.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Manal
 */

#include "C:\WS_EmbDip\ECLIPSE_WS_2\FIFO_Buffer\fifo.h"
element_type uart_buffer[width1];

int main ()
{

	FIFO_Buf_t FIFO_UART  ;
	element_type i , temp=0 ;
	if( FIFO_init(&FIFO_UART , uart_buffer, width1 ) == FIFO_no_error )
		printf ("fifo init --------- Done\n");

	for(i=0 ; i<7 ; i++)
	{
		printf("FIFO Enqueue (%x)\n",i);
		if (FIFO_enqueue(&FIFO_UART, i)== FIFO_no_error)
			printf ("\tfifo Enqueue --------- Done\n");
		else
			printf ("\tfifo Enqueue --------- failed\n");
	}
	FIFO_Print(&FIFO_UART);

	if (FIFO_dequeue(&FIFO_UART, &temp )== FIFO_no_error)
		printf ("\tfifo Dequeue %x --------- Done\n",temp);
	if (FIFO_dequeue(&FIFO_UART, &temp )== FIFO_no_error)
		printf ("\tfifo Dequeue %x --------- Done\n",temp);

	FIFO_Print(&FIFO_UART);

return 0 ;

}
