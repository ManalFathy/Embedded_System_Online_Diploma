/*
 * implement_fun.c
 *
 *  Created on: Nov 2, 2022
 *      Author: ayman
 */
#include "fun_hed.h"
#include "fifo.h"
FIFO_Buf_t FIFO_st;


void add_student_file()
{
	char x[10],y[10];
	int z[10];
	float a ;
	int i,j ;
	element_type* st;
	FILE *fp;
	fp=fopen("input.txt" , "r");
	while (fscanf(fp,"%d",&j) == 1)
	{
		if(	FIFO_findRN(&FIFO_st ,st, j ) == FIFO_searchNotFound)
		{
			FIFO_st.head->roll = j ;
			fscanf(fp,"%s",FIFO_st.head->fname);
			fscanf(fp,"%s",FIFO_st.head->lname);
			fscanf(fp,"%f",&FIFO_st.head->GPA);
			for (i=0;i<5;i++)
			{
				fscanf(fp,"%d",&FIFO_st.head->cid[i]);
			}
			DPRINTF("[INFO]Roll number %d saved successfully\n",j);
			FIFO_st.head++;
			FIFO_st.count++;
		}
		else
		{
			DPRINTF("[ERROR]Roll number %d is already taken\n",j);
			fscanf(fp,"%s",x);
			fscanf(fp,"%s",y);
			fscanf(fp,"%f",&a);
			for (i=0;i<5;i++)
			{
				fscanf(fp,"%d",&z[i]);
			}

		}



	}
	fclose(fp);

	DPRINTF("---------------------------\n");
	tot_s();

}
void add_student_manually()
{
	int i;
	element_type stemp;
	element_type* st;

	label:	DPRINTF("Enter the roll number of student\n");
	DSCANF("%d",&stemp.roll);
	if(	FIFO_findRN(&FIFO_st ,st, stemp.roll ) != FIFO_searchNotFound)
	{
		DPRINTF("[error] this ID is taken \n");
		goto label;
	}

	DPRINTF("Enter the first name of student\n");
	DSCANF("%s",&stemp.fname);
	DPRINTF("Enter the last name of student\n");
	DSCANF("%s",&stemp.lname);
	DPRINTF("Enter the GPA of student\n");
	DSCANF("%f",&stemp.GPA);
	DPRINTF("Enter the course id of each course\n");
	for(i=0 ; i<5 ;i++)
	{
		DPRINTF("Course %d ID:",i+1);
		DSCANF("%d",&stemp.cid[i]);
	}

	FIFO_enqueue(&FIFO_st , stemp);

	DPRINTF("[info]Student Details is added successfully\n");
	DPRINTF("---------------------------------\n");
	tot_s();
}
void find_rl()
{
	int i ;
	element_type* st ;
	DPRINTF("Enter the roll number of student\n");
	DSCANF("%d",&i);
	if(	FIFO_findRN(&FIFO_st ,st, i ) == FIFO_searchNotFound)
	{
		DPRINTF("[error] this Roll number not found  \n");
	}
	else
	{
		Display_element(st);
	}

}
void find_fn()
{
	char n[10];
	DPRINTF("Enter the student first name\n");
	DSCANF("%s",n);
	if( FIFO_findFN(&FIFO_st , n )== FIFO_searchNotFound)
	{
		DPRINTF("[error] this first name not found  \n");
	}

}
void find_c()
{
	int i ;
	DPRINTF("Enter the course id \n");
	DSCANF("%d",&i);
	if( FIFO_findcid(&FIFO_st , i ) == FIFO_searchNotFound)
		DPRINTF("[error] this Course id not found  \n");
}

void tot_s()
{
	int i = FIFO_st.count;
	DPRINTF("[info]The total number of students is %d \n " , i );
	DPRINTF("[info]You can add up to 50 students  \n " );
	DPRINTF("[info]You can add %d more students \n " , (50-i) );


}
void del_s()
{
	int i ;
	element_type* st ;
	DPRINTF("Enter the roll number of student you want to delete \n");
	DSCANF("%d",&i);
	if( FIFO_delRN(&FIFO_st , i ) == FIFO_searchNotFound);

}
void up_s()
{
	int i ,id , j;
	DPRINTF("Enter the roll number of student you want to update\n");
	DSCANF("%d",&id);

	//element_type* st = FIFO_st.base;
	for(i=0;i<=FIFO_st.count;i++)
	{
		if(id ==(FIFO_st.tail)[i].roll)
			break;
	}
	if(i<=FIFO_st.count)
	{

		DPRINTF("1.Roll number \n");
		DPRINTF("2.First name \n");
		DPRINTF("3.Last name \n");
		DPRINTF("4.GPA \n");
		DPRINTF("5.courses \n");
		DSCANF("%d",&j);
		switch (j)
		{
		case 1 :

			DPRINTF("Enter the new roll number \n");
			DSCANF("%d",&((FIFO_st.tail)[i].roll));
			break ;

		case 2 :
			DPRINTF("Enter the new first name \n");
			DSCANF("%s",&((FIFO_st.tail)[i].fname));
			break ;
		case 3 :
			DPRINTF("Enter the new last name \n");
			DSCANF("%s",&((FIFO_st.tail)[i].lname));
			break ;
		case 4 :
			DPRINTF("Enter the new GPA \n");
			DSCANF("%f",&((FIFO_st.tail)[i].GPA));
			break ;
		case 5 :
			DPRINTF("Enter the new Courses ID \n");
			for(j=0 ; j <5 ; j++)
			{
				DPRINTF("Course %d : ", i+1);
				DSCANF("%d",&((FIFO_st.tail)[i].cid[j]));
			}


			break ;
		default :
			DPRINTF("WRONG OPTION");
			break;
		}

		DPRINTF("[Info] Updated Successfully \n");
	}
	else
	{

		DPRINTF("[ERROR]this ID didn't exist\n");


	}
}
void show_s()
{
	FIFO_Print(&FIFO_st);
}
