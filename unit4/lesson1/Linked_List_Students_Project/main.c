/*
 * main.c
 *
 *  Created on: Oct 15, 2022
 *      Author: Manal
 */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
//#include "conio.h"
#define DPRINTF(...) { fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__);\
		fflush(stdout); \
		fflush(stdin); }
#define DSCANF(...) { fflush(stdout); \
		fflush(stdin); \
		scanf(__VA_ARGS__);\
		fflush(stdout); \
		fflush(stdin); }
//effective data
struct Sdata
{
	int ID;
	char name[40];
	float height ;
};
//linked list node
struct SStudent
{
	struct Sdata student;
	struct SStudent* PNestStudent ;
};

struct SStudent* gpFirstStudent = NULL ;

void AddStudent ()
{
	struct SStudent* pNewStudent ;
	struct SStudent* pLastStudent ;
	char temp_text[40];
	//check if list is empty == NULL
	if (gpFirstStudent == NULL)
	{
		//create new record
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		gpFirstStudent = pNewStudent ;
	}
	else //list have a records
	{ // navigate until reach to the last record
		pLastStudent =gpFirstStudent ;
		while (pLastStudent->PNestStudent)
			pLastStudent = pLastStudent->PNestStudent ;
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		pLastStudent->PNestStudent = pNewStudent ;
	}
	DPRINTF("\n Enter the ID :");
	gets(temp_text);
	pNewStudent-> student.ID = atoi(temp_text) ; // fill new record

	DPRINTF("\n Enter the student full name :");
	gets(pNewStudent-> student.name);

	DPRINTF("\n Enter the height :");
	gets(temp_text);
	pNewStudent-> student.height = atof(temp_text) ;

	pNewStudent->PNestStudent = NULL ; //set next pointer of new student to null
}

int delete_student()
{
	char temp_text[40];
	unsigned int selected_id ;
	//get the selected id

	DPRINTF("\n Enter the student ID to be deleted :");
	gets(temp_text);
	selected_id = atoi(temp_text);

	if(gpFirstStudent) //list is not empty
	{
		struct SStudent* pSelectedStudent = gpFirstStudent ;
		struct SStudent* pPrevStudent = NULL ;
		while(pSelectedStudent) //loop on all records
		{
			if(pSelectedStudent->student.ID == selected_id)//compare each node with selected id
			{
				if (pPrevStudent) // the first is not the selected one
				{
					pPrevStudent->PNestStudent = pSelectedStudent->PNestStudent;
				}
				else // 1st student == ID
				{
					gpFirstStudent = pSelectedStudent->PNestStudent ;

				}
				free(pSelectedStudent);
				return 1 ;

			}
			pPrevStudent = pSelectedStudent ;
			pSelectedStudent = pSelectedStudent->PNestStudent ;

		}

	}
	DPRINTF("\n cannot find student ID");
	return 0 ;

}

void view_students()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	int count = 0;

	if(gpFirstStudent == NULL)
	{
		DPRINTF("\n empty list");
	}
	else
	{
		while(pCurrentStudent)
		{
			DPRINTF("\n record number %d ", count+1);
			DPRINTF("\n\t ID %d ", pCurrentStudent->student.ID);
			DPRINTF("\n\t Name %s ", pCurrentStudent->student.name);
			DPRINTF("\n\t Height %f ", pCurrentStudent->student.height);
			pCurrentStudent = pCurrentStudent->PNestStudent;
			count++;
		}

	}

}
void DeleteAll()
{

	struct SStudent* pCurrentStudent = gpFirstStudent;


	if(gpFirstStudent == NULL)
	{
		DPRINTF("\n empty list");
	}
	else
	{
		while(pCurrentStudent)
		{
			struct SStudent* ptempStudent = pCurrentStudent;
			pCurrentStudent = pCurrentStudent->PNestStudent;
			free(ptempStudent);
		}
		gpFirstStudent = NULL ;

	}

}

