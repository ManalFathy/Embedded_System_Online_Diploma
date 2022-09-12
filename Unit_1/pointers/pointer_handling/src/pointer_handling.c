/*
 ============================================================================
 Name        : pointer_handling.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int m = 29;
	printf("Address of m : %p \n",&m);
	printf("value of m : %d \n", m);

	int* ab; // ab is an integar pointer
	ab=&m; // ab is point to a
	printf("content of ab (address of m): %p \n",ab);
	printf("the value that ab point to : %d \n", *ab);

	m=34; // assign 34 to m
	printf("content of ab (address of m): %p \n",ab);
	printf("the value that ab point to : %d \n", *ab);

	*ab=7; // assign 34 to m
	printf("content of ab (address of m): %p \n",ab);
	printf("the value that ab point to : %d \n", *ab);





	return EXIT_SUCCESS;
}
