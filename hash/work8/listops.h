/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://www.csse.unimelb.edu.au/~alistair/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
/*
** Modified Andrew Turpin May 2013 for COMP20007
*/

typedef struct node node_t;
struct node {
    Key key;
    void *data;
    node_t *next;
};

typedef struct {
    node_t *head;
    node_t *foot;
    node_t *curr;   // for iterator
    unsigned int size;
} list_t;

list_t *list_create(void);
void    list_add(list_t *a, Key k, void *p, int mtf);
void    *list_find(list_t *a, Key k, int mtf);
void    list_delete(list_t *a, Key k);
void    list_print(list_t *list);
