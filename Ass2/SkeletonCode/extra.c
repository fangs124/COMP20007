/*
 *
*/
#include "extra.h"
#include "hash.h"

#include <stdbool.h>

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n) {
    //find next prime after 2*n
    return n;
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
