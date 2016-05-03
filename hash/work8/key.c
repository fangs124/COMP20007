/* 
** COMP200007 Design of Algorithms 
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:21:49 EST
*/

#include "key.h"

int 
keyCmp(const void *a, const void *b) {
    int aa = *((int *)a);
    int bb = *((int *)b);
    return bb - aa;
}
