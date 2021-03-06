/*
 *
*/
#include "hash.h"

#include <stdlib.h>

//
#include <stdio.h>
//
#define MAXSTRLEN 256

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size) {
    //not sure if this is right
    (void) e;
    (void) size;
    return 1;
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
    //generate random a here
    static unsigned int a = 0;
    if (a == 0){
        a = rand() %size;
    }
    return (a * key[0]) %size;
}

/* Universal hash function as described in Dasgupta et al 1.5.2 */
unsigned int universal_hash(unsigned char *key, unsigned int size) {
    //make this static?
    unsigned int h = 0;
    unsigned int i;
    static unsigned int initialized = 0;
    static unsigned int r[MAXSTRLEN];
  
    if(!initialized){
        for(i = 0; i < MAXSTRLEN; i++){
            r[i] = rand() %size;
        }
        initialized = 1;
    }

    for(i = 0; i < size; i++){
        h += (r[i] * key[i]);
    }
    return h %size;
}

//implement this
