/*
 ============================================================================
 Name        : Multiply2Floating.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float i,j;
	printf("Enter two numbers:");
	fflush(stdin); fflush(stdout);
	scanf("%f %f", &i,&j);
	printf("Product:%lf",i*j);
	return EXIT_SUCCESS;
}
