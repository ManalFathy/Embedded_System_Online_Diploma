/*
 ============================================================================
 Name        : ArrayAverage.c
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
	int n , i;
	float sum=0 ;
	float a[100];
	printf ("Enter the number of data :");// number of data that will store in the array
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	for(i=0;i<n;i++) // take the array element
	{
		printf ("Enter element number %d :" , i+1);
		fflush(stdin); fflush(stdout);
		scanf("%f",&a[i]);
	}
	for(i=0;i<n;i++) // add array element
		sum+=a[i];

	printf("Average=%.2f", sum/n);

	return EXIT_SUCCESS;
}
