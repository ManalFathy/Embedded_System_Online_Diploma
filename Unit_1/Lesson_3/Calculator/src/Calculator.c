/*
 ============================================================================
 Name        : Calculator.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	char c;
	float a,b;
	printf("Enter an operator either + or - or * or / :");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);

	printf("Enter two operands :");
	fflush(stdin); fflush(stdout);
	scanf("%f %f",&a,&b);

	switch(c){
	case '+':
		printf("%.1f + %.1f = %.1f", a, b , a + b );
		break;

	case '-':
		printf("%.1f - %.1f= %.1f", a ,b , a - b );
		break;

	case '*':
		printf("%.1f * %.1f = %.1f", a , b , a * b );
		break;

	case '/':
		printf("%.1f / %.1f = %.1f", a , b , a / b );
		break;
	default :
		printf("wrong operands");

	}

	return EXIT_SUCCESS;
}
