/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * NAME: Adrian Hendrawan Putra
 * ID  : 743206
 * DESC: 0x7c
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
    return !(bool) strcmp(str2, str1); //invert return value
}

/* Returns a copy of src */
char *str_copy(char *src) {
    assert(src != NULL);

    
    /* allocate memory */
    size_t len = strlen(src)-1; //exclude '\n'
    char *new_str = (char*) malloc(sizeof(char)*len);
    assert(new_str != NULL);
    
    /* copy string */
    strncpy(new_str, src, len);
    new_str[len] = '\0'; //guarantees '0'-terminated

    return new_str;
}

/* Prints str to file */
void str_print(FILE *file, char *str) {
    fprintf(file, " %s", str);
}

