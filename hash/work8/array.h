/* 
** COMP200007 Design of Algorithms 
** Data structure to store an array of (key, void *) pairs, but
** stores them in separate arrays, first keys then ptrs.
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:21:49 EST
*/

#include "key.h"

typedef struct array {
    int n;
    Key *keys;
    void **ps;
} array_t;

array_t *array_create(void);
void    array_add(array_t *a, Key k, void *p, int mtf);
void    *array_find(array_t *a, Key k, int mtf);
void    array_delete(array_t *a, Key k);
void    array_print(array_t *a);
