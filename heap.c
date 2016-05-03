#include <stdlib.h>
#include <assert.h>
#include "heap.h"

#define HEAP_SUCCESS      0
#define HEAP_FAIL         1

#define INITIAL_HEAP_SIZE 32

/* returns a pointer to a new empty heap */
heap_t* create_heap(void) {
	heap_t* heap = (heap_t*) malloc(sizeof(heap_t));
	heap->H = NULL;
	heap->map = NULL;
	heap->n = 0;
	heap->size = 0;
	return heap;
}

/* inserts data index into h, returns sucess status */
int insert(heap_t* h, uint index, float key) {
	assert(h != NULL);

	/* allocate heap size */
	if(h->size = 0){
		h->size = INITIAL_HEAP_SIZE;
		h->H = (item_t*) malloc(sizeof(item_t) * INITIAL_HEAP_SIZE);
		h->map = (uint*) malloc(sizeof(uint) * INITIAL_HEAP_SIZE);
	}
	/* double heap size */
	else if(h->n == h->size){
		h->size *= 2;
		h->H = (item_t*) realloc(h->H, sizeof(item_t) * h->size);
		h->map = (uint*) realloc(h->map, sizeof(uint) * h->size);
	}

	/* create item insert item */
	
}
/* returns the data index of the root */
uint peek(heap_t* h);

/* returns the key of the root */
float peek_key(heap_t* h);

/* removes the root and returns the data index, re-heaps h */
uint remove_min(heap_t* h);

/* adds delta to the key of data index, re-heaps h */
void change_key(heap_t* h, uint index, int delta);

/* free allocated memory associated with heap h */
void destroy_heap(heap_t* h);