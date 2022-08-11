/*
 ============================================================================
 Name        : SearchINArray.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n ,i ,x,a[100];
	printf("Enter the number of elements :"); // number of array elements
	fflush(stdin); fflush(stdout);
	scanf("%d", &n);
	printf("Enter the array elements:");
	fflush(stdin); fflush(stdout);
	for(i=0;i<n;i++)
		scanf("%d", &a[i]);
	printf("Enter the element to be searched :"); // the element want to be searched
	fflush(stdin); fflush(stdout);
	scanf("%d", &x);
	for(i=0;i<n;i++) // search in the array
	{
		if(a[i]==x)
		{
			printf("the number found at location : %d", i+1);
			break;
		}
	}
	if(i==n)
		printf("the number you entered not in the list ");


	return EXIT_SUCCESS;
}
