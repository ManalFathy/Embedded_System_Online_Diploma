/*
 ============================================================================
 Name        : LargestNumber.c
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
	float a,b,c;
	printf("Enter Three Numbers:");
	fflush(stdin); fflush(stdout);
	scanf("%f %f %f",&a,&b,&c);
	if(a>b){
		if(a>c)
			printf("Largest number = %g" , a);
		else
			printf("Largest number = %g" , c);
	}
	else {
		if(b>c)
			printf("Largest number = %g" , b);
		else
			printf("Largest number = %g" , c);
	}
		return EXIT_SUCCESS;
	}
