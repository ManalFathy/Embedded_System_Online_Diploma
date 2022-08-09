/*
 ============================================================================
 Name        : Add2integars.c
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
	int i,j;
	printf("Enter two integers:");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&i,&j);
	printf("Sum:%d",i+j);
	return EXIT_SUCCESS;
}
