/*
 ============================================================================
 Name        : String_Reverse.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char s[20],r[20];
	int k=0;
	printf("Enter a string :");//ask user to enter the string
	fflush(stdin); fflush(stdout);
	gets(s);
	int i= strlen(s);

	while(i > 0) // reverse the entered string
	{
		r[k]=s[i-1];
		k++;
		i--;
	}
	s[k+1]=0;
	printf("Reverse string is : %s ",r);

	return EXIT_SUCCESS;
}
