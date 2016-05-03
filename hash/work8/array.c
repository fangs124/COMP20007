/* 
** COMP200007 Design of Algorithms 
** Data structure to store an array of (key, void *) pairs, but
** stores them in separate arrays, first keys then ptrs.
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:54:26 EST
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "array.h"

    // create empty array
array_t *
array_create() {
    array_t *a = (array_t *)malloc(sizeof(array_t));
    assert(a != NULL);
    a->n    = 0;
    a->keys = NULL;
    a->ps   = NULL;
    return(a);
}

void
mtf(array_t *a, int pos) {
    Key headK  = a->keys[pos];
    void *headP= a->ps[pos];
    for(int j = pos ; j > 0 ; j--) {
        Key tempK  = a->keys[j];
        void *tempP= a->ps[j];
        a->keys[j] = a->keys[j-1];
        a->ps[j]   = a->ps[j-1];
        a->keys[j-1] = tempK;
        a->ps[j-1] = tempP;
    }
     a->keys[0] = headK;
     a->ps[0]   = headP;
}

// add (k,p) to a. MTF if mtf == 1, not otherwise
void
array_add(array_t *a, Key k, void *p, int mtf_flag) {
    a->n   += 1;
    a->keys = (Key *)realloc(a->keys, sizeof(Key) * a->n);
    a->ps   = (void **)realloc(a->ps, sizeof(void *) * a->n );
    assert(a->keys != NULL && a->ps != NULL);

    a->keys[a->n - 1] = k;
    a->ps  [a->n - 1] = p;
    
    if (mtf_flag)
        mtf(a, a->n-1);
}


// find k in a->keys at i and return a->ps[i]
// or return NULL if k not there.
// If mtf==1, mtf k if present, nothing otherwise.
void *
array_find(array_t *a, Key k, int mtf_flag) {
    assert(a != NULL);
    int i;
    for(i = 0 ; i < a->n && keyCmp(a->keys+i, &k) != 0; i++)
        ;
    if (i == a->n)
        return NULL;

    if (mtf_flag && i > 0) {
        mtf(a, i);
        i = 0;
    }
    return a->ps[i]; 
}

// If k is in the array, move all items to 
// right of k (and matching ps) to the left one space
// thus deleting  (k,ps)
void    
array_delete(array_t *a, Key k) {
    assert(a != NULL);
    int i;
    for(i = 0 ; i < a->n && keyCmp(a->keys+i, &k) != 0; i++)
        ;

    for(int j = i+1 ; j < a->n ; j++) {
        a->keys[j-1] = a->keys[j];
        a->ps[j-1] = a->ps[j];
    }
}

void
array_print(array_t *a) {
    printf("n=%d Keys: ",a->n);
    for(int i = 0 ; i < a->n ; i++)
        printf(KEY_PRINT_FORMAT" ",a->keys[i]);
    //printf("ps: ");
    //for(int i = 0 ; i < a->n ; i++)
    //    printf(" ",a->ps[i]);
}
