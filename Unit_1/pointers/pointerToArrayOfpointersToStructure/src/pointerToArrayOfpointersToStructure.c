/*
 ============================================================================
 Name        : pointerToArrayOfpointersToStructure.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
typedef struct Employee
{
	char name[10];
	int id;
}employee;

int main(void)
{
	employee emp1={"ahmed",1001}; // emp1,emp2,emp3 is a employee structure datatype
	employee emp2={"alex",1002};
	employee emp3={"john",1003};

	employee *arr[]={&emp1,&emp2,&emp3};//arr is an array of pointers to structure employee datatype
	employee (*(*pta)[3])=arr;//pta is apointer to array of 3 elements their type is pointer to structure

	printf("second Employee name : %s\n",(**(*pta+1)).name);
	printf("second Employee name : %s\n",(**(arr+1)).name);//*pta=*(&arr)=arr
	printf("second Employee name : %s\n",(*arr[1]).name);//*(arr+1)=arr[1]
	printf("second Employee name : %s\n",emp2.name);//arr[1]=&emp2//*&emp2=emp2


	return EXIT_SUCCESS;
}