int get_student()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	char temp_text[40];
	int index, count = 1;
	DPRINTF("\n enter the student index");
	gets(temp_text);
	index = atoi(temp_text);

	if(gpFirstStudent == NULL)
	{
		DPRINTF("\n empty list");
		return 0 ;
	}
	else
	{
		while(pCurrentStudent)
		{
			if(count == index)
			{
				DPRINTF("\n\t ID %d ", pCurrentStudent->student.ID);
				DPRINTF("\n\t Name %s ", pCurrentStudent->student.name);
				DPRINTF("\n\t Height %f ", pCurrentStudent->student.height);
				return 1 ;
			}
			else{
				count++;
				pCurrentStudent = pCurrentStudent->PNestStudent;
			}
		}

		DPRINTF("\n index not found");
		return 0;
	}
}
void get_length()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	int count =0;
	while(pCurrentStudent)
	{
		count++;
		pCurrentStudent = pCurrentStudent->PNestStudent;
	}

	DPRINTF("\n the list length : %d", count);
}
void get_student_fromEND()
{
	struct SStudent* pCurrentStudent = gpFirstStudent;
	struct SStudent* pEndStudent = gpFirstStudent;
	char temp_text[40];
	int i,index;
	DPRINTF("\n enter the student index");
	gets(temp_text);
	index = atoi(temp_text);
	for(i=1 ; i<index ;i++) // make 2 pointers seprated with the index
	{
		pEndStudent = pEndStudent->PNestStudent;
	}
	while(pEndStudent->PNestStudent) // make the second pointer reach until the end
	{
		pEndStudent = pEndStudent->PNestStudent;
		pCurrentStudent = pCurrentStudent->PNestStudent;
	}
	DPRINTF("\n\t ID %d ", pCurrentStudent->student.ID);
	DPRINTF("\n\t Name %s ", pCurrentStudent->student.name);
	DPRINTF("\n\t Height %f ", pCurrentStudent->student.height);
}
void middleOFList()
{
	struct SStudent* pFastStudent = gpFirstStudent;
	struct SStudent* pSlowStudent = gpFirstStudent;
	while(pFastStudent->PNestStudent)
	{
		pFastStudent = pFastStudent->PNestStudent;
		pFastStudent = pFastStudent->PNestStudent;
		pSlowStudent = pSlowStudent->PNestStudent;
	}
	DPRINTF("\n\t ID %d ", pSlowStudent->student.ID);
	DPRINTF("\n\t Name %s ", pSlowStudent->student.name);
	DPRINTF("\n\t Height %f ",pSlowStudent->student.height);

}
void reverse_StudentList()
{
	struct SStudent* pprevStudent = NULL;
	struct SStudent* pcurrentStudent = gpFirstStudent;
	struct SStudent* pnextStudent = NULL;
	while (pcurrentStudent != NULL)
	{
		pnextStudent = pcurrentStudent->PNestStudent;
		pcurrentStudent->PNestStudent= pprevStudent;
		pprevStudent = pcurrentStudent;
		pcurrentStudent = pnextStudent;
	}
	gpFirstStudent= pprevStudent;
	view_students();
}

int main()
{
	char temp_text[40];
	while(1)
	{
		DPRINTF("\n===============");
		DPRINTF("\n\t choose on the following options :\n");
		DPRINTF("\n 1:AddStudent");
		DPRINTF("\n 2:delete_student");
		DPRINTF("\n 3:view_students");
		DPRINTF("\n 4:DeleteAll");
		DPRINTF("\n 5:get student information by index from the start");
		DPRINTF("\n 6:get student information by index from the end");
		DPRINTF("\n 7:get list length");
		DPRINTF("\n 8:get the middle of the list");
		DPRINTF("\n 9:reverse students list");
		DPRINTF("\n Enter option number:");

		gets(temp_text);
		DPRINTF("\n===============");
		switch(atoi(temp_text))
		{
		case 1:
			AddStudent();
			break ;
		case 2:
			delete_student();
			break ;
		case 3:
			view_students();
			break ;
		case 4:
			DeleteAll();
			break ;
		case 5:
			get_student();
			break ;
		case 6:
			get_student_fromEND();
			break ;
		case 7:
			get_length();
			break ;
		case 8:
			middleOFList();
			break ;
		case 9:
			reverse_StudentList();
			break;
		default:
			DPRINTF("WRONG OPTION");
			break;

		}
	}
	return 0 ;
}





