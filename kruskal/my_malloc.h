
/*
 * Anh Vo, for:
 *
 * Week 7 Lab: COMP20007 Design of Algorithms
 *
 *
*/

#ifndef _MY_MALLOC_H_
#define _MY_MALLOC_H_
#include <stdio.h>
#include <stdlib.h>


/* malloc n * size bytes, which is called by the function "module" */
void *my_malloc(int n, int size, char *module); 

/* ralloc n * size bytes, which is called by the function "module" */
void *my_realloc(void *old, int n, int size, char *module); 

#endif
