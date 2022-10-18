/*
 * main.c
 *
 *  Created on: Oct 11, 2022
 *      Author: manal
 */
#include "C:\WS_EmbDip\ECLIPSE_WS\LIFO_Buffer\lifo.h"

unsigned int buffer1[5];// 5*4=20byte stored in data memory


int main()
{
	int i , temp=0 ;
 LIFO_Buf_t uart_lifo , I2C_lifo;

LIFO_init(&uart_lifo, buffer1 , 5);//static allocation

unsigned int buffer2 = (unsigned int*)malloc(5 * sizeof(unsigned int));// dynamic allocation stored in heap
LIFO_init(&I2C_lifo, buffer2 , 5);

for( i=0 ; i<5 ; i++)
{
	if( LIFO_Add_item(&uart_lifo, i) == LIFO_No_error)
	printf ("Uart Lifo Add: %d \n",i);
}
for( i=0 ; i<5 ; i++)
{
	if (LIFO_get_item(&uart_lifo, &temp) == LIFO_No_error)
	printf ("Uart Lifo get: %d \n",temp);
}




return 0;

}
