/*
 ============================================================================
 Name        : AreaOfCircle.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define pi (3.1415)
#define area(R) ((pi)*(R)*(R))

int main(void)
{
	float r , a;
	printf("Enter the radius :");
	fflush(stdin); fflush(stdout);
	scanf("%f",&r);
	a=area(r);
	printf("Area = %.2f",a);

	return EXIT_SUCCESS;
}
