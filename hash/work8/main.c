/*
** COMP200007 Design of Algorithms 
** Test harness for various hash table implementations.
** Assumes Key is int.
**
**
** Author: Andrew Turpin
** Wed  8 May 2013 19:21:49 EST
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "key.h"
#include "MurmurHash3.h"
#include "hashtable.h"


/*
** Wrap call to MurmurHash3_x86_32 with HashFn compatible type
*/
unsigned int 
murmur(Key k, unsigned int m, unsigned int probe_num) {
    uint32_t out;
    uint8_t key = k;
    MurmurHash3_x86_32(&key, m, 1273891, &out );
    return out % m;
}

unsigned int 
basic_hash(Key k, unsigned int m, unsigned int probe_num) {
    return k % m;
}

unsigned int 
basic_hash2(Key k, unsigned int m, unsigned int probe_num) {
    return 1 + (k % (m-1));
}

/*
** Read in first file of keys, 
** Insert into hashtable, 
** Search for keys in second file
** Print time
*/
int
main(int argc, char *argv[]) {

    if (argc != 6) {
        fprintf(stderr,"Usage: %s a|c|d 0|1 size filename1 filename2\n",argv[0]);
        fprintf(stderr,"    where\n");
        fprintf(stderr,"       a for array, c for chaining, d for double hashing\n");
        fprintf(stderr,"       0 for no MTF, 1 for MTF\n");
        fprintf(stderr,"       size is number of elements in table\n");
        fprintf(stderr,"       filename1 is keys (one per line) to insert\n");
        fprintf(stderr,"       filename2 is keys (one per line) to search\n");
        return EXIT_FAILURE;
    }

    /*
    ** Create table
    */
    int mtf, size;
    char type;
    sscanf(argv[1], "%c", &type);
    sscanf(argv[2], "%d", &mtf);
    sscanf(argv[3], "%d", &size);

    clock_t start_time = clock();

    HashTable *ht = hash_create(
                type == 'a' ? Array : (type == 'd' ? DoubleHash : List), 
                mtf ? MTF_TRUE : MTF_FALSE, 
                //murmur, 
                basic_hash, 
                basic_hash2, 
                size); 

    /*
    ** Insert keys from filename 1 (argv[4])
    */
    FILE *f1 = fopen(argv[4], "r");
    assert(f1 != NULL);

    #define BUFF_SIZE 128   // max length of key in ascii chars
    char buff[BUFF_SIZE];
    while (fgets(buff, BUFF_SIZE, f1) != NULL) {
        Key key;
        sscanf(buff, KEY_PRINT_FORMAT, &key);    
        void *data = malloc(sizeof(1)); // data ptr is junk, but not NULL
        assert(data != NULL);
        hash_insert(ht, key, data);           
    }
    fclose(f1);
    //hash_print(ht);

    /*
    ** Search keys from filename 1 (argv[4])
    */
    FILE *f2 = fopen(argv[5], "r");
    assert(f2 != NULL);
    int count_found = 0;
    int count_not_found = 0;
    while (fgets(buff, BUFF_SIZE, f2) != NULL) {
        Key key;
        sscanf(buff, KEY_PRINT_FORMAT, &key);    
        void *res = hash_search(ht, key);
        count_not_found += res == NULL;
        count_found     += res != NULL;
    }
    fclose(f2);
    //hash_print(ht);

    printf("found= %d not_found= %d time= %f\n",count_found, count_not_found, 
        ((float)clock()-(float)start_time)/(float)CLOCKS_PER_SEC*1000.0);
}
