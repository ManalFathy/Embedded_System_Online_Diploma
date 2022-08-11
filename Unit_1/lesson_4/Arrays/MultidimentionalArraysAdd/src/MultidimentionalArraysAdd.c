/*
 ============================================================================
 Name        : MultidimentionalArraysAdd.c
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
	int r , c ;
	float a[2][2],b[2][2],s[2][2];
	printf("Enter the elements of 1st matrix : \n");
	for(r=0 ; r<2 ; r++) // take the input of 2*2 matrix
	{
		for(c=0 ; c<2 ; c++)
		{
			printf("Enter a%d%d", r+1 , c+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&a[r][c]);
		}
	}

	printf("Enter the elements of 2nd matrix : \n");
	for(r=0 ; r<2 ; r++) // take the input of 2*2 matrix
	{
		for(c=0 ; c<2 ; c++)
		{
			printf("Enter b%d%d", r+1 , c+1);
			fflush(stdin); fflush(stdout);
			scanf("%f",&b[r][c]);
		}
	}

	for(r=0 ; r<2 ; r++) // add the two matrix
	{
		for(c=0 ; c<2 ; c++)
		{
			s[r][c]=a[r][c]+b[r][c];
		}
	}
	printf("Sum of Matrix :\n");
	for(r=0 ; r<2 ; r++) // print the sum
	{
		for(c=0 ; c<2 ; c++)
		{
			printf ("%.1f\t" ,s[r][c]);
		}
		printf(" \n");
	}

	return EXIT_SUCCESS;
}
