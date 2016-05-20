/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * NAME: Adrian Hendrawan Putra
 * ID  : 743206
 * DESC: 0x7c
 *
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>

/* Unsure if this is allowed */
#include <stdio.h>
#include <stdlib.h>

#define MAXSTRLEN 256

/* Helper internal functions */

/* Print MAXSTRLEN random ints according to specs */
void print_random_int(unsigned int size, unsigned int seed);
unsigned int *extended_euclid(unsigned int a, unsigned int b);

/* ------------------------- */

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    /* smallest prime is 2 */
    if (n == 0) {
        return 2;
    }
    /* find prime largern than 2*n */
    unsigned int candidate = (2*n) + 1; //candidate is always odd
    unsigned int i;
    bool found = false;
    
    while (!found) {
        found = true;

        /* test for odd factors  */
        for (i = 3; i*i <= candidate; i+=2) {
            if (candidate % i == 0) {
                /* candidadate is not prime */
                found = false;
                break;
            }
        }

        /* if not found, get new candidate */
        if (!found) candidate += 2;
    }

    return candidate;
}


/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
    print_random_int(size, seed);

    int coll_count = 0;
    unsigned int char_val;
    unsigned int i;
    
    /* start from string of length 1 */
    unsigned int length = 1;
    unsigned char *string = (unsigned char*) malloc(sizeof(unsigned char)*length+1);
    assert(string != NULL);

    /* initialize string */
    for (i = 0; i < length+1; i++){
        /* '\0'-terminate the string */
        if (i == length) string[i] = '\0';
        /* string must not be 0-padded */
        else string[i] = (unsigned char) 1;
    }

    /* bruteforce generate strings */
    while (coll_count != n && length != MAXSTRLEN) {
        /* try for each position */
        for (i = 0; i < length; i++){
            /* try for all values of char */
            for (char_val = 1; char_val < 0x100; char_val++){
                string[i] = (unsigned char) char_val;
                
                /* print string if hashed to 0 */
                if (universal_hash(string, size) == 0) {
                    fprintf(stdout, "%s\n", &string[0]);
                    coll_count++;

                    /* stop if n collisions is found */
                    if(coll_count == n){
                        return;
                    }
                }
            }
        }

        /* increase string length */
        length++;
        string = (unsigned char*) realloc(string, sizeof(unsigned char) * length+1);
        assert(string != NULL);

        /* initialize string */
        for (i = 0; i < length+1; i++){
            /* '\0'-terminate the string */
            if (i == length) string[i] = '\0';
            /* string must not be 0-padded */
            else string[i] = (unsigned char) 1;
        }
    }
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
    //unfinished
}

/* Helper internal functions */

/* Print MAXSTRLEN random ints according to specs */
void print_random_int(unsigned int size, unsigned int seed){
    srand(seed);
    fprintf(stdout, "%d\n", MAXSTRLEN);
    for(unsigned int i = 0; i < MAXSTRLEN; i++){
        fprintf(stdout, "%u\n", (unsigned int)(rand() % size));
    }
}

/* note: a >= b */
/* Takes in (a,b) and returns (x,y,d) such that ax + by = d */
unsigned int *extended_euclid(unsigned int a, unsigned int b) {
    /* allocate space for (x,y,d) */
    unsigned int *return_val = (unsigned int*) malloc(sizeof(unsigned int) * 3);
    unsigned int *temp; // holds (x', y', d)
    assert(return_val != NULL);

    if(b == 0){ //return (1, 0, a)
        return_val[0] = 1;
        return_val[1] = 0;
        return_val[2] = a;
    }

    else { // return (y', x' - [a/b]y', d)
        /* note: a >= b */
        if (b >= a%b) temp = extended_euclid(b, a%b);
        else temp = extended_euclid(a%b, b);

        return_val[0] = temp[1];
        return_val[1] = temp[0] - ((a/b)*temp[1]);
        return_val[2] = temp[2];
        
        /* free temp memory */
        free(temp);
        temp = NULL;
    }

    return return_val;
}

/* ------------------------- */

/*
 * Attribution:
 *   determine_size() function is adapted from
 *   http://people.eng.unimelb.edu.au/ammoffat/ppsaa/c/isprime.c
 *
 *    extended_euclid() function is adapted from
 *    Algorithms(Dasgupta, et al.) page 20
*/
