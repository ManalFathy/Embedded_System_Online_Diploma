/*
 ============================================================================
 Name        : ReverseSentence_Recursive.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
void ReverseRecursive();

int main(void) {


	printf("Enter a string :");//ask user to enter the string
	fflush(stdin); fflush(stdout);
	ReverseRecursive();
	return EXIT_SUCCESS;
}
void ReverseRecursive()
{
	char c;
	scanf("%c",&c);
	if (c != '\n'){
		ReverseRecursive();
	printf("%c",c);
}
	}
