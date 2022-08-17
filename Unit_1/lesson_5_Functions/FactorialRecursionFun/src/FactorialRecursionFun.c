/*
 ============================================================================
 Name        : FactorialRecursionFun.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
long Factorial(int);
int main(void) {
	int n ;
	long int f;
	printf("Enter an integer :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);// n is number want to get its factorial
	f=Factorial(n);
	printf("Factorial of %d = %ld", n, f);

	return EXIT_SUCCESS;
}

long Factorial(int n)
{
	if(n>1)
		return (n*Factorial(n-1));
	else return 1;
}
