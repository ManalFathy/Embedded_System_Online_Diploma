/*
 * fun_hed.h
 *
 *  Created on: Nov 2, 2022
 *      Author: ayman
 */

#ifndef FUN_HED_H_
#define FUN_HED_H_
#include "fifo.h"
#define DPRINTF(...) { fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__);\
		fflush(stdout); \
		fflush(stdin); }
#define DSCANF(...) { fflush(stdout); \
		fflush(stdin); \
		scanf(__VA_ARGS__);\
		fflush(stdout); \
		fflush(stdin); }
struct sinfo
{
	char fname[50];
	char lname[50];
	int roll;
	float GPA;
	int cid[10];
};



void add_student_file();
void add_student_manually();
void find_rl();
void find_fn();
void find_c();
void tot_s();
void del_s();
void up_s();
void show_s();


#endif /* FUN_HED_H_ */
