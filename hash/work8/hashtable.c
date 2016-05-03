/**
** COMP200007 Design of Algorithms 
** Hash tables with separate chaining and arrays instead of LL.
**
** Author: Andrew Turpin (aturpin@unimelb.edu.au)
** Date: Wed  8 May 2013 19:41:20 EST
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "key.h"
#include "listops.h"
#include "array.h"
#include "hashtable.h"

/* 
** Create hash table, allocate space, initialise ptrs to NULL 
** INPUTS:
**    type is one of HashChainStyle
**    mtf is one of MTF_FALSE or MTF_TRUE
**    h1  is a hash function
**    h2  is a hash function (can be NULL, but then DoubleHash wont work)
**    size is number of slots to create in the table
** RETURNS: 
**    New, empty hash table with memory all alocated ready to go.
*/
HashTable *
hash_create(HashChainStyle type, int mtf, HashFn h1, HashFn h2, int size) {
	HashTable *ht = (HashTable *) malloc( sizeof(HashTable));
	assert(ht != NULL);

	ht->hash1        = h1; 
	ht->hash2        = h2; 
	ht->table_size   = size; 
	ht->mtf_flag     = mtf; 
	ht->chain_style  = type; 
	ht->htable       = (void **)malloc(sizeof(void *) * size);
	assert(ht->htable != NULL);

	if (type == Array) 
		for(int i = 0 ; i < size ; i++) {
			ht->htable[i] = array_create();
			assert(ht->htable[i] != NULL);
		}
	else if (type == List) 
		for(int i = 0 ; i < size ; i++) {
			list_t *temp = list_create();
			ht->htable[i] = (void *)temp;
			assert(ht->htable[i] != NULL);
		}
	else if (type == DoubleHash) {  // an empty table slot has ->data == NULL
		assert(ht->hash2 != NULL);
		for(int i = 0 ; i < size ; i++) {
			KeyDataPair *temp = (KeyDataPair *)malloc(sizeof(KeyDataPair));
			assert(temp != NULL);
			temp->data = NULL;
			ht->htable[i] = (void *)temp;
		}
	} else { 
		fprintf(stderr, "Invalid hashtable type: %d\n",type);    
		free(ht);
		return NULL;
	}

	return(ht);
}


/* 
** Search ht for k.
** INPUTS:
**   ht is hash table
**    k is key
** RETURNS: 
**     data ptr if found, else NULL 
** SIDE EFFECTS: 
**     may mtf.
** ASSUMES:
**    ht->hash1 and ht->hash2 are both valid
*/
void *
hash_search(HashTable *ht, Key k) {
	assert(ht != NULL);

	unsigned int hval = ht->hash1(k, ht->table_size, 0);

		// this is where superclasses/inheritence comes in handy in C++
	if (ht->chain_style == Array)
		return array_find((array_t *)(ht->htable[hval]), k, ht->mtf_flag == MTF_TRUE);
	else if (ht->chain_style == List) 
		return list_find((list_t *)(ht->htable[hval]), k, ht->mtf_flag == MTF_TRUE);
	else if (ht->chain_style == DoubleHash) {
		KeyDataPair *pair = (KeyDataPair *)(ht->htable[hval]);
		if (pair->key != k) {
			//WRITE ME
			// compute ht->hash2 in a loop until found or whole table searched
			int count = 0;
			while(pair->key != k && count < ht->table_size) {
				unsigned int h = (hval + count * ht->hash2(k, ht->table_size, count)) % ht->table_size;
				pair = (KeyDataPair *)(ht->htable[h]);
				if(0 == keyCmp((void *)(pair->key),(void *)k)) {
					return(pair->data);
				}
				count++;
			}
			fprintf(stderr,"Warning: table searched, "KEY_PRINT_FORMAT" not found\n", pair->key);
		}
		if(0 == keyCmp((void *)(pair->key),(void *)k))
			return(pair->data);
	}

	return NULL;
}//hash_search()

/* 
** Insert (k,data) into ht
** Does not check for duplicates.
** INPUTS:
**   ht is hash table
**    k is key
** SIDE_EFFECT: probably mallocs space for both k and data
*/
void
hash_insert(HashTable *ht, Key k, void *data) {
	assert(ht != NULL);

	assert(ht->hash1 != NULL);
	unsigned int hval = ht->hash1(k, ht->table_size, 0);

	if (ht->chain_style == Array)
		array_add((array_t *)(ht->htable[hval]), k, data, ht->mtf_flag == MTF_TRUE);
	else if (ht->chain_style == List) 
		list_add((list_t *)(ht->htable[hval]), k, data, ht->mtf_flag == MTF_TRUE);
	else if (ht->chain_style == DoubleHash)  {
		KeyDataPair *pair = (KeyDataPair *)(ht->htable[hval]);
			// look for pair->data == NULL, which is empty slot
		int count = 0;
		while (pair->data != NULL && count < ht->table_size) {
			unsigned int h = (hval + count * ht->hash2(k, ht->table_size, count)) % ht->table_size;
			pair = (KeyDataPair *)(ht->htable[h]);
			count++;
		}
		if (count < ht->table_size) {
			pair->key = k;
			pair->data = data;
		} else {
			fprintf(stderr,"Warning: table full, "KEY_PRINT_FORMAT" not inserted\n", k);
		}
	}
}

/* 
** Insert (k,data) into ht
** Does not check for duplicates.
** INPUTS:
**   ht is hash table
** SIDE_EFFECT: prints ht
*/
void
hash_print(HashTable *ht) {
	printf("********* HASH TABLE size=%d mtf=%d\n",ht->table_size, ht->mtf_flag);
	for(int i =0 ; i < ht->table_size ; i++) {
		printf("%4d ", i);
		if (ht->chain_style == Array)
			array_print((array_t *)(ht->htable[i]));
		else if (ht->chain_style == List)
			list_print((list_t *)(ht->htable[i]));
		else if (ht->chain_style == DoubleHash) {
			KeyDataPair *pair = (KeyDataPair *)(ht->htable[i]);
			if (pair->data == NULL)
				printf("NULL");
			else
				printf(KEY_PRINT_FORMAT,pair->key);
		}
		printf("\n");
	}
	fflush(stdout);
}// hash_print()
