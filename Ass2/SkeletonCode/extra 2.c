/*
 *
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    //find next prime after 2*n
    //need to watch for this
    unsigned int size = 5*n;
    //maybe use static here?
    //prime matrix
    unsigned int i = 0;
    static bool *matrix = NULL;

    /* initialize list */
    if(matrix == NULL){
        matrix = (bool*) malloc(sizeof(bool)*size);
        while(i < size){
            if(i < 2){ //0 and 1 is not a prime;
                matrix[i] = false;
            }
            else{
                matrix[i] = true;
            }
            i++;
        }
        //find floor square root of size
        //need to fix this?
        for(i = 0; (i+1)*(i+1) <= size; i++){};
        //max integer to check
        unsigned int max = i;
        unsigned int j;
        //sieve the non-primes
        for(i = 2; i < max; i++){
            for(j = 2; i*j < size; j++){
                matrix[i*j] = false;
            }
        }
    } 
    /* get next prime */
    unsigned int return_val;
    for(i = (2*n)+1; i < size; i++){
        if(matrix[i] == true){
            return i;
        }
    }
    fprintf(stderr, "error: determine_size() on extra.c can't find prime!\n");
    exit(EXIT_FAILURE);
    return n;
    //should remove this
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n) {
}

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n) {
}

//implement this
/*
notes:

to impelement:
    implement determine_size() in extra.c to choose a hash table
    size equal to the next prime after 2*n.
assumption made:
    n is sufficiently small
    there exists a prime between 2*n and 3*n.

*/
