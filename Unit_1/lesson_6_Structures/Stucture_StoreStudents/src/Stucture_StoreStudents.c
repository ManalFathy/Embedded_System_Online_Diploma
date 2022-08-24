/*
 ============================================================================
 Name        : Stucture_StoreStudents.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef struct S_student
{
	char name[20];
	int roll_number;
	float marks;
}student;

int main(void)
{
	student s[10];
	int i=0;
	printf("Enter students information:\n");//take students information
	for(;i<10;i++)
	{
		s[i].roll_number=i+1;
		printf("for roll number: %d\n" ,s[i].roll_number);
		printf("Enter name:");
		fflush(stdin); fflush(stdout);
		gets(s[i].name);
		printf("Enter marks:");
		fflush(stdin); fflush(stdout);
		scanf("%f",&s[i].marks);
	}
	printf("Displaying students information:\n");//displaying students information
	for(i=0;i<10;i++)
	{
		printf("information for roll number :%d\n",s[i].roll_number);
		printf("Name:%s\n",s[i].name);
		printf("Marks:%.2f\n",s[i].marks);
	}

	return EXIT_SUCCESS;
}
