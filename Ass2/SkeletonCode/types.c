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

/* Returns whether str1 is equal to str2 */
bool str_eq(char *str1, char *str2) {
    return !(bool) strcmp(str2, str1);
}

/* Returns a copy of src */
char *str_copy(char *src) {
	//check this
    
    //strip '\n' char from string and replace with '\n';
    char *new_str;
    unsigned int n = strlen(src);

    if(src[n-1] == '\n'){
        new_str = (char*) malloc(sizeof(char)*n-1);
        strncpy(new_str, src, n-1);
        new_str[n] = '\0';
    }
    else{
        new_str = (char*) malloc(sizeof(char)*n);
        strncpy(new_str, src, n);
    }

    return new_str;
}

/* Prints str to file */
void str_print(FILE *file, char *str) {
	fprintf(file, " %s", str);
}

//implement this

