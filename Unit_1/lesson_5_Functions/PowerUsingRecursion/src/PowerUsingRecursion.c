/*
 ============================================================================
 Name        : PowerUsingRecursion.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int power(int,int);

int main(void)
{
	int n,p,r;
	printf("enter base number:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	printf("enter power number(positive integar) :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&p);
	r=power(n,p);
	printf("%d^%d=%d",n,p,r);

	return EXIT_SUCCESS;
}
int power(int n,int p)
{
	if (p>=1)
		return n*power(n,p-1) ;
	else
return 1 ;
}
