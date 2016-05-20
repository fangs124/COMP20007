/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * NAME: Adrian Hendrawan Putra
 * ID  : 743206
 * DESC: 0x7c
 *
*/
#include "hash.h"

#include <stdlib.h>

#define MAXSTRLEN 256

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size) {
    (void) e;
    (void) size;
    return 1; //next bucket
}

/* Very simple hash */
unsigned int worst_hash(void *e, unsigned int size) {
    (void) e;
    (void) size;
    return 0;
}

/* Basic numeric hash function */
unsigned int num_hash(long n, unsigned int size) {
    return n % size;
}

/* Bad hash function */
unsigned int bad_hash(char *key, unsigned int size) {
    /* generate random a */
    static unsigned int a = 0;
    if (a == 0) {
        a = rand() % size;
    }

    return (a * key[0]) % size;
}

/* Universal hash function as described in Dasgupta et al 1.5.2 */
unsigned int universal_hash(unsigned char *key, unsigned int size) {
    static unsigned int initialized = 0;
    static unsigned int r[MAXSTRLEN];
    unsigned int i;

    /* generate r[] if not initialized */
    if (!initialized) {
        for (i = 0; i < MAXSTRLEN; i++) {
            r[i] = rand() % size;
        }
        initialized = 1;
    }

    /* calculate hash */
    unsigned int h = 0;
    for (i = 0; i < strlen(key); i++) {
        h += (r[i] * key[i]);
    }
    
    return h % size;
}
