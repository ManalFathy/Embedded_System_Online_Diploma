/*
 ============================================================================
 Name        : Structure_Student.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct S_student
{
	char name[20];
	int roll_number;
	float marks;
};

int main(void)
{
	struct S_student x;
	printf("Enter information of student:\n");//take student information
	printf("Enter student name:");
	fflush(stdin); fflush(stdout);
	gets(x.name);
	printf("Enter student roll number:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x.roll_number);
	printf("Enter student marks:");
	fflush(stdin); fflush(stdout);
	scanf("%f",&x.marks);
	printf("Displaying information:\n");//displaying student information
	printf("Name:%s\n",x.name);
	printf("Roll:%d\n",x.roll_number);
	printf("Marks:%.2f\n",x.marks);
	return EXIT_SUCCESS;
}
