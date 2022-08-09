/*
 ============================================================================
 Name        : SwapWithoutTemp.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x,y;
	printf("enter two integars :");
	fflush(stdin); fflush(stdout);
	scanf("%d %d",&x , &y);
	x=x+y;
	y=x-y;
	x=x-y;
	printf("After Swapping :%d %d", x,y);
	return EXIT_SUCCESS;
}
