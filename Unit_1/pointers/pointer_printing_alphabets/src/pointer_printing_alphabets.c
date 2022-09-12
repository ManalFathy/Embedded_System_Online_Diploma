/*
 ============================================================================
 Name        : pointer_printing_alphabets.c
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
	char alpha[28];
	int x;
	char *p ;
	p=alpha;

	for(x=0;x<26;x++) // Assign the alphabets in the array using pointer
	{
		*p=x+'A';
		p++;
	}

	printf("the alphabets are :");
	p=alpha;
	for(x=0;x<26;x++)
	{
		printf("%c \t",*p);
		p++;
	}
	return EXIT_SUCCESS;
}
