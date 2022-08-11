/*
 ============================================================================
 Name        : String_Length.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char s[100];
	int i=0;
	printf("Enter a string :");//ask user to enter the string
	fflush(stdin); fflush(stdout);
	gets(s);
	while (s[i]!= 0)
		i++;

	printf("Length of string :%d",i);

	return EXIT_SUCCESS;
}
