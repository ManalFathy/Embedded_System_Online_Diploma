/*
 ============================================================================
 Name        : MatrixTranspose.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int a[10][10],t[10][10];
	int r,c,i,j;

	printf("Enter the number of rows and columns of the matrix :");// take Matrix dimensions
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&r ,&c);
	printf("Enter the elements of the matrix :\n"); // take Matrix element
	for(i=0 ; i<r ;i++)
	{
		for(j=0 ; j<c ;j++)
		{
			printf("Enter element a%d%d:",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%d",&a[i][j]);

		}

	}
	printf("Entered Matrix :\n"); //print entered matrix
	for(i=0 ; i<r ;i++)
	{
		for(j=0 ; j<c ;j++)
		{
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}

	for(i=0 ; i<r ;i++)
	{
		for(j=0 ; j<c ;j++)
		{
			t[j][i]=a[i][j];
		}
	}
	printf("Transpose of Matrix :\n"); //print transposed matrix
	for(i=0 ; i<c ;i++)
	{
		for(j=0 ; j<r ;j++)
		{
			printf("%d\t",t[i][j]);
		}
		printf("\n");
	}


	return EXIT_SUCCESS;
}
