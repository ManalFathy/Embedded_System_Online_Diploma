/*
 ============================================================================
 Name        : Structure_addDistances.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
struct Sdistance
{
	int feet;
	float inch;
};

int main(void)
{
	struct Sdistance a,b,sum;
	printf("Enter information for first distance:\n");//take the distances
	printf("Enter feet:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&a.feet);
	printf("Enter inch:");
	fflush(stdin); fflush(stdout);
	scanf("%f",&a.inch);

	printf("Enter information for second distance:\n");
	printf("Enter feet:");
	fflush(stdin); fflush(stdout);
	scanf("%d",&b.feet);
	printf("Enter inch:");
	fflush(stdin); fflush(stdout);
	scanf("%f",&b.inch);
	sum.feet=a.feet+b.feet; //adding them
	sum.inch=a.inch+b.inch;
	if(sum.inch>12.0)//convert inch to feet
	{
		sum.inch-=12.0;
		sum.feet++;
	}
	printf("sum of distance = %d\'-%.1f\"",sum.feet,sum.inch);




	return EXIT_SUCCESS;
}
