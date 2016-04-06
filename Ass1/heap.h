typedef struct ITEMS {
	//the key for deciding position in heap
	float key;
	//the payload index provided by the calling program
	uint index;
} item_t;


typedef struct HEAPS {
	item_t *H; //the array
	//map[i] is index into H of location of payload with index == i;
	uint *map;
	uint n; //number of items
	uint size; //max number of items 
} heap_t;

/* returns a pointer to a new empty heap */
heap_t *create_heap(void);

/* inserts data index into h, returns sucess status */
int insert(heap_t* h, uint index, float key);

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