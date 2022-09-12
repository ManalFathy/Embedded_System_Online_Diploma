/*
 ============================================================================
 Name        : pointer_reversingArray.c
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
	int a[20],i,n;
	int* p;
	printf("input the number of array elements :");
	fflush(stdin); fflush(stdout);
	scanf("%d",&n);
	p=a;
	printf("input the array elements :\n");// take array elements from user
	for(i=0;i<n;i++)
	{
		printf("element %d : ",(i+1));
		fflush(stdin); fflush(stdout);
		scanf("%d",p);
		p++;
	}

	printf("the elements of the array in reverse order \n");
	for(i=0;i<n;i++)
	{
		p--;
		printf("element %d : %d \n",(n-i),*p);

	}


	return EXIT_SUCCESS;
}
