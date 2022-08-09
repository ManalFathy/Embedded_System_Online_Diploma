/*
 ============================================================================
 Name        : AlphabetCheck.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(void) {
	char c;
	printf("Enter a character : ");
	fflush(stdin); fflush (stdout);
	scanf("%c",&c);
	if(isalpha(c))
		printf("%c is an alphabet", c);
	else
		printf("%c is not an alphabet", c);

	return EXIT_SUCCESS;
}
