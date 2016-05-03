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
** Modified Andrew Turpin April 2013 for COMP20007
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "listops.h"


/*
** Return a new list
*/
list_t
*list_create() {
    list_t *list;
    list = (list_t*)malloc(sizeof(list_t));
    assert(list != NULL);
    list->head = list->foot = list->curr = NULL;
    list->size = 0;
    return list;
}

/*
** print the size of the list at the start, then
** print the data elements in each node (using LIST_PRINT_FORMAT)
** and ->NULL at the end of the list.
*/
void
list_print(list_t *list) {
    node_t *curr;
    assert(list!=NULL);
    printf("(n= %d)", list->size);
    curr = list->head;
    while (curr) {
        char extra[3] = "  ";
        if (curr == list->foot)
            extra[0] = 'f';
        if (curr == list->curr)
            extra[1] = 'c';
        printf("%s"KEY_PRINT_FORMAT, extra,curr->key);
        curr = curr->next;
    }
    printf("->NULL\n");
}

/*
** Insert value in a new node at the head of the list
*/
void
list_add(list_t *list, Key k, void *p, int mtf) {
    assert(list!=NULL);
    node_t *newnode;
    newnode = (node_t*)malloc(sizeof(node_t));
    assert(newnode != NULL);
    newnode->key  = k;
    newnode->data = p;
    
    if (mtf || list->head == NULL) {
        newnode->next = list->head;
        list->head = newnode;
        if (list->foot==NULL) { /* this is the first insertion into the list */
            list->foot = newnode;
        }
    } else {
        list->foot->next = newnode;
        newnode->next = NULL;
        list->foot = newnode;
    }
    list->size++;
}

/*
** Find k in list, return associated data or NULL if not there.
** If mtf==1, move found item to front.
*/
void *
list_find(list_t *list, Key k, int mtf) {
    assert(list != NULL);

    node_t *prev = NULL;
    node_t *curr = list->head;
    while (curr != NULL && keyCmp(&(curr->key), &k) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        return NULL;
    } else {
        if (mtf && curr != list->head) {
            if (curr == list->foot)
                list->foot = prev;
            prev->next = curr->next; 
            curr->next = list->head;
            list->head = curr;
        }
    }
    return curr->data;
}
void
list_delete(list_t *list, Key k) {
    assert(list != NULL);

    node_t *prev = NULL;
    node_t *curr = list->head;
    while (curr != NULL && keyCmp(&(curr->key), &k) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return;

    if (curr == list->foot)
        list->foot = prev;

    if (curr == list->head) 
        list->head = list->head->next;
    else 
        prev->next = curr->next; 
    
    free(curr);
}
