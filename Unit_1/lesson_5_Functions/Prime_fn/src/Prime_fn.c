/*
 ============================================================================
 Name        : Prime_fn.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int primeCheck(int);

int main(void)
{
	int n1,n2,i,flag=0;
	printf("Enter two numbers (intervals):");// enter the intervals that want to check the prime numbers between them
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&n1,&n2);
	printf("prime numbers between %d and %d are:",n1,n2);
	for(i=n1+1;i<n2;i++)
	{
		flag=primeCheck(i);
		if(flag==1)
			printf("%d ",i);
	}

	return EXIT_SUCCESS;
}
int primeCheck(int n)
{
	int i;
	for(i=2;i<=n/2;i++)
	{
		if(n%i==0)
			return 0;
	}
	return 1;
}
