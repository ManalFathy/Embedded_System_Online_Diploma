/*
 ============================================================================
 Name        : VowelCheck.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c ;
	printf("Enter an alphabet:");
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	if (c== 'a'|| c=='e' || c=='i' || c=='o' ||c== 'u')
		printf("%c is a vowel", c);
	else if (c== 'A'|| c=='E' || c=='I' || c=='O' || c=='U')
		printf("%c is a vowel", c);
	else
		printf("%c is a constant", c);

return EXIT_SUCCESS;
}
