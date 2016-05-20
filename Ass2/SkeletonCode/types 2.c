/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module provides fundamental functionality used to
 * interpret generic pointers into typed data.
 *
*/
#include "types.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* Returns whether n1 is equal to n2 */
bool int_eq(long e1, long e2) {
    return e1 == e2;
}

/* Prints n to file */
void int_print(FILE *file, long e) {
    fprintf(file, " %ld", e);
}

// implement this
/* Returns whether str1 is equal to str2 */
bool str_eq(char *str1, char *str2) {
	//assert that strings are non-empty
	return (bool) memcmp(str1, str2);
}

//implement this
/* Returns a copy of src */
char *str_copy(char *src) {
	//assert that string is non-empty
	size_t n = strlen(src)+1;
	char *new_str = (char*) malloc(sizeof(char)*n);
	return memcpy(new_str, src, n);
	//need to check for correctness
}

//implement this
/* Prints str to file */
void str_print(FILE *file, char *str) {
	fprintf(file, " %s", str);
}

//implement this
/*
notes:

data is fetched from file using fgets, '\0'-termination can be assumed
	hashtable.c line 123
	while (fgets(buffer, MAX_LINE_LEN, file) != NULL);
*/
