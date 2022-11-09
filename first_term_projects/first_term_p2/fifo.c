/*
 * fifo.c
 *
 *  Created on: Oct 13, 2022
 *      Author: Manal
 */
#include "fifo.h"
#include "fun_hed.h"

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
		//printf("\n =========fifo print=========\n");
		for(i=0 ; i<fifo->count ; i++)
		{
			DPRINTF("Student %d :\n",i+1);
			DPRINTF("\t Roll number :%d \n  ", temp->roll);
			DPRINTF("\t First name :%s \n  ", temp->fname);
			DPRINTF("\t Last name :%s \n  ", temp->lname);
			DPRINTF("\t GPA :%.1f \n  ", temp->GPA);
			DPRINTF("\t course 1 id :%d \n  ", temp->cid[0]);
			DPRINTF("\t course 2 id :%d \n  ", temp->cid[1]);
			DPRINTF("\t course 3 id :%d \n  ", temp->cid[2]);
			DPRINTF("\t course 4 id :%d \n  ", temp->cid[3]);
			DPRINTF("\t course 5 id :%d \n  ", temp->cid[4]);
			temp++;
		}
		//printf("\n ==================\n");
	}

}
void Display_element(element_type* temp)
{

	DPRINTF("\t Roll number :%d \n  ", temp->roll);
	DPRINTF("\t First name :%s \n  ", temp->fname);
	DPRINTF("\t Last name :%s \n  ", temp->lname);
	DPRINTF("\t GPA :%.1f \n  ", temp->GPA);
	DPRINTF("\t course 1 id :%d \n  ", temp->cid[0]);
	DPRINTF("\t course 2 id :%d \n  ", temp->cid[1]);
	DPRINTF("\t course 3 id :%d \n  ", temp->cid[2]);
	DPRINTF("\t course 4 id :%d \n  ", temp->cid[3]);
	DPRINTF("\t course 5 id :%d \n  ", temp->cid[4]);
	DPRINTF("-----------------------------------\n  ");




}
FIFO_Buf_status FIFO_findRN(FIFO_Buf_t* fifo ,element_type* item, int id )
{
	element_type* temp;
	int i ;

	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;


	if (fifo->count == 0);
	//printf("fifo is empty \n");

	temp = fifo->tail;
	for(i=0 ; i<fifo->count ; i++)
	{
		if(temp->roll == id)
		{
			*item=*temp;
			return FIFO_no_error;
		}
		temp++;
	}

	return FIFO_searchNotFound;



}
FIFO_Buf_status FIFO_findFN(FIFO_Buf_t* fifo , char name[10] )
{
	element_type* temp;
	int i ,j=0;

	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;


	if (fifo->count == 0);
	//printf("fifo is empty \n");

	temp = fifo->tail;
	for(i=0 ; i<fifo->count ; i++)
	{
		if (strcmp(temp->fname , name) == 0)
		{

			Display_element(temp);

			j++;
		}
		temp++;
	}
	if (j== 0)
		return FIFO_searchNotFound;
	else
	{
		DPRINTF("The total number of students is \n : %d",j+1);
		return FIFO_no_error;

	}
}


FIFO_Buf_status FIFO_findcid(FIFO_Buf_t* fifo , int id )
{
	element_type* temp;
	int i,j,k=0;


	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;


	if (fifo->count == 0);
	//printf("fifo is empty \n");

	temp = fifo->tail;
	for(i=0 ; i<fifo->count ; i++)
	{
		for (j=0 ; j<5 ; j++)
		{
			if (temp->cid[j] == id)
			{

				Display_element(temp);
				k++;
				break;
			}
		}
		temp++;
	}
	if (k== 0)
		return FIFO_searchNotFound;
	else
	{
		DPRINTF("The total number of students that enrolled in course %d is : %d\n", id , k);
		return FIFO_no_error;

	}
}



FIFO_Buf_status FIFO_delRN(FIFO_Buf_t* fifo , int id )
{

	int i ,j;
/*	if(!fifo->base || !fifo->head || !fifo->tail)
		return FIFO_null;


	if (fifo->count == 0);
	return FIFO_empty;*/

	for(i=0;i<=fifo->count;i++)
	{
		if(id==(fifo->base)[i].roll)
			break;
	}
	if(i<fifo->count)
	{

		for(j=0;j<fifo->count;j++,i++)
		{
			(fifo->base)[i]=(fifo->base)[i+1];
		}
		fifo->count --;
		fifo->head --;
		DPRINTF("[INFO]The Roll number %d is deleted successfuly \n",id);
		return FIFO_no_error;
	}
	else
	{
		DPRINTF("[ERROR]The Roll number %d not found\n",id);
		return FIFO_searchNotFound;
	}


}
