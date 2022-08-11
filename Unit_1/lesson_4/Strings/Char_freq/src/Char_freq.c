/*
 ============================================================================
 Name        : Char_freq.c
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

	char s[100],c;
	int i,k=0;
	printf("Enter a string :");// ask user to enter a string
	fflush(stdin); fflush(stdout);
	gets(s);
	printf("Enter a character to find frequency : ");// ask user to enter the character that wanted to find its frequency
	fflush(stdin); fflush(stdout);
	scanf("%c",&c);
	for (i=0 ; i<=strlen(s) ; i++)
	{
		if(s[i]==c)
			k++;
	}
	printf("the frequency of %c = %d" ,c,k );
	return EXIT_SUCCESS;
}
