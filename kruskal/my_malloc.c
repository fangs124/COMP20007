/*
 * Anh Vo, for:
 *
 * Week 7 Lab: COMP20007 Design of Algorithms
 *
 *
*/
#include "my_malloc.h"

/* malloc n * size bytes, which is called by the function "module" */
extern void *my_malloc(int n, int size, char *module) {
  void *p;
  if ( !(p= malloc(n * size)) ) {
    fprintf(stderr, "my_malloc: Unable to malloc %d x %d = %d bytes as required by %s\n",
	    n, size, n*size, module);
    exit (EXIT_FAILURE);
  }
  return p;
}

/* ralloc n * size bytes, which is called by the function "module" */
extern void *my_realloc(void *old, int n, int size, char *module) {
  void *p;
  if ( !(p= realloc(old, n * size)) ) {
    fprintf(stderr, "my_ralloc: Unable to malloc %d x %d = %d bytes as required by %s\n",
	    n, size, n*size, module);
    exit (EXIT_FAILURE);
  }
  return p;
}

