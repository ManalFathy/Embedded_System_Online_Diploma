/*
 ============================================================================
 Name        : InsertElementInArray.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n,i ,x,j;
	int a[100];
		  printf("Enter number of elements:");//number of array elements
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);

	for(i=0 ; i<n ; i++)
	{
		a[i]=i+1; // put any numbers in the array
		printf("%d",a[i]);
	}

	printf ("\nEnter the elements to be inserted:");// the element want to inserted
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	printf ("Enter the location:");// the location of the element want to inserted
	fflush(stdin); fflush(stdout);
	scanf("%d",&j);

	for(i=n ; i>=j ; i--)// shifting the elements and insert the new one
		a[i]=a[i-1];
	a[j-1]=x;

	for(i=0 ; i<=n ; i++) //print the new array
		printf("%d",a[i]);





	return EXIT_SUCCESS;
}
