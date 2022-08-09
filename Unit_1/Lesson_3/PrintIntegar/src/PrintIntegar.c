/*
 ============================================================================
 Name        : PrintIntegar.c
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
	int i;
	printf("Enter a integer:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&i);
	printf("\n You entered: %d",i);

	return EXIT_SUCCESS;
}
