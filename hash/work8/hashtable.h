/* 
** COMP200007 Design of Algorithms 
** Hash tables with separate chaining and arrays instead of LL.
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:21:49 EST
*/


    // DoubleHash not implemented - no chains at all
enum HashChainStyle {List, Array, DoubleHash}; 

#define MTF_FALSE 0     // selects if MTF used or not
#define MTF_TRUE  1

    // hash functions take 3 arguments: key, table size m, 
    // and the probe number (0 is initial probe)
typedef unsigned int (*HashFn)(Key k, unsigned int m, unsigned int probe_num);

typedef struct {
    HashFn hash1;                // hash function
    HashFn hash2;                // hash function 2 (for double hashing)
    int table_size;              // m
    int mtf_flag;                // MTF_TRUE for MTF, MTF_FALSE otherwise;
    HashChainStyle chain_style;  // one of HashChainStyle
    void **htable;               // either array of array_t * or list_t *
} HashTable;

    // this is used for DoubleHash as an array element
typedef struct {
    Key key;
    void *data;
} KeyDataPair;

HashTable *hash_create(HashChainStyle type, int mtf, HashFn h1, HashFn h2, int size); // create empty hash table
void      *hash_search(HashTable *ht, Key k);            // Search ht for k, return data ptr if found, else NULL 
void       hash_insert(HashTable *ht, Key k, void *d);   // insert d with key k into ht
void       hash_print(HashTable *ht);                    // print whole table
