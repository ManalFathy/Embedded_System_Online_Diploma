/*
 ============================================================================
 Name        : pointer_reversing_string.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char s[20];
	printf("input a string :");// take a string from user
	fflush(stdin); fflush(stdout);
	gets(s);
	char* p = NULL;
	int i , size=strlen(s);
	p=&s[size-1];
	printf("the reversed string :");//printing the string in reverse order
	for(i=0;i<size;i++)
	{
		printf("%c",*p);
		p--;
	}
	return EXIT_SUCCESS;
}
