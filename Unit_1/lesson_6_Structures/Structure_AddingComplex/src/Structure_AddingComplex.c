/*
 ============================================================================
 Name        : Structure_AddingComplex.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct SComplex
{
	float real;
	float imag;
}a,b;
void addingComplex(struct SComplex x,struct SComplex y)
{
	struct SComplex z;
	z.real=x.real+y.real;
	z.imag=x.imag+y.imag;
	printf("sum=%.1f+%.1fi",z.real,z.imag);
}

int main(void)
{
	printf("For 1st complex number\n:");
	printf("Enter real and imaginary respectively:\n");//take the numbers
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&a.real,&a.imag);

	printf("For 2nd complex number\n:");
	printf("Enter real and imaginary respectively:\n");//take the numbers
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&b.real,&b.imag);

	addingComplex(a,b);

	return EXIT_SUCCESS;
}
