/*
 ============================================================================
 Name        : FactorialOfNumber.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int i , n ;
	long int f=1;
	printf("Enter an integer :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	if (n<0)
		printf("Error!!! Factorial of negative number doesn't exist");
	else {
		for (i=1 ; i<= n ; i++)
			f*=i;
		printf("Factorial = %ld", f);
	}
	return EXIT_SUCCESS;
}
